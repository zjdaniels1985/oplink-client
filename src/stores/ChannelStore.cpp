#include "ChannelStore.h"

ChannelStore* ChannelStore::s_instance = nullptr;

ChannelStore::ChannelStore(QObject *parent)
    : QObject(parent)
{
}

ChannelStore* ChannelStore::instance() {
    if (!s_instance) {
        s_instance = new ChannelStore();
    }
    return s_instance;
}

QList<Channel*> ChannelStore::channelsForServer(const QString& serverId) const {
    QList<Channel*> result;
    for (Channel* channel : m_channels) {
        if (channel->serverId() == serverId) {
            result.append(channel);
        }
    }
    return result;
}

void ChannelStore::addChannel(Channel* channel) {
    if (!channel) {
        return;
    }
    
    // Check if channel already exists
    for (Channel* c : m_channels) {
        if (c->id() == channel->id()) {
            return;
        }
    }
    
    channel->setParent(this);
    m_channels.append(channel);
    emit channelsChanged();
    emit channelAdded(channel);
}

void ChannelStore::removeChannel(const QString& channelId) {
    for (int i = 0; i < m_channels.size(); ++i) {
        if (m_channels[i]->id() == channelId) {
            Channel* channel = m_channels.takeAt(i);
            if (m_currentChannel == channel) {
                m_currentChannel = nullptr;
                emit currentChannelChanged();
            }
            channel->deleteLater();
            emit channelsChanged();
            emit channelRemoved(channelId);
            break;
        }
    }
}

void ChannelStore::setCurrentChannel(Channel* channel) {
    if (m_currentChannel != channel) {
        m_currentChannel = channel;
        emit currentChannelChanged();
    }
}

Channel* ChannelStore::findChannel(const QString& channelId) {
    for (Channel* channel : m_channels) {
        if (channel->id() == channelId) {
            return channel;
        }
    }
    return nullptr;
}

void ChannelStore::clear() {
    qDeleteAll(m_channels);
    m_channels.clear();
    m_currentChannel = nullptr;
    emit channelsChanged();
    emit currentChannelChanged();
}

void ChannelStore::clearForServer(const QString& serverId) {
    QList<Channel*> toRemove;
    for (Channel* channel : m_channels) {
        if (channel->serverId() == serverId) {
            toRemove.append(channel);
        }
    }
    
    for (Channel* channel : toRemove) {
        removeChannel(channel->id());
    }
}
