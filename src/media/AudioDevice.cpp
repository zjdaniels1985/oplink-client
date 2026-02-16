#include "AudioDevice.h"
#include <QDebug>

AudioDevice* AudioDevice::s_instance = nullptr;

AudioDevice::AudioDevice(QObject *parent)
    : QObject(parent)
{
}

AudioDevice* AudioDevice::instance() {
    if (!s_instance) {
        s_instance = new AudioDevice();
    }
    return s_instance;
}

QList<AudioDeviceInfo> AudioDevice::getInputDevices() {
    qInfo() << "Stub: Getting audio input devices";
    
    // TODO: Use GStreamer to enumerate audio devices
    // gst_device_monitor_get_devices()
    
    QList<AudioDeviceInfo> devices;
    
    AudioDeviceInfo device1;
    device1.id = "default";
    device1.name = "Default Microphone";
    device1.isInput = true;
    devices.append(device1);
    
    AudioDeviceInfo device2;
    device2.id = "usb-mic";
    device2.name = "USB Microphone";
    device2.isInput = true;
    devices.append(device2);
    
    return devices;
}

QList<AudioDeviceInfo> AudioDevice::getOutputDevices() {
    qInfo() << "Stub: Getting audio output devices";
    
    // TODO: Use GStreamer to enumerate audio devices
    
    QList<AudioDeviceInfo> devices;
    
    AudioDeviceInfo device1;
    device1.id = "default";
    device1.name = "Default Speakers";
    device1.isInput = false;
    devices.append(device1);
    
    AudioDeviceInfo device2;
    device2.id = "headphones";
    device2.name = "Headphones";
    device2.isInput = false;
    devices.append(device2);
    
    return devices;
}

QString AudioDevice::getDefaultInputDevice() {
    return "default";
}

QString AudioDevice::getDefaultOutputDevice() {
    return "default";
}
