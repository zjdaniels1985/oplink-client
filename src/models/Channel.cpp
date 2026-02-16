#include "Channel.h"

Channel::Channel(QObject *parent)
    : QObject(parent)
{
}

void Channel::setId(const QString& id) {
    if (m_id != id) {
        m_id = id;
        emit idChanged();
    }
}

void Channel::setServerId(const QString& serverId) {
    if (m_serverId != serverId) {
        m_serverId = serverId;
        emit serverIdChanged();
    }
}

void Channel::setName(const QString& name) {
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

void Channel::setType(const QString& type) {
    if (m_type != type) {
        m_type = type;
        emit typeChanged();
    }
}

void Channel::setTopic(const QString& topic) {
    if (m_topic != topic) {
        m_topic = topic;
        emit topicChanged();
    }
}

void Channel::setPosition(int position) {
    if (m_position != position) {
        m_position = position;
        emit positionChanged();
    }
}
