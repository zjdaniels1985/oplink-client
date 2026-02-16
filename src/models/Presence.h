#pragma once

#include <QObject>
#include <QString>
#include <QDateTime>

class Presence : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString serverId READ serverId WRITE setServerId NOTIFY serverIdChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString customStatus READ customStatus WRITE setCustomStatus NOTIFY customStatusChanged)
    Q_PROPERTY(QDateTime lastSeen READ lastSeen WRITE setLastSeen NOTIFY lastSeenChanged)

public:
    explicit Presence(QObject *parent = nullptr);
    
    QString userId() const { return m_userId; }
    void setUserId(const QString& userId);
    
    QString serverId() const { return m_serverId; }
    void setServerId(const QString& serverId);
    
    QString status() const { return m_status; }
    void setStatus(const QString& status);
    
    QString customStatus() const { return m_customStatus; }
    void setCustomStatus(const QString& customStatus);
    
    QDateTime lastSeen() const { return m_lastSeen; }
    void setLastSeen(const QDateTime& lastSeen);
    
signals:
    void userIdChanged();
    void serverIdChanged();
    void statusChanged();
    void customStatusChanged();
    void lastSeenChanged();

private:
    QString m_userId;
    QString m_serverId;
    QString m_status;
    QString m_customStatus;
    QDateTime m_lastSeen;
};
