# Build Notes for OpLink Client

## Build Environment Setup

This document provides detailed instructions for setting up a complete build environment for the OpLink Qt 6 QML desktop client.

## Prerequisites Summary

### Required Components
1. **Qt 6.6+** with the following modules:
   - Qt6::Core
   - Qt6::Quick
   - Qt6::Qml
   - Qt6::Network
   - Qt6::WebSockets
   - Qt6::Multimedia
   - Qt6::Concurrent

2. **GStreamer 1.20+** with plugins:
   - gstreamer-1.0
   - gstreamer-app-1.0
   - gstreamer-video-1.0
   - gstreamer-audio-1.0
   - gstreamer-webrtc-1.0 (webrtcbin plugin)
   - Additional plugins: good, bad, nice, libav

3. **Opus 1.3+** - Audio codec library

4. **RNNoise** (optional) - Noise suppression library

5. **Build Tools**:
   - CMake 3.21+
   - Ninja (recommended) or Make
   - C++17 compiler (GCC 9+, Clang 10+, or MSVC 2019+)
   - pkg-config (Linux/macOS)

---

## Linux Build Setup

### Ubuntu/Debian

```bash
# Update package list
sudo apt update

# Install Qt 6 (from Ubuntu 22.04+ repos, or use official Qt installer)
sudo apt install -y \
    qt6-base-dev \
    qt6-declarative-dev \
    qt6-websockets-dev \
    qt6-multimedia-dev \
    libqt6concurrent6 \
    qml6-module-qtquick \
    qml6-module-qtquick-controls \
    qml6-module-qtquick-layouts \
    qml6-module-qtquick-window

# Install GStreamer
sudo apt install -y \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    libgstreamer-plugins-bad1.0-dev \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-libav \
    gstreamer1.0-nice \
    gstreamer1.0-tools

# Install Opus
sudo apt install -y libopus-dev

# Install RNNoise (may need to build from source or use a PPA)
# Option 1: Try package manager
sudo apt install -y librnnoise-dev

# Option 2: Build from source if not available
# git clone https://github.com/xiph/rnnoise.git
# cd rnnoise
# ./autogen.sh
# ./configure
# make
# sudo make install

# Install build tools
sudo apt install -y \
    cmake \
    ninja-build \
    pkg-config \
    build-essential

# Verify installations
cmake --version
pkg-config --modversion Qt6Core
pkg-config --modversion gstreamer-1.0
pkg-config --modversion opus
```

### Fedora/RHEL

```bash
# Install Qt 6
sudo dnf install -y \
    qt6-qtbase-devel \
    qt6-qtdeclarative-devel \
    qt6-qtwebsockets-devel \
    qt6-qtmultimedia-devel

# Install GStreamer
sudo dnf install -y \
    gstreamer1-devel \
    gstreamer1-plugins-base-devel \
    gstreamer1-plugins-good \
    gstreamer1-plugins-bad-free \
    gstreamer1-plugins-ugly-free

# Install Opus
sudo dnf install -y opus-devel

# Install build tools
sudo dnf install -y \
    cmake \
    ninja-build \
    gcc-c++
```

### Arch Linux

```bash
# Install Qt 6
sudo pacman -S qt6-base qt6-declarative qt6-websockets qt6-multimedia

# Install GStreamer
sudo pacman -S gstreamer gst-plugins-base gst-plugins-good \
               gst-plugins-bad gst-plugins-ugly gst-libav

# Install Opus and RNNoise
sudo pacman -S opus rnnoise

# Install build tools
sudo pacman -S cmake ninja base-devel
```

---

## Windows Build Setup

### Option 1: Using Official Qt Installer

