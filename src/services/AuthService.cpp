#include "AuthService.h"
#include "config/ConfigManager.h"
#include "stores/SessionStore.h"
#include <QJsonObject>
#include <QDebug>

AuthService* AuthService::s_instance = nullptr;

AuthService::AuthService(QObject *parent)
    : QObject(parent)
    , m_httpClient(new HttpClient(this))
{
    m_httpClient->setBaseUrl(ConfigManager::instance()->apiBaseUrl());
}

AuthService* AuthService::instance() {
    if (!s_instance) {
        s_instance = new AuthService();
    }
    return s_instance;
}

void AuthService::registerUser(const QString& username,
                               const QString& email,
                               const QString& password) {
    QJsonObject data;
    data["username"] = username;
    data["email"] = email;
    data["password"] = password;
    
    m_httpClient->post("/auth/register", data, 
        [this](QJsonDocument doc, QString error) {
            if (!error.isEmpty()) {
                emit registerFailed(error);
                return;
            }
            
            emit registerSuccess();
        });
}

void AuthService::login(const QString& username, const QString& password) {
    QJsonObject data;
    data["username"] = username;
    data["password"] = password;
    
    m_httpClient->post("/auth/login", data,
        [this](QJsonDocument doc, QString error) {
            if (!error.isEmpty()) {
                emit loginFailed(error);
                return;
            }
            
            QJsonObject response = doc.object();
            QString token = response.value("token").toString();
            
            if (token.isEmpty()) {
                emit loginFailed("No token in response");
                return;
            }
            
            // Parse user data
            QJsonObject userData = response.value("user").toObject();
            User* user = new User();
            user->setId(userData.value("id").toString());
            user->setUsername(userData.value("username").toString());
            user->setEmail(userData.value("email").toString());
            user->setAvatar(userData.value("avatar").toString());
            
            // Store session
            SessionStore::instance()->setToken(token);
            SessionStore::instance()->setCurrentUser(user);
            m_httpClient->setAuthToken(token);
            
            emit loginSuccess(token, user);
        });
}

void AuthService::logout() {
    SessionStore::instance()->clear();
    m_httpClient->setAuthToken(QString());
}

void AuthService::fetchCurrentUser() {
    QString token = SessionStore::instance()->token();
    if (token.isEmpty()) {
        emit userFetchFailed("Not authenticated");
        return;
    }
    
    m_httpClient->get("/auth/me",
        [this](QJsonDocument doc, QString error) {
            if (!error.isEmpty()) {
                emit userFetchFailed(error);
                return;
            }
            
            QJsonObject userData = doc.object();
            User* user = new User();
            user->setId(userData.value("id").toString());
            user->setUsername(userData.value("username").toString());
            user->setEmail(userData.value("email").toString());
            user->setAvatar(userData.value("avatar").toString());
            
            SessionStore::instance()->setCurrentUser(user);
            emit userFetched(user);
        });
}
