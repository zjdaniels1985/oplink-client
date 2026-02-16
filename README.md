# OpLink Client

<div align="center">
  <h1>OPLINK</h1>
  <p><strong>OperationsLink - Mission Critical Gaming Communications</strong></p>
  <p>Cross-platform desktop client built with Qt 6, QML, and C++17</p>
</div>

---

## 🎯 Features

- ✅ **Real-time Messaging** - REST API + WebSocket/STOMP for instant communication
- ✅ **Cross-Platform** - Native support for Linux and Windows
- ✅ **Modern UI** - Discord-like interface built with QML
- ✅ **Authentication** - Integrated with Spring Boot backend (/api/auth/*)
- 🚧 **Voice Chat** - Media stack stubbed with GStreamer + WebRTC + RNNoise + Opus
- 🚧 **Video Chat** - Hardware-accelerated encoding support (NVIDIA/Intel/AMD)
- 🚧 **Screen Sharing** - Coming soon

## 🛠️ Tech Stack

- **Qt 6.6+** - Cross-platform application framework
- **C++17** - Modern C++ standards
- **QML** - Declarative UI language
- **GStreamer 1.20+** - Media framework with webrtcbin
- **RNNoise** - Audio noise suppression preprocessing
- **Opus** - Audio codec
- **WebSockets** - STOMP protocol for real-time updates
- **CMake 3.21+** - Build system with presets

## 📋 Requirements

### Common Requirements
- **Qt 6.6+** with modules: Core, Quick, Qml, Network, WebSockets, Multimedia, Concurrent
- **CMake 3.21+**
- **Ninja** build system (recommended)
- **GStreamer 1.20+** with webrtc plugin
- **Opus 1.3+**
- **RNNoise** (optional but recommended)

### Linux
- GCC 9+ or Clang 10+
- pkg-config
- Development packages:
  ```bash
  sudo apt update
  sudo apt install -y \
    qt6-base-dev qt6-declarative-dev qt6-websockets-dev \
    qt6-multimedia-dev libqt6concurrent6 \
    cmake ninja-build pkg-config \
    libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev \
    gstreamer1.0-plugins-good gstreamer1.0-plugins-bad \
    gstreamer1.0-nice gstreamer1.0-libav \
    libopus-dev librnnoise-dev
  ```

### Windows
- **MSVC 2019+** or **MinGW-w64**
- **Visual Studio 2019+** (recommended for MSVC)
- Install **Qt 6.6+** from [qt.io](https://www.qt.io/download) or use `aqt`:
  ```bash
  pip install aqt
  aqt install-qt windows desktop 6.6.0 win64_msvc2019_64
  ```
- Install **GStreamer** from [gstreamer.freedesktop.org](https://gstreamer.freedesktop.org/download/)
  - Choose "Complete" installation to get all plugins including webrtcbin
- **Opus** and **RNNoise** can be built manually or installed via **vcpkg**:
  ```bash
  vcpkg install opus:x64-windows rnnoise:x64-windows
  ```

### Optional: vcpkg for Dependency Management
You can use vcpkg to install dependencies:
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh  # or bootstrap-vcpkg.bat on Windows
./vcpkg install opus rnnoise
```

## 🚀 Building

### Using CMake Presets (Recommended)

#### Linux
```bash
git clone https://github.com/zjdaniels1985/oplink-client.git
cd oplink-client

# Debug build
cmake --preset=linux-ninja-debug
cmake --build --preset=linux-ninja-debug

# Release build
cmake --preset=linux-ninja-release
cmake --build --preset=linux-ninja-release
```

#### Windows
```bash
git clone https://github.com/zjdaniels1985/oplink-client.git
cd oplink-client

# Debug build
cmake --preset=windows-ninja-debug -DCMAKE_PREFIX_PATH="C:/Qt/6.6.0/msvc2019_64"
cmake --build --preset=windows-ninja-debug

# Release build
cmake --preset=windows-ninja-release -DCMAKE_PREFIX_PATH="C:/Qt/6.6.0/msvc2019_64"
cmake --build --preset=windows-ninja-release
```

### Manual Build (Alternative)

```bash
mkdir build && cd build

# Linux
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release

# Windows (adjust Qt path)
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH="C:/Qt/6.6.0/msvc2019_64" \
  -DCMAKE_TOOLCHAIN_FILE="path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"

cmake --build .
```

## 🎮 Running

### Linux
```bash
# From build directory
./oplink-client

# Or install and run
cmake --install . --prefix ~/.local
~/.local/bin/oplink-client
```

### Windows
```bash
# From build directory
oplink-client.exe

# Ensure Qt DLLs and GStreamer are in PATH or copy them to executable directory
```

## ⚙️ Configuration

OpLink uses a `config.json` file for configuration. On first run, copy the template:

```bash
cp config.json.template config.json
```

### config.json Structure
```json
{
  "apiBaseUrl": "http://localhost:8080/api",
  "wsBaseUrl": "ws://localhost:8080/ws",
  "sfuSignalUrl": "http://localhost:8080/api/voice",
  "turn": {
    "enabled": false,
    "urls": ["turn:turn.example.com:3478"],
    "username": "",
    "credential": ""
  },
  "features": {
    "sfuSignaling": false,
    "voiceChat": false,
    "videoChat": false,
    "screenShare": false
  },
  "audio": {
    "echoCancellation": true,
    "noiseSuppression": true,
    "autoGainControl": true,
    "rnnoiseEnabled": true,
    "opusBitrate": 64000,
    "opusFrameSize": 20
  },
  "video": {
    "preferredCodec": "h264",
    "maxWidth": 1920,
    "maxHeight": 1080,
    "maxFramerate": 30,
    "hardwareAcceleration": true
  }
}
```

### Environment Variable Overrides
You can override config values with environment variables:

```bash
# Linux/macOS
export OPLINK_API_URL="http://myserver:8080/api"
export OPLINK_WS_URL="ws://myserver:8080/ws"
export OPLINK_SFU_URL="http://myserver:8080/api/voice"

# Windows (PowerShell)
$env:OPLINK_API_URL="http://myserver:8080/api"
$env:OPLINK_WS_URL="ws://myserver:8080/ws"
$env:OPLINK_SFU_URL="http://myserver:8080/api/voice"
```

### Config File Locations
OpLink searches for `config.json` in the following order:
1. Current working directory: `./config.json`
2. Executable directory: `<exe-path>/config.json`
3. User config directory:
   - Linux: `~/.config/OpLink/config.json`
   - Windows: `%APPDATA%/OpLink/config.json`

## 📚 Architecture

### Project Structure
```
oplink-client/
├── CMakeLists.txt          # Main build configuration
├── CMakePresets.json       # CMake presets for Linux/Windows
├── config.json.template    # Configuration template
├── src/
│   ├── main.cpp            # Application entry point
│   ├── config/
│   │   ├── ConfigManager.h/cpp   # Config loading and management
│   ├── models/
│   │   ├── User.h/cpp
│   │   ├── Server.h/cpp
│   │   ├── Channel.h/cpp
│   │   ├── Message.h/cpp
│   │   └── Presence.h/cpp
│   ├── stores/
│   │   ├── SessionStore.h/cpp    # Auth state
│   │   ├── ServerStore.h/cpp     # Server data
│   │   ├── ChannelStore.h/cpp    # Channel data
│   │   └── MessageStore.h/cpp    # Message history with pagination
│   ├── services/
│   │   ├── HttpClient.h/cpp      # REST API client
│   │   ├── WsClient.h/cpp        # STOMP WebSocket client
│   │   ├── AuthService.h/cpp     # Authentication
│   │   ├── MessageService.h/cpp  # Messaging
│   │   ├── PresenceService.h/cpp # User presence
│   │   ├── VoiceService.h/cpp    # Voice (stubbed)
│   │   └── VideoService.h/cpp    # Video (stubbed)
│   ├── media/
│   │   ├── MediaPipeline.h/cpp      # GStreamer pipeline (stub)
│   │   ├── AudioDevice.h/cpp        # Device enumeration (stub)
│   │   └── RNNoiseProcessor.h/cpp   # RNNoise wrapper (stub)
│   └── ui/qml/
│       ├── main.qml              # Main window
│       ├── Theme.qml             # Dark theme singleton
│       ├── components/
│       │   ├── ServerList.qml
│       │   ├── ChannelList.qml
│       │   ├── MemberList.qml
│       │   ├── StatusBar.qml
│       │   └── LoginDialog.qml
│       └── views/
│           ├── ServerView.qml
│           └── ChatView.qml
└── qml.qrc                 # QML resources
```

### Backend Integration
The client integrates with the Spring Boot backend:
- **Auth**: `/api/auth/register`, `/api/auth/login`, `/api/auth/me`
- **Messaging**: 
  - REST: `/api/channels/{id}/messages` (GET for history, POST to send)
  - WebSocket: `/topic/channels/{id}/messages` (real-time updates)
- **Presence**: `/topic/servers/{id}/presence` (WebSocket)
- **Voice (stubbed)**: `/api/voice/{channelId}/offer`, `/api/voice/{channelId}/ice`

### Media Stack (Stubbed)
The media stack is prepared but not fully implemented:
- **Audio Pipeline**: `device → RNNoise → Opus → webrtcbin → SFU`
- **Video Pipeline**: `device → H.264 (hw/sw) → webrtcbin → SFU`
- **Hardware Encoders**: nvh264enc (NVIDIA), vaapih264enc (Intel/AMD Linux), h264_amf (AMD Windows)
- **Signaling**: Placeholder calls to SFU endpoints (feature-flagged)

## 🔧 Development

### Code Style
- C++17 standard
- Qt naming conventions (camelCase for methods, PascalCase for classes)
- Use Qt containers (QList, QString, QMap) for Qt integration

### Adding New Features
1. Update models in `src/models/` if new data types needed
2. Add business logic in `src/services/`
3. Update stores in `src/stores/` for state management
4. Create/update QML components in `src/ui/qml/`

### Debugging
Enable debug output:
```bash
QT_LOGGING_RULES="*.debug=true" ./oplink-client
```

## 🤝 Contributing

OpLink is a personal project for gaming with friends. Contributions welcome!

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## 📄 License

MIT License - See LICENSE file

## 🔗 Links

- **OpLink Server Repository**: [github.com/zjdaniels1985/oplink-server](https://github.com/zjdaniels1985/oplink-server)
- **Issue Tracker**: [github.com/zjdaniels1985/oplink-client/issues](https://github.com/zjdaniels1985/oplink-client/issues)
- **Qt Documentation**: [doc.qt.io](https://doc.qt.io/)
- **GStreamer Documentation**: [gstreamer.freedesktop.org/documentation](https://gstreamer.freedesktop.org/documentation/)

## 🐛 Known Issues / TODO

- [ ] Full GStreamer media pipeline implementation
- [ ] WebRTC SFU signaling integration
- [ ] Voice activity detection (VAD)
- [ ] Push-to-talk support
- [ ] Video rendering in QML
- [ ] Screen sharing implementation
- [ ] User settings persistence
- [ ] Message editing/deletion
- [ ] Rich message formatting
- [ ] File uploads/attachments
- [ ] Notification system
- [ ] System tray integration

---

**OpLink** - Where tactical communication meets gaming excellence