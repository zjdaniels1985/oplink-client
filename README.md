# OpLink Client

<div align="center">
  <h1>OPLINK</h1>
  <p><strong>OperationsLink - Mission Critical Gaming Communications</strong></p>
  <p>Cross-platform desktop client built with Qt 6 and C++</p>
</div>

---

## 🎯 Features

- ✅ **Real-time Messaging** - WebSocket-based instant communication
- ✅ **Cross-Platform** - Native support for Linux and Windows
- ✅ **Modern UI** - Built with QML for smooth, responsive interface
- ✅ **Military Theme** - Tactical design for gaming operations
- 🚧 **Voice Chat** - Coming soon
- 🚧 **Screen Sharing** - In development

## 🛠️ Tech Stack

- **Qt 6.5+** - Cross-platform application framework
- **C++17** - Modern C++ standards
- **QML** - Declarative UI language
- **WebSockets** - Real-time communication
- **CMake** - Build system

## 📋 Requirements

### Linux
- Qt 6.5 or higher
- CMake 3.16+
- GCC 9+ or Clang 10+
- OpenGL libraries

### Windows
- Qt 6.5 or higher
- CMake 3.16+
- MSVC 2019+ or MinGW
- Visual Studio 2019+ (recommended)

## 🚀 Building

### Linux

```bash
# Install Qt 6
sudo apt install qt6-base-dev qt6-websockets-dev qt6-multimedia-dev

# Clone and build
git clone https://github.com/zjdaniels1985/oplink-client.git
cd oplink-client
mkdir build && cd build
cmake ..
cmake --build .
```

### Windows

```bash
# Install Qt 6 from https://www.qt.io/download

# Clone and build
git clone https://github.com/zjdaniels1985/oplink-client.git
cd oplink-client
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH="C:/Qt/6.5.0/msvc2019_64" ..
cmake --build . --config Release
```

## 🎮 Running

```bash
# Linux
./oplink-client

# Windows
oplink-client.exe
```

## ⚙️ Configuration

Edit server connection settings:
- Default: `ws://localhost:8080/ws`
- Can be changed in Settings menu or via environment variable:

```bash
export OPLINK_SERVER_URL="ws://your-server:8080/ws"
```

## 📚 Documentation

- [Building Guide](docs/BUILDING.md)
- [Architecture Overview](docs/ARCHITECTURE.md)

## 🤝 Contributing

OpLink is a personal project for gaming with friends. Contributions welcome!

## 📄 License

MIT License - See LICENSE file

## 🔗 Links

- [OpLink Server Repository](https://github.com/zjdaniels1985/oplink-server)
- [Issue Tracker](https://github.com/zjdaniels1985/oplink-client/issues)

---

**OpLink** - Where tactical communication meets gaming excellence