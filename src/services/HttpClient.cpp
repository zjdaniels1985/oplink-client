#include "HttpClient.h"
#include <QJsonParseError>
#include <QNetworkRequest>
#include <QDebug>

HttpClient::HttpClient(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
}

HttpClient::~HttpClient() = default;

void HttpClient::setBaseUrl(const QString& baseUrl) {
    m_baseUrl = baseUrl;
    if (m_baseUrl.endsWith('/')) {
        m_baseUrl.chop(1);
    }
}

void HttpClient::setAuthToken(const QString& token) {
    m_authToken = token;
}

void HttpClient::get(const QString& path, 
                     std::function<void(QJsonDocument, QString)> callback) {
    QString url = m_baseUrl + path;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    if (!m_authToken.isEmpty()) {
        request.setRawHeader("Authorization", ("Bearer " + m_authToken).toUtf8());
    }
    
    QNetworkReply* reply = m_networkManager->get(request);
    handleReply(reply, callback);
}

void HttpClient::post(const QString& path,
                      const QJsonObject& data,
                      std::function<void(QJsonDocument, QString)> callback) {
    QString url = m_baseUrl + path;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    if (!m_authToken.isEmpty()) {
        request.setRawHeader("Authorization", ("Bearer " + m_authToken).toUtf8());
    }
    
    QJsonDocument doc(data);
    QByteArray jsonData = doc.toJson();
    
    QNetworkReply* reply = m_networkManager->post(request, jsonData);
    handleReply(reply, callback);
}

void HttpClient::put(const QString& path,
                     const QJsonObject& data,
                     std::function<void(QJsonDocument, QString)> callback) {
    QString url = m_baseUrl + path;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    if (!m_authToken.isEmpty()) {
        request.setRawHeader("Authorization", ("Bearer " + m_authToken).toUtf8());
    }
    
    QJsonDocument doc(data);
    QByteArray jsonData = doc.toJson();
    
    QNetworkReply* reply = m_networkManager->put(request, jsonData);
    handleReply(reply, callback);
}

void HttpClient::del(const QString& path,
                     std::function<void(QJsonDocument, QString)> callback) {
    QString url = m_baseUrl + path;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    if (!m_authToken.isEmpty()) {
        request.setRawHeader("Authorization", ("Bearer " + m_authToken).toUtf8());
    }
    
    QNetworkReply* reply = m_networkManager->deleteResource(request);
    handleReply(reply, callback);
}

void HttpClient::handleReply(QNetworkReply* reply,
                              std::function<void(QJsonDocument, QString)> callback) {
    connect(reply, &QNetworkReply::finished, this, [reply, callback]() {
        if (reply->error() != QNetworkReply::NoError) {
            QString errorMsg = reply->errorString();
            qWarning() << "HTTP error:" << errorMsg;
            callback(QJsonDocument(), errorMsg);
            reply->deleteLater();
            return;
        }
        
        QByteArray data = reply->readAll();
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
        
        if (parseError.error != QJsonParseError::NoError) {
            QString errorMsg = "JSON parse error: " + parseError.errorString();
            qWarning() << errorMsg;
            callback(QJsonDocument(), errorMsg);
            reply->deleteLater();
            return;
        }
        
        callback(doc, QString());
        reply->deleteLater();
    });
}
