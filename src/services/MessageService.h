#pragma once

#include <QObject>
#include "HttpClient.h"
#include "WsClient.h"
#include "models/Message.h"

class MessageService : public QObject {
    Q_OBJECT

public:
    static MessageService* instance();
    
    void fetchHistory(const QString& channelId, 
                     const QString& beforeCursor = QString(),
                     int limit = 50);
    
    void sendMessage(const QString& channelId, const QString& content);
    
    void subscribeToChannel(const QString& channelId);
    void unsubscribeFromChannel(const QString& channelId);
    
signals:
    void historyFetched(const QString& channelId, 
                       QList<Message*> messages,
                       const QString& beforeCursor,
                       const QString& afterCursor);
    void historyFetchFailed(const QString& error);
    void messageSent(Message* message);
    void messageSendFailed(const QString& error);
    void messageReceived(Message* message);

private:
    explicit MessageService(QObject *parent = nullptr);
    ~MessageService() override = default;
    
    void handleMessageFromWs(const QJsonObject& data);
    
    HttpClient* m_httpClient;
    WsClient* m_wsClient;
    
    static MessageService* s_instance;
};
