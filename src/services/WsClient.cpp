#include "WsClient.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>

WsClient::WsClient(QObject *parent)
    : QObject(parent)
    , m_webSocket(new QWebSocket())
    , m_reconnectTimer(new QTimer(this))
{
    QObject::connect(m_webSocket, &QWebSocket::connected,
                     this, &WsClient::onConnected);
    QObject::connect(m_webSocket, &QWebSocket::disconnected,
                     this, &WsClient::onDisconnected);
    QObject::connect(m_webSocket, &QWebSocket::textMessageReceived,
                     this, &WsClient::onTextMessageReceived);
    QObject::connect(m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
                     this, &WsClient::onError);
    
    m_reconnectTimer->setSingleShot(true);
    QObject::connect(m_reconnectTimer, &QTimer::timeout,
                     this, &WsClient::attemptReconnect);
}

WsClient::~WsClient() {
    m_shouldReconnect = false;
    if (m_webSocket) {
        m_webSocket->close();
        delete m_webSocket;
    }
}

void WsClient::setUrl(const QString& url) {
    m_url = url;
}

void WsClient::setAuthToken(const QString& token) {
    m_authToken = token;
}

void WsClient::connect() {
    if (m_url.isEmpty()) {
        qWarning() << "WebSocket URL not set";
        return;
    }
    
    m_shouldReconnect = true;
    m_reconnectAttempts = 0;
    
    qInfo() << "Connecting to WebSocket:" << m_url;
    
    QNetworkRequest request(m_url);
    if (!m_authToken.isEmpty()) {
        request.setRawHeader("Authorization", ("Bearer " + m_authToken).toUtf8());
    }
    
    m_webSocket->open(request);
}

void WsClient::disconnect() {
    m_shouldReconnect = false;
    m_reconnectTimer->stop();
    
    if (m_webSocket->state() == QAbstractSocket::ConnectedState) {
        // Send STOMP DISCONNECT
        sendStompFrame("DISCONNECT", {});
        m_webSocket->close();
    }
}

void WsClient::onConnected() {
    qInfo() << "WebSocket connected";
    m_connected = true;
    m_reconnectAttempts = 0;
    emit connectedChanged();
    
    // Send STOMP CONNECT frame
    QMap<QString, QString> headers;
    headers["accept-version"] = "1.2";
    headers["heart-beat"] = "10000,10000";
    
    if (!m_authToken.isEmpty()) {
        headers["Authorization"] = "Bearer " + m_authToken;
    }
    
    sendStompFrame("CONNECT", headers);
}

void WsClient::onDisconnected() {
    qInfo() << "WebSocket disconnected";
    m_connected = false;
    emit connectedChanged();
    
    if (m_shouldReconnect) {
        attemptReconnect();
    }
}

void WsClient::onTextMessageReceived(const QString& message) {
    processStompFrame(message);
}

void WsClient::onError(QAbstractSocket::SocketError error) {
    QString errorMsg = m_webSocket->errorString();
    qWarning() << "WebSocket error:" << error << errorMsg;
    emit connectionError(errorMsg);
}

void WsClient::attemptReconnect() {
    if (!m_shouldReconnect) {
        return;
    }
    
    m_reconnectAttempts++;
    int delay = qMin(30000, 1000 * m_reconnectAttempts);
    
    qInfo() << "Attempting to reconnect in" << delay << "ms (attempt" << m_reconnectAttempts << ")";
    m_reconnectTimer->start(delay);
    
    connect();
}

void WsClient::subscribe(const QString& destination,
                         std::function<void(QJsonObject)> callback) {
    if (!m_connected) {
        qWarning() << "Cannot subscribe: not connected";
        return;
    }
    
    int subId = m_subscriptionId++;
    m_destinationToSubId[destination] = subId;
    m_subscriptions[destination] = callback;
    
    QMap<QString, QString> headers;
    headers["id"] = QString::number(subId);
    headers["destination"] = destination;
    
    sendStompFrame("SUBSCRIBE", headers);
    qInfo() << "Subscribed to:" << destination;
}

void WsClient::unsubscribe(const QString& destination) {
    if (!m_destinationToSubId.contains(destination)) {
        return;
    }
    
    int subId = m_destinationToSubId[destination];
    m_destinationToSubId.remove(destination);
    m_subscriptions.remove(destination);
    
    QMap<QString, QString> headers;
    headers["id"] = QString::number(subId);
    
    sendStompFrame("UNSUBSCRIBE", headers);
    qInfo() << "Unsubscribed from:" << destination;
}

void WsClient::send(const QString& destination, const QJsonObject& payload) {
    if (!m_connected) {
        qWarning() << "Cannot send: not connected";
        return;
    }
    
    QJsonDocument doc(payload);
    QString body = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    
    QMap<QString, QString> headers;
    headers["destination"] = destination;
    headers["content-type"] = "application/json";
    
    sendStompFrame("SEND", headers, body);
}

void WsClient::sendStompFrame(const QString& command,
                               const QMap<QString, QString>& headers,
                               const QString& body) {
    QString frame = command + "\n";
    
    for (auto it = headers.begin(); it != headers.end(); ++it) {
        frame += it.key() + ":" + it.value() + "\n";
    }
    
    frame += "\n";
    if (!body.isEmpty()) {
        frame += body;
    }
    frame += "\0";
    
    m_webSocket->sendTextMessage(frame);
}

void WsClient::processStompFrame(const QString& frame) {
    QStringList lines = frame.split('\n');
    if (lines.isEmpty()) {
        return;
    }
    
    QString command = lines[0];
    
    if (command == "CONNECTED") {
        qInfo() << "STOMP CONNECTED";
        return;
    }
    
    if (command == "MESSAGE") {
        // Parse headers
        QMap<QString, QString> headers;
        int bodyStart = 1;
        for (int i = 1; i < lines.size(); ++i) {
            if (lines[i].isEmpty()) {
                bodyStart = i + 1;
                break;
            }
            int colonPos = lines[i].indexOf(':');
            if (colonPos > 0) {
                QString key = lines[i].left(colonPos);
                QString value = lines[i].mid(colonPos + 1);
                headers[key] = value;
            }
        }
        
        // Get destination
        QString destination = headers.value("destination");
        if (destination.isEmpty()) {
            return;
        }
        
        // Get body
        QString body;
        for (int i = bodyStart; i < lines.size(); ++i) {
            if (lines[i] == "\0") {
                break;
            }
            if (i > bodyStart) {
                body += "\n";
            }
            body += lines[i];
        }
        
        // Parse JSON payload
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(body.toUtf8(), &parseError);
        
        if (parseError.error != QJsonParseError::NoError) {
            qWarning() << "Failed to parse STOMP message body:" << parseError.errorString();
            return;
        }
        
        if (!doc.isObject()) {
            qWarning() << "STOMP message body is not a JSON object";
            return;
        }
        
        // Call subscription callback
        if (m_subscriptions.contains(destination)) {
            m_subscriptions[destination](doc.object());
        }
    }
    
    if (command == "ERROR") {
        qWarning() << "STOMP ERROR:" << frame;
    }
}
