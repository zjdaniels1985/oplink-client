#pragma once

#include <QObject>
#include <QString>
#include "models/User.h"

class SessionStore : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool authenticated READ authenticated NOTIFY authenticatedChanged)
    Q_PROPERTY(User* currentUser READ currentUser NOTIFY currentUserChanged)
    Q_PROPERTY(QString token READ token NOTIFY tokenChanged)

public:
    static SessionStore* instance();
    
    bool authenticated() const { return !m_token.isEmpty(); }
    User* currentUser() { return m_currentUser; }
    QString token() const { return m_token; }
    
    void setToken(const QString& token);
    void setCurrentUser(User* user);
    void clear();
    
signals:
    void authenticatedChanged();
    void currentUserChanged();
    void tokenChanged();

private:
    explicit SessionStore(QObject *parent = nullptr);
    ~SessionStore() override = default;
    
    QString m_token;
    User* m_currentUser = nullptr;
    
    static SessionStore* s_instance;
};
