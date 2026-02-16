#pragma once

#include <QObject>
#include <QString>

// Stub for GStreamer media pipeline
// Will be implemented with:
// - Audio: device -> RNNoise -> Opus -> webrtcbin -> SFU
// - Video: device -> H.264 (hw or sw) -> webrtcbin -> SFU
// - Playback: webrtcbin -> decoder -> sink

class MediaPipeline : public QObject {
    Q_OBJECT

public:
    explicit MediaPipeline(QObject *parent = nullptr);
    ~MediaPipeline() override;
    
    bool initialize();
    void cleanup();
    
    // Audio pipeline
    bool createAudioCapturePipeline(const QString& deviceId);
    bool createAudioPlaybackPipeline();
    void destroyAudioPipeline();
    
    // Video pipeline
    bool createVideoCapturePipeline(const QString& deviceId);
    bool createScreenCapturePipeline();
    void destroyVideoPipeline();
    
    // WebRTC control
    bool createWebRTCConnection();
    void closeWebRTCConnection();
    void setRemoteSDP(const QString& sdp);
    void addICECandidate(const QString& candidate);
    
signals:
    void localSDPCreated(const QString& sdp);
    void iceCandidate(const QString& candidate);
    void error(const QString& message);

private:
    // GStreamer pipeline pointers would go here
    // GstElement* m_audioPipeline = nullptr;
    // GstElement* m_videoPipeline = nullptr;
    // GstElement* m_webrtc = nullptr;
    
    bool m_initialized = false;
};
