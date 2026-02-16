#pragma once

#include <QObject>
#include <QString>

// Stubbed VideoService for future WebRTC video implementation
// Will handle video capture, hardware encoding, screen sharing,
// WebRTC connections to SFU, and video rendering

class VideoService : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool cameraActive READ cameraActive NOTIFY cameraActiveChanged)
    Q_PROPERTY(bool screenSharing READ screenSharing NOTIFY screenSharingChanged)

public:
    static VideoService* instance();
    
    bool cameraActive() const { return m_cameraActive; }
    bool screenSharing() const { return m_screenSharing; }
    
    // Stubbed methods - to be implemented with GStreamer + WebRTC
    Q_INVOKABLE void startCamera();
    Q_INVOKABLE void stopCamera();
    Q_INVOKABLE void startScreenShare();
    Q_INVOKABLE void stopScreenShare();
    Q_INVOKABLE QStringList getVideoDevices();
    Q_INVOKABLE void setVideoDevice(const QString& deviceId);
    
signals:
    void cameraActiveChanged();
    void screenSharingChanged();
    void error(const QString& message);

private:
    explicit VideoService(QObject *parent = nullptr);
    ~VideoService() override = default;
    
    bool m_cameraActive = false;
    bool m_screenSharing = false;
    
    static VideoService* s_instance;
};
