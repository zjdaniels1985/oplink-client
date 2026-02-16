#include "ServerStore.h"

ServerStore* ServerStore::s_instance = nullptr;

ServerStore::ServerStore(QObject *parent)
    : QObject(parent)
{
}

ServerStore* ServerStore::instance() {
    if (!s_instance) {
        s_instance = new ServerStore();
    }
    return s_instance;
}

void ServerStore::addServer(Server* server) {
    if (!server) {
        return;
    }
    
    // Check if server already exists
    for (Server* s : m_servers) {
        if (s->id() == server->id()) {
            return;
        }
    }
    
    server->setParent(this);
    m_servers.append(server);
    emit serversChanged();
    emit serverAdded(server);
}

void ServerStore::removeServer(const QString& serverId) {
    for (int i = 0; i < m_servers.size(); ++i) {
        if (m_servers[i]->id() == serverId) {
            Server* server = m_servers.takeAt(i);
            if (m_currentServer == server) {
                m_currentServer = nullptr;
                emit currentServerChanged();
            }
            server->deleteLater();
            emit serversChanged();
            emit serverRemoved(serverId);
            break;
        }
    }
}

void ServerStore::setCurrentServer(Server* server) {
    if (m_currentServer != server) {
        m_currentServer = server;
        emit currentServerChanged();
    }
}

Server* ServerStore::findServer(const QString& serverId) {
    for (Server* server : m_servers) {
        if (server->id() == serverId) {
            return server;
        }
    }
    return nullptr;
}

void ServerStore::clear() {
    qDeleteAll(m_servers);
    m_servers.clear();
    m_currentServer = nullptr;
    emit serversChanged();
    emit currentServerChanged();
}
