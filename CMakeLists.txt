cmake_minimum_required(VERSION 3.21)

project(oplink-client VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt 6 packages
find_package(Qt6 6.6 REQUIRED COMPONENTS
    Core
    Quick
    Qml
    Network
    WebSockets
    Multimedia
    Concurrent
)

# GStreamer (required for media stack)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0>=1.20)
pkg_check_modules(GSTREAMER_APP REQUIRED gstreamer-app-1.0>=1.20)
pkg_check_modules(GSTREAMER_VIDEO REQUIRED gstreamer-video-1.0>=1.20)
pkg_check_modules(GSTREAMER_AUDIO REQUIRED gstreamer-audio-1.0>=1.20)
pkg_check_modules(GSTREAMER_WEBRTC REQUIRED gstreamer-webrtc-1.0>=1.20)

# RNNoise for audio preprocessing
pkg_check_modules(RNNOISE rnnoise)
if(NOT RNNOISE_FOUND)
    message(WARNING "RNNoise not found via pkg-config, will attempt manual detection")
    find_library(RNNOISE_LIBRARIES NAMES rnnoise)
    find_path(RNNOISE_INCLUDE_DIRS rnnoise.h)
    if(RNNOISE_LIBRARIES AND RNNOISE_INCLUDE_DIRS)
        set(RNNOISE_FOUND TRUE)
        message(STATUS "Found RNNoise: ${RNNOISE_LIBRARIES}")
    endif()
endif()

# Opus codec
pkg_check_modules(OPUS REQUIRED opus>=1.3)

# Optional FFmpeg fallback
pkg_check_modules(FFMPEG libavcodec libavformat libavutil)

# Source files
set(PROJECT_SOURCES
    src/main.cpp
    
    # Config
    src/config/ConfigManager.h
    src/config/ConfigManager.cpp
    
    # Models
    src/models/User.h
    src/models/User.cpp
    src/models/Server.h
    src/models/Server.cpp
    src/models/Channel.h
    src/models/Channel.cpp
    src/models/Message.h
    src/models/Message.cpp
    src/models/Presence.h
    src/models/Presence.cpp
    
    # Stores
    src/stores/SessionStore.h
    src/stores/SessionStore.cpp
    src/stores/ServerStore.h
    src/stores/ServerStore.cpp
    src/stores/ChannelStore.h
    src/stores/ChannelStore.cpp
    src/stores/MessageStore.h
    src/stores/MessageStore.cpp
    
    # Services
    src/services/HttpClient.h
    src/services/HttpClient.cpp
    src/services/WsClient.h
    src/services/WsClient.cpp
    src/services/AuthService.h
    src/services/AuthService.cpp
    src/services/MessageService.h
    src/services/MessageService.cpp
    src/services/PresenceService.h
    src/services/PresenceService.cpp
    src/services/VoiceService.h
    src/services/VoiceService.cpp
    src/services/VideoService.h
    src/services/VideoService.cpp
    
    # Media
    src/media/MediaPipeline.h
    src/media/MediaPipeline.cpp
    src/media/AudioDevice.h
    src/media/AudioDevice.cpp
    src/media/RNNoiseProcessor.h
    src/media/RNNoiseProcessor.cpp
    
    # QML
    qml.qrc
)

# Create executable
qt_add_executable(oplink-client
    ${PROJECT_SOURCES}
)

# Include directories
target_include_directories(oplink-client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${GSTREAMER_INCLUDE_DIRS}
    ${GSTREAMER_APP_INCLUDE_DIRS}
    ${GSTREAMER_VIDEO_INCLUDE_DIRS}
    ${GSTREAMER_AUDIO_INCLUDE_DIRS}
    ${GSTREAMER_WEBRTC_INCLUDE_DIRS}
    ${OPUS_INCLUDE_DIRS}
)

if(RNNOISE_FOUND)
    target_include_directories(oplink-client PRIVATE ${RNNOISE_INCLUDE_DIRS})
    target_compile_definitions(oplink-client PRIVATE HAVE_RNNOISE)
endif()

if(FFMPEG_FOUND)
    target_include_directories(oplink-client PRIVATE ${FFMPEG_INCLUDE_DIRS})
    target_compile_definitions(oplink-client PRIVATE HAVE_FFMPEG)
endif()

# Link libraries
target_link_libraries(oplink-client PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Qml
    Qt6::Network
    Qt6::WebSockets
    Qt6::Multimedia
    Qt6::Concurrent
    ${GSTREAMER_LIBRARIES}
    ${GSTREAMER_APP_LIBRARIES}
    ${GSTREAMER_VIDEO_LIBRARIES}
    ${GSTREAMER_AUDIO_LIBRARIES}
    ${GSTREAMER_WEBRTC_LIBRARIES}
    ${OPUS_LIBRARIES}
)

if(RNNOISE_FOUND)
    target_link_libraries(oplink-client PRIVATE ${RNNOISE_LIBRARIES})
endif()

if(FFMPEG_FOUND)
    target_link_libraries(oplink-client PRIVATE ${FFMPEG_LIBRARIES})
endif()

# Link directories
target_link_directories(oplink-client PRIVATE
    ${GSTREAMER_LIBRARY_DIRS}
    ${OPUS_LIBRARY_DIRS}
)

if(RNNOISE_FOUND)
    target_link_directories(oplink-client PRIVATE ${RNNOISE_LIBRARY_DIRS})
endif()

if(FFMPEG_FOUND)
    target_link_directories(oplink-client PRIVATE ${FFMPEG_LIBRARY_DIRS})
endif()

# Platform-specific settings
if(WIN32)
    set_target_properties(oplink-client PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Install
install(TARGETS oplink-client
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)

# Install config template
install(FILES config.json.template
    DESTINATION bin
    RENAME config.json
)
