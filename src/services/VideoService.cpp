#include "VideoService.h"
#include "config/ConfigManager.h"
#include <QDebug>

VideoService* VideoService::s_instance = nullptr;

VideoService::VideoService(QObject *parent)
    : QObject(parent)
{
}

VideoService* VideoService::instance() {
    if (!s_instance) {
        s_instance = new VideoService();
    }
    return s_instance;
}

void VideoService::startCamera() {
    qInfo() << "Stub: Starting camera";
    
    // TODO: Implementation with GStreamer + WebRTC
    // 1. Create GStreamer pipeline with:
    //    - Video source (camera device)
    //    - Hardware encoder (nvh264enc, vaapih264enc, h264_amf) or software fallback
    //    - webrtcbin for WebRTC
    // 2. Post SDP offer to SFU
    // 3. Handle ICE candidates
    
    bool videoEnabled = ConfigManager::instance()->isFeatureEnabled("videoChat");
    if (!videoEnabled) {
        qWarning() << "Video chat feature is disabled";
        emit error("Video chat not yet available");
        return;
    }
    
    emit error("Video chat coming soon - media stack stubbed");
}

void VideoService::stopCamera() {
    qInfo() << "Stub: Stopping camera";
    
    if (m_cameraActive) {
        m_cameraActive = false;
        emit cameraActiveChanged();
    }
    
    // TODO: Clean up GStreamer pipeline
}

void VideoService::startScreenShare() {
    qInfo() << "Stub: Starting screen share";
    
    // TODO: Implementation with GStreamer + WebRTC
    // 1. Create GStreamer pipeline with:
    //    - Screen capture source (ximagesrc on Linux, dxgiscreencapsrc on Windows)
    //    - Hardware encoder or software fallback
    //    - webrtcbin for WebRTC
    // 2. Post SDP offer to SFU
    
    bool screenShareEnabled = ConfigManager::instance()->isFeatureEnabled("screenShare");
    if (!screenShareEnabled) {
        qWarning() << "Screen share feature is disabled";
        emit error("Screen sharing not yet available");
        return;
    }
    
    emit error("Screen sharing coming soon - media stack stubbed");
}

void VideoService::stopScreenShare() {
    qInfo() << "Stub: Stopping screen share";
    
    if (m_screenSharing) {
        m_screenSharing = false;
        emit screenSharingChanged();
    }
    
    // TODO: Clean up GStreamer pipeline
}

QStringList VideoService::getVideoDevices() {
    qInfo() << "Stub: Getting video devices";
    
    // TODO: Enumerate devices via GStreamer
    QStringList devices;
    devices << "Default Webcam";
    devices << "USB Camera";
    
    return devices;
}

void VideoService::setVideoDevice(const QString& deviceId) {
    qInfo() << "Stub: Setting video device:" << deviceId;
    
    // TODO: Update GStreamer pipeline source
}
