#include "SessionStore.h"

SessionStore* SessionStore::s_instance = nullptr;

SessionStore::SessionStore(QObject *parent)
    : QObject(parent)
{
}

SessionStore* SessionStore::instance() {
    if (!s_instance) {
        s_instance = new SessionStore();
    }
    return s_instance;
}

void SessionStore::setToken(const QString& token) {
    if (m_token != token) {
        m_token = token;
        emit tokenChanged();
        emit authenticatedChanged();
    }
}

void SessionStore::setCurrentUser(User* user) {
    if (m_currentUser != user) {
        if (m_currentUser) {
            m_currentUser->deleteLater();
        }
        m_currentUser = user;
        if (m_currentUser) {
            m_currentUser->setParent(this);
        }
        emit currentUserChanged();
    }
}

void SessionStore::clear() {
    setToken(QString());
    setCurrentUser(nullptr);
}
