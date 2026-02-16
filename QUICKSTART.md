# Quick Start Guide - OpLink Client

This guide will get you up and running with the OpLink desktop client as quickly as possible.

## Prerequisites Check

Before building, verify you have:
- [ ] Qt 6.6+ installed
- [ ] CMake 3.21+ installed
- [ ] GStreamer 1.20+ installed (with webrtcbin plugin)
- [ ] Opus library installed
- [ ] C++17 compatible compiler

See [BUILD_NOTES.md](BUILD_NOTES.md) for detailed installation instructions.

## Quick Build (5 minutes)

### Linux

```bash
# 1. Clone the repository
git clone https://github.com/zjdaniels1985/oplink-client.git
cd oplink-client

# 2. Install dependencies (Ubuntu/Debian)
sudo apt update && sudo apt install -y \
    qt6-base-dev qt6-declarative-dev qt6-websockets-dev qt6-multimedia-dev \
    libgstreamer1.0-dev libopus-dev cmake ninja-build

# 3. Build
cmake --preset=linux-ninja-release
cmake --build --preset=linux-ninja-release

# 4. Run
./build-linux-release/oplink-client
```

### Windows

```powershell
# 1. Install Qt 6.6 from https://www.qt.io/download
# 2. Install GStreamer from https://gstreamer.freedesktop.org/download/

# 3. Clone the repository
git clone https://github.com/zjdaniels1985/oplink-client.git
cd oplink-client

# 4. Build
cmake --preset=windows-ninja-release -DCMAKE_PREFIX_PATH="C:/Qt/6.6.0/msvc2019_64"
cmake --build --preset=windows-ninja-release

# 5. Run
.\build-windows-release\oplink-client.exe
```

## Configuration

1. Copy the config template:
   ```bash
   cp config.json.template config.json
   ```

2. Edit `config.json` to point to your server:
   ```json
   {
     "apiBaseUrl": "http://your-server:8080/api",
     "wsBaseUrl": "ws://your-server:8080/ws"
   }
   ```

3. Or use environment variables:
   ```bash
   export OPLINK_API_URL="http://your-server:8080/api"
   export OPLINK_WS_URL="ws://your-server:8080/ws"
   ```

## First Run

1. Launch the application
2. The login dialog will appear
3. Register a new account or login with existing credentials
4. Start chatting!

## Troubleshooting

**Qt not found?**
```bash
export Qt6_DIR=/path/to/Qt/6.6.0/gcc_64/lib/cmake/Qt6
```

**GStreamer not found?**
```bash
# Linux
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig

# Windows
$env:GSTREAMER_1_0_ROOT_MSVC_X86_64 = "C:\gstreamer\1.0\msvc_x86_64"
```

**Build fails?**
- Check CMake version: `cmake --version` (need 3.21+)
- Verify Qt installation: `qmake6 --version` or `qmake --version`
- See full build documentation: [BUILD_NOTES.md](BUILD_NOTES.md)

## Features Available

### ✅ Working Now
- User authentication (register/login)
- Real-time messaging
- Channel browsing
- Server/channel navigation
- User presence indicators
- Dark theme UI

### 🚧 Coming Soon (Stubbed)
- Voice chat (media stack ready, needs SFU integration)
- Video chat (hardware encoding configured)
- Screen sharing
- Push-to-talk
- Noise suppression (RNNoise ready)

## Development

Want to contribute? See the main [README.md](README.md) for architecture details.

### Quick Dev Setup
```bash
# Debug build for development
cmake --preset=linux-ninja-debug
cmake --build --preset=linux-ninja-debug

# Run with debug output
QT_LOGGING_RULES="*.debug=true" ./build-linux-debug/oplink-client
```

## Need Help?

- Read the [README.md](README.md) for full documentation
- Check [BUILD_NOTES.md](BUILD_NOTES.md) for detailed build instructions
- File an issue: [github.com/zjdaniels1985/oplink-client/issues](https://github.com/zjdaniels1985/oplink-client/issues)
- Server setup: [github.com/zjdaniels1985/oplink-server](https://github.com/zjdaniels1985/oplink-server)

---

**OpLink** - Mission Critical Gaming Communications