1. **Download Qt Online Installer**
   - Visit [qt.io/download](https://www.qt.io/download)
   - Download the open-source installer
   - Run the installer and select:
     - Qt 6.6.0 (or later)
     - MSVC 2019 64-bit or MinGW components
     - Qt Quick modules

2. **Install Visual Studio 2019 or 2022**
   - Download from [visualstudio.microsoft.com](https://visualstudio.microsoft.com/)
   - Install with "Desktop development with C++" workload
   - Ensure CMake and Ninja are included

3. **Install GStreamer**
   - Download from [gstreamer.freedesktop.org/download](https://gstreamer.freedesktop.org/download/)
   - Choose the **Complete** MSVC package (includes all plugins)
   - Install both runtime and development packages
   - Add GStreamer `bin` directory to PATH:
     ```
     C:\gstreamer\1.0\msvc_x86_64\bin
     ```

4. **Install Opus and RNNoise via vcpkg**
   ```powershell
   # Clone vcpkg
   git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
   cd C:\vcpkg
   .\bootstrap-vcpkg.bat
   
   # Install dependencies
   .\vcpkg install opus:x64-windows
   .\vcpkg install rnnoise:x64-windows
   
   # Integrate with Visual Studio (optional)
   .\vcpkg integrate install
   ```

### Option 2: Using aqt (Automated Qt Installer)

```powershell
# Install Python and pip first
pip install aqtinstall

# Install Qt 6.6.0 for Windows with MSVC 2019
aqt install-qt windows desktop 6.6.0 win64_msvc2019_64

# Set Qt path
$env:Qt6_DIR = "C:\Qt\6.6.0\msvc2019_64"
```

---

## macOS Build Setup

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install Qt 6
brew install qt@6

# Install GStreamer
brew install gstreamer gst-plugins-base gst-plugins-good \
             gst-plugins-bad gst-plugins-ugly gst-libav

# Install Opus and RNNoise
brew install opus
# RNNoise may need to be built from source

# Install build tools
brew install cmake ninja

# Link Qt
echo 'export PATH="/usr/local/opt/qt@6/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

---

## Building the Project

### Linux/macOS

```bash
# Clone repository
git clone https://github.com/zjdaniels1985/oplink-client.git
cd oplink-client

# Create config from template
cp config.json.template config.json

# Configure with CMake preset
cmake --preset=linux-ninja-release

# Build
cmake --build --preset=linux-ninja-release

# Run
./build-linux-release/oplink-client
```

### Windows (PowerShell)

```powershell
# Clone repository
git clone https://github.com/zjdaniels1985/oplink-client.git
cd oplink-client

# Create config from template
Copy-Item config.json.template config.json

# Configure with CMake
cmake --preset=windows-ninja-release `
  -DCMAKE_PREFIX_PATH="C:/Qt/6.6.0/msvc2019_64" `
  -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"

# Build
cmake --build --preset=windows-ninja-release

# Run
.\build-windows-release\oplink-client.exe
```

### Manual Build (without presets)

```bash
mkdir build && cd build

# Linux
cmake .. -G Ninja \
  -DCMAKE_BUILD_TYPE=Release

# Windows
cmake .. -G Ninja ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_PREFIX_PATH="C:/Qt/6.6.0/msvc2019_64" ^
  -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"

# Build
cmake --build .

# Install (optional)
cmake --install . --prefix ~/.local  # Linux
cmake --install . --prefix "C:/Program Files/OpLink"  # Windows
```

---

## Troubleshooting

### Qt not found
```bash
# Set Qt path manually
export Qt6_DIR=/path/to/qt/6.6.0/gcc_64/lib/cmake/Qt6
# or on Windows
$env:Qt6_DIR = "C:\Qt\6.6.0\msvc2019_64\lib\cmake\Qt6"
```

### GStreamer not found
```bash
# Linux: Ensure pkg-config can find GStreamer
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig

# Windows: Set GStreamer environment
$env:GSTREAMER_1_0_ROOT_MSVC_X86_64 = "C:\gstreamer\1.0\msvc_x86_64"
```

### RNNoise not found (optional dependency)
RNNoise is optional. The build will proceed without it, but noise suppression won't be available. To build RNNoise from source:

```bash
git clone https://github.com/xiph/rnnoise.git
cd rnnoise
./autogen.sh
./configure --prefix=/usr/local
make
sudo make install
```

### Compilation errors
- Ensure you have C++17 support
- Check that all Qt modules are installed
- Verify CMake version is 3.21 or higher

---

## Development Environment

### Qt Creator
1. Open CMakeLists.txt in Qt Creator
2. Configure project with appropriate kit
3. Build and run from IDE

### VS Code
1. Install CMake Tools extension
2. Open project folder
3. Select preset from status bar
4. Build with F7

### Visual Studio
1. Open folder in Visual Studio
2. VS will detect CMakeLists.txt
3. Configure CMake settings
4. Build with Ctrl+Shift+B

---

## Continuous Integration

GitHub Actions CI is not included in this initial bootstrap per user request. To add CI later:

1. Create `.github/workflows/build.yml`
2. Set up Qt installation in CI environment
3. Install GStreamer and dependencies
4. Run CMake configure and build
5. Optionally run tests

Example workflow stub:
```yaml
name: Build

on: [push, pull_request]

jobs:
  build-linux:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Install Qt
        uses: jurplel/install-qt-action@v3
        with:
          version: '6.6.0'
      - name: Install dependencies
        run: |
          sudo apt update
          sudo apt install -y libgstreamer1.0-dev libopus-dev
      - name: Build
        run: |
          cmake --preset=linux-ninja-release
          cmake --build --preset=linux-ninja-release
```

---

## Next Steps After Build

1. Copy `config.json.template` to `config.json`
2. Edit `config.json` to point to your OpLink server
3. Run the application
4. Login with your credentials
5. Start messaging!

For backend setup, see [OpLink Server](https://github.com/zjdaniels1985/oplink-server)
