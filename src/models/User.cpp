#include "User.h"

User::User(QObject *parent)
    : QObject(parent)
{
}

void User::setId(const QString& id) {
    if (m_id != id) {
        m_id = id;
        emit idChanged();
    }
}

void User::setUsername(const QString& username) {
    if (m_username != username) {
        m_username = username;
        emit usernameChanged();
    }
}

void User::setEmail(const QString& email) {
    if (m_email != email) {
        m_email = email;
        emit emailChanged();
    }
}

void User::setAvatar(const QString& avatar) {
    if (m_avatar != avatar) {
        m_avatar = avatar;
        emit avatarChanged();
    }
}

void User::setStatus(const QString& status) {
    if (m_status != status) {
        m_status = status;
        emit statusChanged();
    }
}

void User::setOnline(bool online) {
    if (m_online != online) {
        m_online = online;
        emit onlineChanged();
    }
}
