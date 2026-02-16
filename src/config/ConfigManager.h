#pragma once

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class ConfigManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString apiBaseUrl READ apiBaseUrl NOTIFY configChanged)
    Q_PROPERTY(QString wsBaseUrl READ wsBaseUrl NOTIFY configChanged)
    Q_PROPERTY(QString sfuSignalUrl READ sfuSignalUrl NOTIFY configChanged)

public:
    static ConfigManager* instance();
    
    bool load();
    
    QString apiBaseUrl() const { return m_apiBaseUrl; }
    QString wsBaseUrl() const { return m_wsBaseUrl; }
    QString sfuSignalUrl() const { return m_sfuSignalUrl; }
    
    QJsonObject turnConfig() const { return m_turnConfig; }
    QJsonObject features() const { return m_features; }
    QJsonObject audioConfig() const { return m_audioConfig; }
    QJsonObject videoConfig() const { return m_videoConfig; }
    
    bool isFeatureEnabled(const QString& feature) const;
    
signals:
    void configChanged();

private:
    explicit ConfigManager(QObject *parent = nullptr);
    ~ConfigManager() override = default;
    
    void applyEnvironmentOverrides();
    
    QString m_apiBaseUrl;
    QString m_wsBaseUrl;
    QString m_sfuSignalUrl;
    QJsonObject m_turnConfig;
    QJsonObject m_features;
    QJsonObject m_audioConfig;
    QJsonObject m_videoConfig;
    
    static ConfigManager* s_instance;
};
