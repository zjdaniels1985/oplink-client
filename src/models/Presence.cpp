#include "Presence.h"

Presence::Presence(QObject *parent)
    : QObject(parent)
{
}

void Presence::setUserId(const QString& userId) {
    if (m_userId != userId) {
        m_userId = userId;
        emit userIdChanged();
    }
}

void Presence::setServerId(const QString& serverId) {
    if (m_serverId != serverId) {
        m_serverId = serverId;
        emit serverIdChanged();
    }
}

void Presence::setStatus(const QString& status) {
    if (m_status != status) {
        m_status = status;
        emit statusChanged();
    }
}

void Presence::setCustomStatus(const QString& customStatus) {
    if (m_customStatus != customStatus) {
        m_customStatus = customStatus;
        emit customStatusChanged();
    }
}

void Presence::setLastSeen(const QDateTime& lastSeen) {
    if (m_lastSeen != lastSeen) {
        m_lastSeen = lastSeen;
        emit lastSeenChanged();
    }
}
