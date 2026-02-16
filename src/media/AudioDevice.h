#pragma once

#include <QObject>
#include <QList>
#include <QString>

struct AudioDeviceInfo {
    QString id;
    QString name;
    bool isInput;
};

class AudioDevice : public QObject {
    Q_OBJECT

public:
    static AudioDevice* instance();
    
    QList<AudioDeviceInfo> getInputDevices();
    QList<AudioDeviceInfo> getOutputDevices();
    
    QString getDefaultInputDevice();
    QString getDefaultOutputDevice();
    
private:
    explicit AudioDevice(QObject *parent = nullptr);
    ~AudioDevice() override = default;
    
    static AudioDevice* s_instance;
};
