#include "VoiceService.h"
#include "config/ConfigManager.h"
#include <QDebug>

VoiceService* VoiceService::s_instance = nullptr;

VoiceService::VoiceService(QObject *parent)
    : QObject(parent)
{
}

VoiceService* VoiceService::instance() {
    if (!s_instance) {
        s_instance = new VoiceService();
    }
    return s_instance;
}

void VoiceService::setMuted(bool muted) {
    if (m_muted != muted) {
        m_muted = muted;
        qInfo() << "Voice muted:" << m_muted;
        emit mutedChanged();
        
        // TODO: Mute/unmute audio capture pipeline
    }
}

void VoiceService::setDeafened(bool deafened) {
    if (m_deafened != deafened) {
        m_deafened = deafened;
        qInfo() << "Voice deafened:" << m_deafened;
        emit deafenedChanged();
        
        // If deafened, also mute
        if (m_deafened && !m_muted) {
            setMuted(true);
        }
        
        // TODO: Mute/unmute audio playback pipeline
    }
}

void VoiceService::joinVoiceChannel(const QString& channelId) {
    qInfo() << "Stub: Joining voice channel" << channelId;
    
    // TODO: Implementation with GStreamer + WebRTC
    // 1. Create GStreamer pipeline with:
    //    - Audio source (device)
    //    - RNNoise filter
    //    - Opus encoder
    //    - webrtcbin for WebRTC
    // 2. Post SDP offer to SFU signaling endpoint
    // 3. Handle ICE candidates
    // 4. Set up audio playback pipeline
    
    bool sfuEnabled = ConfigManager::instance()->isFeatureEnabled("sfuSignaling");
    if (!sfuEnabled) {
        qWarning() << "SFU signaling feature is disabled";
        emit error("Voice chat not yet available");
        return;
    }
    
    // Placeholder signaling
    QString sfuUrl = ConfigManager::instance()->sfuSignalUrl();
    qInfo() << "Would POST to:" << sfuUrl + "/api/voice/" + channelId + "/offer";
    
    emit error("Voice chat coming soon - media stack stubbed");
}

void VoiceService::leaveVoiceChannel() {
    qInfo() << "Stub: Leaving voice channel";
    
    if (m_connected) {
        m_connected = false;
        emit connectedChanged();
    }
    
    // TODO: Clean up GStreamer pipeline
}

QStringList VoiceService::getAudioInputDevices() {
    qInfo() << "Stub: Getting audio input devices";
    
    // TODO: Enumerate devices via GStreamer
    QStringList devices;
    devices << "Default Microphone";
    devices << "USB Microphone";
    
    return devices;
}

QStringList VoiceService::getAudioOutputDevices() {
    qInfo() << "Stub: Getting audio output devices";
    
    // TODO: Enumerate devices via GStreamer
    QStringList devices;
    devices << "Default Speakers";
    devices << "Headphones";
    
    return devices;
}

void VoiceService::setAudioInputDevice(const QString& deviceId) {
    qInfo() << "Stub: Setting audio input device:" << deviceId;
    
    // TODO: Update GStreamer pipeline source
}

void VoiceService::setAudioOutputDevice(const QString& deviceId) {
    qInfo() << "Stub: Setting audio output device:" << deviceId;
    
    // TODO: Update GStreamer pipeline sink
}
