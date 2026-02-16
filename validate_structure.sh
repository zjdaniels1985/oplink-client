#!/bin/bash
# Validation script for OpLink Client project structure

echo "=== OpLink Client Project Structure Validation ==="
echo ""

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Check counter
total_checks=0
passed_checks=0

check_file() {
    total_checks=$((total_checks + 1))
    if [ -f "$1" ]; then
        echo -e "${GREEN}✓${NC} $1"
        passed_checks=$((passed_checks + 1))
    else
        echo -e "${RED}✗${NC} $1 (missing)"
    fi
}

check_dir() {
    total_checks=$((total_checks + 1))
    if [ -d "$1" ]; then
        echo -e "${GREEN}✓${NC} $1/"
        passed_checks=$((passed_checks + 1))
    else
        echo -e "${RED}✗${NC} $1/ (missing)"
    fi
}

echo "Build System Files:"
check_file "CMakeLists.txt"
check_file "CMakePresets.json"
check_file "config.json.template"
check_file "qml.qrc"

echo ""
echo "Documentation:"
check_file "README.md"
check_file "BUILD_NOTES.md"
check_file "LICENSE"
check_file ".gitignore"

echo ""
echo "Source Directories:"
check_dir "src"
check_dir "src/config"
check_dir "src/models"
check_dir "src/stores"
check_dir "src/services"
check_dir "src/media"
check_dir "src/ui/qml"
check_dir "src/ui/qml/components"
check_dir "src/ui/qml/views"

echo ""
echo "Config Files:"
check_file "src/config/ConfigManager.h"
check_file "src/config/ConfigManager.cpp"

echo ""
echo "Model Files:"
check_file "src/models/User.h"
check_file "src/models/User.cpp"
check_file "src/models/Server.h"
check_file "src/models/Server.cpp"
check_file "src/models/Channel.h"
check_file "src/models/Channel.cpp"
check_file "src/models/Message.h"
check_file "src/models/Message.cpp"
check_file "src/models/Presence.h"
check_file "src/models/Presence.cpp"

echo ""
echo "Store Files:"
check_file "src/stores/SessionStore.h"
check_file "src/stores/SessionStore.cpp"
check_file "src/stores/ServerStore.h"
check_file "src/stores/ServerStore.cpp"
check_file "src/stores/ChannelStore.h"
check_file "src/stores/ChannelStore.cpp"
check_file "src/stores/MessageStore.h"
check_file "src/stores/MessageStore.cpp"

echo ""
echo "Service Files:"
check_file "src/services/HttpClient.h"
check_file "src/services/HttpClient.cpp"
check_file "src/services/WsClient.h"
check_file "src/services/WsClient.cpp"
check_file "src/services/AuthService.h"
check_file "src/services/AuthService.cpp"
check_file "src/services/MessageService.h"
check_file "src/services/MessageService.cpp"
check_file "src/services/PresenceService.h"
check_file "src/services/PresenceService.cpp"
check_file "src/services/VoiceService.h"
check_file "src/services/VoiceService.cpp"
check_file "src/services/VideoService.h"
check_file "src/services/VideoService.cpp"

echo ""
echo "Media Files:"
check_file "src/media/MediaPipeline.h"
check_file "src/media/MediaPipeline.cpp"
check_file "src/media/AudioDevice.h"
check_file "src/media/AudioDevice.cpp"
check_file "src/media/RNNoiseProcessor.h"
check_file "src/media/RNNoiseProcessor.cpp"

echo ""
echo "QML Files:"
check_file "src/main.cpp"
check_file "src/ui/qml/main.qml"
check_file "src/ui/qml/Theme.qml"
check_file "src/ui/qml/qmldir"
check_file "src/ui/qml/components/ServerList.qml"
check_file "src/ui/qml/components/ChannelList.qml"
check_file "src/ui/qml/components/MemberList.qml"
check_file "src/ui/qml/components/StatusBar.qml"
check_file "src/ui/qml/components/LoginDialog.qml"
check_file "src/ui/qml/views/ServerView.qml"
check_file "src/ui/qml/views/ChatView.qml"

echo ""
echo "========================================="
echo "Validation Results: $passed_checks/$total_checks checks passed"
echo "========================================="

if [ $passed_checks -eq $total_checks ]; then
    echo -e "${GREEN}All files present!${NC}"
    exit 0
else
    echo -e "${RED}Some files are missing!${NC}"
    exit 1
fi
