#pragma once

#include <QObject>
#include <QString>
#include <QDateTime>

class User : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(bool online READ online WRITE setOnline NOTIFY onlineChanged)

public:
    explicit User(QObject *parent = nullptr);
    
    QString id() const { return m_id; }
    void setId(const QString& id);
    
    QString username() const { return m_username; }
    void setUsername(const QString& username);
    
    QString email() const { return m_email; }
    void setEmail(const QString& email);
    
    QString avatar() const { return m_avatar; }
    void setAvatar(const QString& avatar);
    
    QString status() const { return m_status; }
    void setStatus(const QString& status);
    
    bool online() const { return m_online; }
    void setOnline(bool online);
    
signals:
    void idChanged();
    void usernameChanged();
    void emailChanged();
    void avatarChanged();
    void statusChanged();
    void onlineChanged();

private:
    QString m_id;
    QString m_username;
    QString m_email;
    QString m_avatar;
    QString m_status;
    bool m_online = false;
};
