#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <functional>

class HttpClient : public QObject {
    Q_OBJECT

public:
    explicit HttpClient(QObject *parent = nullptr);
    ~HttpClient() override;
    
    void setBaseUrl(const QString& baseUrl);
    void setAuthToken(const QString& token);
    
    void get(const QString& path, 
             std::function<void(QJsonDocument, QString)> callback);
    
    void post(const QString& path, 
              const QJsonObject& data,
              std::function<void(QJsonDocument, QString)> callback);
    
    void put(const QString& path,
             const QJsonObject& data,
             std::function<void(QJsonDocument, QString)> callback);
    
    void del(const QString& path,
             std::function<void(QJsonDocument, QString)> callback);

private:
    void handleReply(QNetworkReply* reply,
                     std::function<void(QJsonDocument, QString)> callback);
    
    QNetworkAccessManager* m_networkManager;
    QString m_baseUrl;
    QString m_authToken;
};
