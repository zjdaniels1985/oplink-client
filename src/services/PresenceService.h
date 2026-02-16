#pragma once

#include <QObject>
#include "WsClient.h"
#include "models/Presence.h"

class PresenceService : public QObject {
    Q_OBJECT

public:
    static PresenceService* instance();
    
    void subscribeToServer(const QString& serverId);
    void unsubscribeFromServer(const QString& serverId);
    
    void updateStatus(const QString& serverId, const QString& status);
    
signals:
    void presenceUpdated(Presence* presence);

private:
    explicit PresenceService(QObject *parent = nullptr);
    ~PresenceService() override = default;
    
    void handlePresenceFromWs(const QJsonObject& data);
    
    WsClient* m_wsClient;
    
    static PresenceService* s_instance;
};
