#pragma once

#include <QObject>
#include <QList>
#include <QMap>
#include "models/Message.h"

class MessageStore : public QObject {
    Q_OBJECT

public:
    static MessageStore* instance();
    
    QList<Message*> messagesForChannel(const QString& channelId) const;
    void addMessage(Message* message);
    void removeMessage(const QString& messageId);
    void updateMessage(Message* message);
    Message* findMessage(const QString& messageId);
    
    void clear();
    void clearForChannel(const QString& channelId);
    
    // Pagination support (placeholder for cursor-based pagination)
    void setBeforeCursor(const QString& channelId, const QString& cursor);
    void setAfterCursor(const QString& channelId, const QString& cursor);
    QString beforeCursor(const QString& channelId) const;
    QString afterCursor(const QString& channelId) const;
    bool hasMoreBefore(const QString& channelId) const;
    bool hasMoreAfter(const QString& channelId) const;
    
signals:
    void messageAdded(Message* message);
    void messageUpdated(Message* message);
    void messageRemoved(const QString& messageId);
    void messagesChanged(const QString& channelId);

private:
    explicit MessageStore(QObject *parent = nullptr);
    ~MessageStore() override = default;
    
    // Messages indexed by channel ID
    QMap<QString, QList<Message*>> m_messagesByChannel;
    
    // Pagination cursors (placeholder)
    QMap<QString, QString> m_beforeCursors;
    QMap<QString, QString> m_afterCursors;
    QMap<QString, bool> m_hasMoreBefore;
    QMap<QString, bool> m_hasMoreAfter;
    
    static MessageStore* s_instance;
};
