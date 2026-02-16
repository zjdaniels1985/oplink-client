#include "MessageService.h"
#include "config/ConfigManager.h"
#include "stores/MessageStore.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QDebug>

MessageService* MessageService::s_instance = nullptr;

MessageService::MessageService(QObject *parent)
    : QObject(parent)
    , m_httpClient(new HttpClient(this))
    , m_wsClient(new WsClient(this))
{
    m_httpClient->setBaseUrl(ConfigManager::instance()->apiBaseUrl());
    m_wsClient->setUrl(ConfigManager::instance()->wsBaseUrl());
}

MessageService* MessageService::instance() {
    if (!s_instance) {
        s_instance = new MessageService();
    }
    return s_instance;
}

void MessageService::fetchHistory(const QString& channelId,
                                  const QString& beforeCursor,
                                  int limit) {
    QString path = QString("/channels/%1/messages").arg(channelId);
    
    // TODO: Add query parameters for cursor and limit when backend supports it
    // For now, just fetch without pagination
    
    m_httpClient->get(path,
        [this, channelId](QJsonDocument doc, QString error) {
            if (!error.isEmpty()) {
                emit historyFetchFailed(error);
                return;
            }
            
            QJsonArray messagesArray = doc.array();
            QList<Message*> messages;
            
            for (const QJsonValue& value : messagesArray) {
                QJsonObject msgObj = value.toObject();
                
                Message* message = new Message();
                message->setId(msgObj.value("id").toString());
                message->setChannelId(channelId);
                message->setAuthorId(msgObj.value("authorId").toString());
                message->setAuthorName(msgObj.value("authorName").toString());
                message->setContent(msgObj.value("content").toString());
                
                QString timestampStr = msgObj.value("timestamp").toString();
                QDateTime timestamp = QDateTime::fromString(timestampStr, Qt::ISODate);
                message->setTimestamp(timestamp);
                
                message->setEdited(msgObj.value("edited").toBool(false));
                
                messages.append(message);
                
                // Also add to store
                MessageStore::instance()->addMessage(message);
            }
            
            // Placeholder cursors (would come from backend response)
            QString beforeCursor;
            QString afterCursor;
            
            emit historyFetched(channelId, messages, beforeCursor, afterCursor);
        });
}

void MessageService::sendMessage(const QString& channelId, const QString& content) {
    QString path = QString("/channels/%1/messages").arg(channelId);
    
    QJsonObject data;
    data["content"] = content;
    
    m_httpClient->post(path, data,
        [this](QJsonDocument doc, QString error) {
            if (!error.isEmpty()) {
                emit messageSendFailed(error);
                return;
            }
            
            QJsonObject msgObj = doc.object();
            
            Message* message = new Message();
            message->setId(msgObj.value("id").toString());
            message->setChannelId(msgObj.value("channelId").toString());
            message->setAuthorId(msgObj.value("authorId").toString());
            message->setAuthorName(msgObj.value("authorName").toString());
            message->setContent(msgObj.value("content").toString());
            
            QString timestampStr = msgObj.value("timestamp").toString();
            QDateTime timestamp = QDateTime::fromString(timestampStr, Qt::ISODate);
            message->setTimestamp(timestamp);
            
            MessageStore::instance()->addMessage(message);
            emit messageSent(message);
        });
}

void MessageService::subscribeToChannel(const QString& channelId) {
    QString destination = QString("/topic/channels/%1/messages").arg(channelId);
    
    m_wsClient->subscribe(destination, 
        [this](QJsonObject data) {
            handleMessageFromWs(data);
        });
}

void MessageService::unsubscribeFromChannel(const QString& channelId) {
    QString destination = QString("/topic/channels/%1/messages").arg(channelId);
    m_wsClient->unsubscribe(destination);
}

void MessageService::handleMessageFromWs(const QJsonObject& data) {
    Message* message = new Message();
    message->setId(data.value("id").toString());
    message->setChannelId(data.value("channelId").toString());
    message->setAuthorId(data.value("authorId").toString());
    message->setAuthorName(data.value("authorName").toString());
    message->setContent(data.value("content").toString());
    
    QString timestampStr = data.value("timestamp").toString();
    QDateTime timestamp = QDateTime::fromString(timestampStr, Qt::ISODate);
    message->setTimestamp(timestamp);
    
    message->setEdited(data.value("edited").toBool(false));
    
    MessageStore::instance()->addMessage(message);
    emit messageReceived(message);
}
