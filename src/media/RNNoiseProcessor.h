#pragma once

#include <QObject>

// Stub for RNNoise audio preprocessing
// Will process audio samples before Opus encoding

class RNNoiseProcessor : public QObject {
    Q_OBJECT

public:
    explicit RNNoiseProcessor(QObject *parent = nullptr);
    ~RNNoiseProcessor() override;
    
    bool initialize();
    void cleanup();
    
    // Process audio frame (stub)
    void processFrame(float* audioData, int frameSize);
    
private:
    // RNNoise state pointer would go here
    // DenoiseState* m_state = nullptr;
    
    bool m_initialized = false;
};
