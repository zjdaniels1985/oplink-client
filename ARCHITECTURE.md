# OpLink Client Architecture

## High-Level Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                         QML UI Layer                             │
│  ┌──────────┐  ┌───────────┐  ┌──────────┐  ┌─────────────┐   │
│  │ Server   │  │  Channel  │  │   Chat   │  │   Member    │   │
│  │   List   │  │   List    │  │   View   │  │    List     │   │
│  └──────────┘  └───────────┘  └──────────┘  └─────────────┘   │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │              Status Bar (Voice Controls)                  │  │
│  └──────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
                              ↕
┌─────────────────────────────────────────────────────────────────┐
│                      Stores (State Management)                   │
│  ┌─────────────┐  ┌────────────┐  ┌──────────┐  ┌───────────┐ │
│  │   Session   │  │   Server   │  │ Channel  │  │  Message  │ │
│  │    Store    │  │   Store    │  │  Store   │  │   Store   │ │
│  └─────────────┘  └────────────┘  └──────────┘  └───────────┘ │
└─────────────────────────────────────────────────────────────────┘
                              ↕
┌─────────────────────────────────────────────────────────────────┐
│                      Services Layer                              │
│  ┌─────────┐  ┌──────────┐  ┌─────────┐  ┌────────┐  ┌──────┐ │
│  │  Auth   │  │ Message  │  │Presence │  │ Voice  │  │Video │ │
│  │ Service │  │ Service  │  │ Service │  │Service │  │Svc.  │ │
│  └─────────┘  └──────────┘  └─────────┘  └────────┘  └──────┘ │
│  ┌──────────────────────┐  ┌───────────────────────────────┐  │
│  │    HTTP Client       │  │      WebSocket Client         │  │
│  │   (REST API)         │  │      (STOMP/WS)               │  │
│  └──────────────────────┘  └───────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
                              ↕
┌─────────────────────────────────────────────────────────────────┐
│                 Media Stack (Stubbed/Future)                     │
│  ┌───────────────────────────────────────────────────────────┐ │
│  │                  GStreamer Pipeline                        │ │
│  │  ┌──────────┐  ┌─────────┐  ┌──────┐  ┌──────────────┐  │ │
│  │  │  Audio   │→ │ RNNoise │→ │ Opus │→ │  webrtcbin   │  │ │
│  │  │  Device  │  │  Filter │  │Encode│  │     (SFU)    │  │ │
│  │  └──────────┘  └─────────┘  └──────┘  └──────────────┘  │ │
│  │  ┌──────────┐  ┌─────────────────┐  ┌──────────────┐  │ │
│  │  │  Video   │→ │ H.264 Encoder   │→ │  webrtcbin   │  │ │
│  │  │  Device  │  │ (HW/SW fallback)│  │     (SFU)    │  │ │
│  │  └──────────┘  └─────────────────┘  └──────────────┘  │ │
│  └───────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────┘
                              ↕
