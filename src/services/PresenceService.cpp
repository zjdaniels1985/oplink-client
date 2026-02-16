#include "PresenceService.h"
#include "config/ConfigManager.h"
#include <QJsonObject>
#include <QDateTime>
#include <QDebug>

PresenceService* PresenceService::s_instance = nullptr;

PresenceService::PresenceService(QObject *parent)
    : QObject(parent)
    , m_wsClient(new WsClient(this))
{
    m_wsClient->setUrl(ConfigManager::instance()->wsBaseUrl());
}

PresenceService* PresenceService::instance() {
    if (!s_instance) {
        s_instance = new PresenceService();
    }
    return s_instance;
}

void PresenceService::subscribeToServer(const QString& serverId) {
    QString destination = QString("/topic/servers/%1/presence").arg(serverId);
    
    m_wsClient->subscribe(destination,
        [this](QJsonObject data) {
            handlePresenceFromWs(data);
        });
}

void PresenceService::unsubscribeFromServer(const QString& serverId) {
    QString destination = QString("/topic/servers/%1/presence").arg(serverId);
    m_wsClient->unsubscribe(destination);
}

void PresenceService::updateStatus(const QString& serverId, const QString& status) {
    QString destination = QString("/app/servers/%1/presence").arg(serverId);
    
    QJsonObject data;
    data["status"] = status;
    
    m_wsClient->send(destination, data);
}

void PresenceService::handlePresenceFromWs(const QJsonObject& data) {
    Presence* presence = new Presence();
    presence->setUserId(data.value("userId").toString());
    presence->setServerId(data.value("serverId").toString());
    presence->setStatus(data.value("status").toString());
    presence->setCustomStatus(data.value("customStatus").toString());
    
    QString lastSeenStr = data.value("lastSeen").toString();
    if (!lastSeenStr.isEmpty()) {
        QDateTime lastSeen = QDateTime::fromString(lastSeenStr, Qt::ISODate);
        presence->setLastSeen(lastSeen);
    }
    
    emit presenceUpdated(presence);
}
