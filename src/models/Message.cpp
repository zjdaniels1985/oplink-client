#include "Message.h"

Message::Message(QObject *parent)
    : QObject(parent)
{
}

void Message::setId(const QString& id) {
    if (m_id != id) {
        m_id = id;
        emit idChanged();
    }
}

void Message::setChannelId(const QString& channelId) {
    if (m_channelId != channelId) {
        m_channelId = channelId;
        emit channelIdChanged();
    }
}

void Message::setAuthorId(const QString& authorId) {
    if (m_authorId != authorId) {
        m_authorId = authorId;
        emit authorIdChanged();
    }
}

void Message::setAuthorName(const QString& authorName) {
    if (m_authorName != authorName) {
        m_authorName = authorName;
        emit authorNameChanged();
    }
}

void Message::setContent(const QString& content) {
    if (m_content != content) {
        m_content = content;
        emit contentChanged();
    }
}

void Message::setTimestamp(const QDateTime& timestamp) {
    if (m_timestamp != timestamp) {
        m_timestamp = timestamp;
        emit timestampChanged();
    }
}

void Message::setEdited(bool edited) {
    if (m_edited != edited) {
        m_edited = edited;
        emit editedChanged();
    }
}
