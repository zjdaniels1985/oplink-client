#include "Server.h"

Server::Server(QObject *parent)
    : QObject(parent)
{
}

void Server::setId(const QString& id) {
    if (m_id != id) {
        m_id = id;
        emit idChanged();
    }
}

void Server::setName(const QString& name) {
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

void Server::setIcon(const QString& icon) {
    if (m_icon != icon) {
        m_icon = icon;
        emit iconChanged();
    }
}

void Server::setOwnerId(const QString& ownerId) {
    if (m_ownerId != ownerId) {
        m_ownerId = ownerId;
        emit ownerIdChanged();
    }
}
