#include "ConfigManager.h"
#include <QFile>
#include <QJsonParseError>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

ConfigManager* ConfigManager::s_instance = nullptr;

ConfigManager::ConfigManager(QObject *parent)
    : QObject(parent)
{
}

ConfigManager* ConfigManager::instance() {
    if (!s_instance) {
        s_instance = new ConfigManager();
    }
    return s_instance;
}

bool ConfigManager::load() {
    // Try loading from multiple locations in order:
    // 1. ./config.json (working directory)
    // 2. Executable directory + config.json
    // 3. User config directory
    
    QStringList configPaths;
    configPaths << "config.json";
    configPaths << QCoreApplication::applicationDirPath() + "/config.json";
    
    QString userConfigDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    configPaths << userConfigDir + "/config.json";
    
    QString configPath;
    QFile file;
    
    for (const QString& path : configPaths) {
        file.setFileName(path);
        if (file.exists()) {
            configPath = path;
            break;
        }
    }
    
    if (configPath.isEmpty()) {
        qWarning() << "No config.json found. Using defaults.";
        // Set defaults
        m_apiBaseUrl = "http://localhost:8080/api";
        m_wsBaseUrl = "ws://localhost:8080/ws";
        m_sfuSignalUrl = "http://localhost:8080/api/voice";
        applyEnvironmentOverrides();
        return false;
    }
    
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open config file:" << configPath;
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse config.json:" << parseError.errorString();
        return false;
    }
    
    if (!doc.isObject()) {
        qWarning() << "Invalid config.json: root must be an object";
        return false;
    }
    
    QJsonObject config = doc.object();
    
    // Load main URLs
    m_apiBaseUrl = config.value("apiBaseUrl").toString("http://localhost:8080/api");
    m_wsBaseUrl = config.value("wsBaseUrl").toString("ws://localhost:8080/ws");
    m_sfuSignalUrl = config.value("sfuSignalUrl").toString("http://localhost:8080/api/voice");
    
    // Load sub-configs
    m_turnConfig = config.value("turn").toObject();
    m_features = config.value("features").toObject();
    m_audioConfig = config.value("audio").toObject();
    m_videoConfig = config.value("video").toObject();
    
    qInfo() << "Loaded config from:" << configPath;
    qInfo() << "API Base URL:" << m_apiBaseUrl;
    qInfo() << "WS Base URL:" << m_wsBaseUrl;
    qInfo() << "SFU Signal URL:" << m_sfuSignalUrl;
    
    // Apply environment variable overrides
    applyEnvironmentOverrides();
    
    emit configChanged();
    return true;
}

void ConfigManager::applyEnvironmentOverrides() {
    // Allow environment variables to override config values
    QString envApiUrl = qEnvironmentVariable("OPLINK_API_URL");
    if (!envApiUrl.isEmpty()) {
        m_apiBaseUrl = envApiUrl;
        qInfo() << "Override API URL from environment:" << m_apiBaseUrl;
    }
    
    QString envWsUrl = qEnvironmentVariable("OPLINK_WS_URL");
    if (!envWsUrl.isEmpty()) {
        m_wsBaseUrl = envWsUrl;
        qInfo() << "Override WS URL from environment:" << m_wsBaseUrl;
    }
    
    QString envSfuUrl = qEnvironmentVariable("OPLINK_SFU_URL");
    if (!envSfuUrl.isEmpty()) {
        m_sfuSignalUrl = envSfuUrl;
        qInfo() << "Override SFU URL from environment:" << m_sfuSignalUrl;
    }
}

bool ConfigManager::isFeatureEnabled(const QString& feature) const {
    return m_features.value(feature).toBool(false);
}
