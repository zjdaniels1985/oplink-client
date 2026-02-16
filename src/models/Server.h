#pragma once

#include <QObject>
#include <QString>

class Server : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString ownerId READ ownerId WRITE setOwnerId NOTIFY ownerIdChanged)

public:
    explicit Server(QObject *parent = nullptr);
    
    QString id() const { return m_id; }
    void setId(const QString& id);
    
    QString name() const { return m_name; }
    void setName(const QString& name);
    
    QString icon() const { return m_icon; }
    void setIcon(const QString& icon);
    
    QString ownerId() const { return m_ownerId; }
    void setOwnerId(const QString& ownerId);
    
signals:
    void idChanged();
    void nameChanged();
    void iconChanged();
    void ownerIdChanged();

private:
    QString m_id;
    QString m_name;
    QString m_icon;
    QString m_ownerId;
};
