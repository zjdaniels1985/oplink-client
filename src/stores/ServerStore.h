#pragma once

#include <QObject>
#include <QList>
#include "models/Server.h"

class ServerStore : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<Server*> servers READ servers NOTIFY serversChanged)
    Q_PROPERTY(Server* currentServer READ currentServer NOTIFY currentServerChanged)

public:
    static ServerStore* instance();
    
    QList<Server*> servers() const { return m_servers; }
    Server* currentServer() { return m_currentServer; }
    
    void addServer(Server* server);
    void removeServer(const QString& serverId);
    void setCurrentServer(Server* server);
    Server* findServer(const QString& serverId);
    void clear();
    
signals:
    void serversChanged();
    void currentServerChanged();
    void serverAdded(Server* server);
    void serverRemoved(const QString& serverId);

private:
    explicit ServerStore(QObject *parent = nullptr);
    ~ServerStore() override = default;
    
    QList<Server*> m_servers;
    Server* m_currentServer = nullptr;
    
    static ServerStore* s_instance;
};
