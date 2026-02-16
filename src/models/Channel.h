#pragma once

#include <QObject>
#include <QString>

class Channel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString serverId READ serverId WRITE setServerId NOTIFY serverIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString topic READ topic WRITE setTopic NOTIFY topicChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)

public:
    explicit Channel(QObject *parent = nullptr);
    
    QString id() const { return m_id; }
    void setId(const QString& id);
    
    QString serverId() const { return m_serverId; }
    void setServerId(const QString& serverId);
    
    QString name() const { return m_name; }
    void setName(const QString& name);
    
    QString type() const { return m_type; }
    void setType(const QString& type);
    
    QString topic() const { return m_topic; }
    void setTopic(const QString& topic);
    
    int position() const { return m_position; }
    void setPosition(int position);
    
signals:
    void idChanged();
    void serverIdChanged();
    void nameChanged();
    void typeChanged();
    void topicChanged();
    void positionChanged();

private:
    QString m_id;
    QString m_serverId;
    QString m_name;
    QString m_type;
    QString m_topic;
    int m_position = 0;
};