┌─────────────────────────────────────────────────────────────────┐
│                    Backend Integration                           │
│  ┌──────────────────┐         ┌──────────────────────────────┐ │
│  │   Spring Boot    │         │     WebSocket/STOMP          │ │
│  │   REST API       │         │   Real-time Updates          │ │
│  │                  │         │                              │ │
│  │ /api/auth/*      │         │ /topic/channels/{id}/msgs    │ │
│  │ /api/channels/*  │         │ /topic/servers/{id}/presence │ │
│  │ /api/voice/*     │         │                              │ │
│  └──────────────────┘         └──────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────┘
```

## Component Details

### UI Layer (QML)
- **main.qml**: Application window and layout
- **Theme.qml**: Dark theme singleton with Discord-like colors
- **ServerList**: Left rail with server icons
- **ChannelList**: Channel browser with text/voice channels
- **ChatView**: Message transcript + composer
- **MemberList**: Server members with presence
- **StatusBar**: User profile + voice controls (mute/deafen/settings)
- **LoginDialog**: Authentication modal

### Models
- **User**: User profile (id, username, email, avatar, status)
- **Server**: Server/guild (id, name, icon, owner)
- **Channel**: Text/voice channel (id, name, type, topic)
- **Message**: Chat message (id, content, author, timestamp)
- **Presence**: User presence (userId, status, lastSeen)

### Stores (State Management)
- **SessionStore**: Current user session and auth token
- **ServerStore**: List of servers, current server selection
- **ChannelStore**: List of channels, current channel selection
- **MessageStore**: Message history with pagination cursor support

### Services
- **HttpClient**: Generic REST API client with auth header injection
- **WsClient**: STOMP over WebSocket client with auto-reconnect
- **AuthService**: `/api/auth/register`, `/api/auth/login`, `/api/auth/me`
- **MessageService**: Fetch history + send messages + real-time subscription
- **PresenceService**: Subscribe to presence updates
- **VoiceService**: (Stubbed) Audio capture/playback, device selection
- **VideoService**: (Stubbed) Camera/screen capture

### Media Stack (Stubbed)
- **MediaPipeline**: GStreamer pipeline orchestration
- **AudioDevice**: Audio device enumeration
- **RNNoiseProcessor**: Audio noise suppression preprocessing

Pipeline flow (future):
```
Capture:  Device → RNNoise → Opus → webrtcbin → SFU
Playback: SFU → webrtcbin → Opus Decoder → Audio Sink
Video:    Camera → H.264 (nvh264enc/vaapih264enc/x264) → webrtcbin → SFU
Screen:   Screen Capture → H.264 → webrtcbin → SFU
```

### Configuration
- **ConfigManager**: Loads `config.json` with environment variable overrides
- **config.json**: API URLs, TURN server, feature flags, audio/video settings

## Data Flow Examples

### Authentication Flow
```
User Input → LoginDialog → AuthService.login()
  → HttpClient.post("/api/auth/login")
  → Response: {token, user}
  → SessionStore.setToken() + setCurrentUser()
  → UI updates (dialog closes)
```

### Messaging Flow
```
Send:
  User Input → ChatView → MessageService.sendMessage()
    → HttpClient.post("/api/channels/{id}/messages")
    → Response: message object
    → MessageStore.addMessage()
    → UI updates

Receive (Real-time):
  WsClient receives on /topic/channels/{id}/messages
    → MessageService.handleMessageFromWs()
    → MessageStore.addMessage()
    → UI updates (new message appears)
```

### Presence Flow
```
Subscribe:
  ServerStore.currentServer changes
    → PresenceService.subscribeToServer(serverId)
    → WsClient.subscribe("/topic/servers/{id}/presence")

Receive:
  WsClient receives presence update
    → PresenceService.handlePresenceFromWs()
    → Emit presenceUpdated signal
    → UI updates member list
```

## Technology Stack

### Frontend
- **Qt 6.6+**: Cross-platform framework
- **QML**: Declarative UI
- **C++17**: Business logic
- **CMake 3.21+**: Build system

### Media (Prepared)
- **GStreamer 1.20+**: Media framework
- **webrtcbin**: WebRTC implementation
- **Opus**: Audio codec
- **RNNoise**: Noise suppression
- **H.264**: Video codec (nvh264enc/vaapih264enc/h264_amf/x264enc)

### Backend Integration
- **REST API**: HTTP client for CRUD operations
- **WebSocket**: STOMP protocol for real-time updates
- **JSON**: Data serialization

## Build Configuration

### CMake Features
- Modular dependency detection
- Optional RNNoise support (HAVE_RNNOISE)
- Optional FFmpeg fallback (HAVE_FFMPEG)
- CMake presets for Linux/Windows
- Qt resource compilation (qml.qrc)

### Platforms
- **Linux**: GCC 9+, Clang 10+
- **Windows**: MSVC 2019+, MinGW-w64
- **macOS**: (Supported but not primary target)

## Future Enhancements

### Short-term
- [ ] Complete GStreamer media pipeline implementation
- [ ] WebRTC SFU signaling integration
- [ ] User settings dialog
- [ ] Message editing/deletion

### Medium-term
- [ ] Voice activity detection (VAD)
- [ ] Push-to-talk
- [ ] Video rendering in QML
- [ ] Screen sharing implementation
- [ ] File uploads/attachments

### Long-term
- [ ] End-to-end encryption
- [ ] Mobile clients (Qt for iOS/Android)
- [ ] Plugin system
- [ ] Custom themes
- [ ] Accessibility features
