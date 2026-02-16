#pragma once

#include <QObject>
#include <QString>

// Stubbed VoiceService for future WebRTC implementation
// Will handle audio capture, RNNoise preprocessing, Opus encoding,
// WebRTC connections to SFU, and audio playback

class VoiceService : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged)
    Q_PROPERTY(bool deafened READ deafened WRITE setDeafened NOTIFY deafenedChanged)

public:
    static VoiceService* instance();
    
    bool connected() const { return m_connected; }
    bool muted() const { return m_muted; }
    bool deafened() const { return m_deafened; }
    
    void setMuted(bool muted);
    void setDeafened(bool deafened);
    
    // Stubbed methods - to be implemented with GStreamer + WebRTC
    Q_INVOKABLE void joinVoiceChannel(const QString& channelId);
    Q_INVOKABLE void leaveVoiceChannel();
    Q_INVOKABLE QStringList getAudioInputDevices();
    Q_INVOKABLE QStringList getAudioOutputDevices();
    Q_INVOKABLE void setAudioInputDevice(const QString& deviceId);
    Q_INVOKABLE void setAudioOutputDevice(const QString& deviceId);
    
signals:
    void connectedChanged();
    void mutedChanged();
    void deafenedChanged();
    void error(const QString& message);

private:
    explicit VoiceService(QObject *parent = nullptr);
    ~VoiceService() override = default;
    
    bool m_connected = false;
    bool m_muted = false;
    bool m_deafened = false;
    
    static VoiceService* s_instance;
};
