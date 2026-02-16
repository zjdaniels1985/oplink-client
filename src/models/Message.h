#pragma once

#include <QObject>
#include <QString>
#include <QDateTime>

class Message : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString channelId READ channelId WRITE setChannelId NOTIFY channelIdChanged)
    Q_PROPERTY(QString authorId READ authorId WRITE setAuthorId NOTIFY authorIdChanged)
    Q_PROPERTY(QString authorName READ authorName WRITE setAuthorName NOTIFY authorNameChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QDateTime timestamp READ timestamp WRITE setTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(bool edited READ edited WRITE setEdited NOTIFY editedChanged)

public:
    explicit Message(QObject *parent = nullptr);
    
    QString id() const { return m_id; }
    void setId(const QString& id);
    
    QString channelId() const { return m_channelId; }
    void setChannelId(const QString& channelId);
    
    QString authorId() const { return m_authorId; }
    void setAuthorId(const QString& authorId);
    
    QString authorName() const { return m_authorName; }
    void setAuthorName(const QString& authorName);
    
    QString content() const { return m_content; }
    void setContent(const QString& content);
    
    QDateTime timestamp() const { return m_timestamp; }
    void setTimestamp(const QDateTime& timestamp);
    
    bool edited() const { return m_edited; }
    void setEdited(bool edited);
    
signals:
    void idChanged();
    void channelIdChanged();
    void authorIdChanged();
    void authorNameChanged();
    void contentChanged();
    void timestampChanged();
    void editedChanged();

private:
    QString m_id;
    QString m_channelId;
    QString m_authorId;
    QString m_authorName;
    QString m_content;
    QDateTime m_timestamp;
    bool m_edited = false;
};
