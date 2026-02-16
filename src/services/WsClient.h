#pragma once

#include <QObject>
#include <QWebSocket>
#include <QString>
#include <QJsonObject>
#include <QTimer>
#include <QMap>
#include <functional>

class WsClient : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    explicit WsClient(QObject *parent = nullptr);
    ~WsClient() override;
    
    void setUrl(const QString& url);
    void setAuthToken(const QString& token);
    
    void connect();
    void disconnect();
    bool connected() const { return m_connected; }
    
    // STOMP protocol methods
    void subscribe(const QString& destination, 
                   std::function<void(QJsonObject)> callback);
    void unsubscribe(const QString& destination);
    void send(const QString& destination, const QJsonObject& payload);
    
signals:
    void connectedChanged();
    void connectionError(const QString& error);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString& message);
    void onError(QAbstractSocket::SocketError error);
    void attemptReconnect();

private:
    void sendStompFrame(const QString& command, 
                        const QMap<QString, QString>& headers,
                        const QString& body = QString());
    void processStompFrame(const QString& frame);
    
    QWebSocket* m_webSocket;
    QString m_url;
    QString m_authToken;
    bool m_connected = false;
    bool m_shouldReconnect = true;
    
    QTimer* m_reconnectTimer;
    int m_reconnectAttempts = 0;
    
    // Subscription callbacks
    QMap<QString, std::function<void(QJsonObject)>> m_subscriptions;
    int m_subscriptionId = 0;
    QMap<QString, int> m_destinationToSubId;
};
