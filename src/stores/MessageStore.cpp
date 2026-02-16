#include "MessageStore.h"

MessageStore* MessageStore::s_instance = nullptr;

MessageStore::MessageStore(QObject *parent)
    : QObject(parent)
{
}

MessageStore* MessageStore::instance() {
    if (!s_instance) {
        s_instance = new MessageStore();
    }
    return s_instance;
}

QList<Message*> MessageStore::messagesForChannel(const QString& channelId) const {
    return m_messagesByChannel.value(channelId, QList<Message*>());
}

void MessageStore::addMessage(Message* message) {
    if (!message) {
        return;
    }
    
    QString channelId = message->channelId();
    
    // Check if message already exists
    QList<Message*>& messages = m_messagesByChannel[channelId];
    for (Message* m : messages) {
        if (m->id() == message->id()) {
            return;
        }
    }
    
    message->setParent(this);
    messages.append(message);
    
    // Sort by timestamp
    std::sort(messages.begin(), messages.end(), 
              [](const Message* a, const Message* b) {
                  return a->timestamp() < b->timestamp();
              });
    
    emit messageAdded(message);
    emit messagesChanged(channelId);
}

void MessageStore::removeMessage(const QString& messageId) {
    for (auto it = m_messagesByChannel.begin(); it != m_messagesByChannel.end(); ++it) {
        QList<Message*>& messages = it.value();
        for (int i = 0; i < messages.size(); ++i) {
            if (messages[i]->id() == messageId) {
                Message* message = messages.takeAt(i);
                QString channelId = message->channelId();
                message->deleteLater();
                emit messageRemoved(messageId);
                emit messagesChanged(channelId);
                return;
            }
        }
    }
}

void MessageStore::updateMessage(Message* message) {
    if (!message) {
        return;
    }
    
    Message* existing = findMessage(message->id());
    if (existing) {
        existing->setContent(message->content());
        existing->setEdited(message->edited());
        emit messageUpdated(existing);
        emit messagesChanged(existing->channelId());
    }
}

Message* MessageStore::findMessage(const QString& messageId) {
    for (const QList<Message*>& messages : m_messagesByChannel) {
        for (Message* message : messages) {
            if (message->id() == messageId) {
                return message;
            }
        }
    }
    return nullptr;
}

void MessageStore::clear() {
    for (const QList<Message*>& messages : m_messagesByChannel) {
        qDeleteAll(messages);
    }
    m_messagesByChannel.clear();
    m_beforeCursors.clear();
    m_afterCursors.clear();
    m_hasMoreBefore.clear();
    m_hasMoreAfter.clear();
}

void MessageStore::clearForChannel(const QString& channelId) {
    if (m_messagesByChannel.contains(channelId)) {
        qDeleteAll(m_messagesByChannel[channelId]);
        m_messagesByChannel.remove(channelId);
        m_beforeCursors.remove(channelId);
        m_afterCursors.remove(channelId);
        m_hasMoreBefore.remove(channelId);
        m_hasMoreAfter.remove(channelId);
        emit messagesChanged(channelId);
    }
}

void MessageStore::setBeforeCursor(const QString& channelId, const QString& cursor) {
    m_beforeCursors[channelId] = cursor;
    m_hasMoreBefore[channelId] = !cursor.isEmpty();
}

void MessageStore::setAfterCursor(const QString& channelId, const QString& cursor) {
    m_afterCursors[channelId] = cursor;
    m_hasMoreAfter[channelId] = !cursor.isEmpty();
}

QString MessageStore::beforeCursor(const QString& channelId) const {
    return m_beforeCursors.value(channelId, QString());
}

QString MessageStore::afterCursor(const QString& channelId) const {
    return m_afterCursors.value(channelId, QString());
}

bool MessageStore::hasMoreBefore(const QString& channelId) const {
    return m_hasMoreBefore.value(channelId, false);
}

bool MessageStore::hasMoreAfter(const QString& channelId) const {
    return m_hasMoreAfter.value(channelId, false);
}
