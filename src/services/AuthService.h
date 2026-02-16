#pragma once

#include <QObject>
#include "HttpClient.h"
#include "models/User.h"

class AuthService : public QObject {
    Q_OBJECT

public:
    static AuthService* instance();
    
    void registerUser(const QString& username, 
                     const QString& email,
                     const QString& password);
    
    void login(const QString& username, const QString& password);
    void logout();
    void fetchCurrentUser();
    
signals:
    void loginSuccess(const QString& token, User* user);
    void loginFailed(const QString& error);
    void registerSuccess();
    void registerFailed(const QString& error);
    void userFetched(User* user);
    void userFetchFailed(const QString& error);

private:
    explicit AuthService(QObject *parent = nullptr);
    ~AuthService() override = default;
    
    HttpClient* m_httpClient;
    
    static AuthService* s_instance;
};
