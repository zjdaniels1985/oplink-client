#pragma once

#include <QObject>
#include <QList>
#include <QMap>
#include "models/Channel.h"

class ChannelStore : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<Channel*> channels READ channels NOTIFY channelsChanged)
    Q_PROPERTY(Channel* currentChannel READ currentChannel NOTIFY currentChannelChanged)

public:
    static ChannelStore* instance();
    
    QList<Channel*> channels() const { return m_channels; }
    QList<Channel*> channelsForServer(const QString& serverId) const;
    Channel* currentChannel() { return m_currentChannel; }
    
    void addChannel(Channel* channel);
    void removeChannel(const QString& channelId);
    void setCurrentChannel(Channel* channel);
    Channel* findChannel(const QString& channelId);
    void clear();
    void clearForServer(const QString& serverId);
    
signals:
    void channelsChanged();
    void currentChannelChanged();
    void channelAdded(Channel* channel);
    void channelRemoved(const QString& channelId);

private:
    explicit ChannelStore(QObject *parent = nullptr);
    ~ChannelStore() override = default;
    
    QList<Channel*> m_channels;
    Channel* m_currentChannel = nullptr;
    
    static ChannelStore* s_instance;
};
