import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: Theme.backgroundColor
    
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        
        // Channel header
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 48
            color: Theme.backgroundColor
            
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Theme.paddingLarge
                anchors.rightMargin: Theme.paddingLarge
                
                Text {
                    text: "#"
                    color: Theme.textMuted
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                }
                
                Text {
                    Layout.fillWidth: true
                    text: ChannelStore.currentChannel ? 
                          ChannelStore.currentChannel.name : "general"
                    color: Theme.textPrimary
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                }
                
                // Placeholder for video/screen share buttons
                Row {
                    spacing: Theme.paddingMedium
                    
                    Button {
                        text: "📹"
                        flat: true
                        onClicked: VideoService.startCamera()
                        ToolTip.text: "Start Video"
                        ToolTip.visible: hovered
                    }
                    
                    Button {
                        text: "🖥️"
                        flat: true
                        onClicked: VideoService.startScreenShare()
                        ToolTip.text: "Share Screen"
                        ToolTip.visible: hovered
                    }
                }
            }
            
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: Theme.divider
            }
        }
        
        // Message list
        ListView {
            id: messageList
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: 0
            
            spacing: 8
            clip: true
            verticalLayoutDirection: ListView.BottomToTop
            
            model: ChannelStore.currentChannel ? 
                   MessageStore.messagesForChannel(ChannelStore.currentChannel.id) : []
            
            delegate: Rectangle {
                width: messageList.width
                height: messageContent.height + Theme.paddingLarge
                color: "transparent"
                
                RowLayout {
                    id: messageContent
                    anchors.fill: parent
                    anchors.leftMargin: Theme.paddingLarge
                    anchors.rightMargin: Theme.paddingLarge
                    anchors.topMargin: Theme.paddingMedium
                    spacing: Theme.paddingMedium
                    
                    // Avatar placeholder
                    Rectangle {
                        Layout.alignment: Qt.AlignTop
                        width: 40
                        height: 40
                        radius: 20
                        color: Theme.accentPrimary
                        
                        Text {
                            anchors.centerIn: parent
                            text: modelData.authorName ? 
                                  modelData.authorName.substring(0, 1).toUpperCase() : "?"
                            color: "white"
                            font.pixelSize: 16
                            font.bold: true
                        }
                    }
                    
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 2
                        
                        RowLayout {
                            spacing: Theme.paddingMedium
                            
                            Text {
                                text: modelData.authorName || "Unknown"
                                color: Theme.textPrimary
                                font.pixelSize: Theme.fontSizeMedium
                                font.bold: true
                            }
                            
                            Text {
                                text: Qt.formatDateTime(modelData.timestamp, "hh:mm")
                                color: Theme.textMuted
                                font.pixelSize: Theme.fontSizeSmall
                            }
                        }
                        
                        Text {
                            Layout.fillWidth: true
                            text: modelData.content || ""
                            color: Theme.textPrimary
                            font.pixelSize: Theme.fontSizeMedium
                            wrapMode: Text.Wrap
                        }
                    }
                }
            }
        }
        
        // Message composer
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 68
            Layout.margins: Theme.paddingLarge
            Layout.bottomMargin: Theme.paddingLarge + 52 // Account for status bar
            color: Theme.backgroundAccent
            radius: Theme.radiusMedium
            
            RowLayout {
                anchors.fill: parent
                anchors.margins: Theme.paddingMedium
                spacing: Theme.paddingMedium
                
                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    
                    TextArea {
                        id: messageInput
                        placeholderText: ChannelStore.currentChannel ? 
                                       "Message #" + ChannelStore.currentChannel.name : 
                                       "Select a channel"
                        color: Theme.textPrimary
                        placeholderTextColor: Theme.textMuted
                        font.pixelSize: Theme.fontSizeMedium
                        background: Rectangle { color: "transparent" }
                        wrapMode: TextArea.Wrap
                        
                        Keys.onReturnPressed: {
                            if (event.modifiers & Qt.ShiftModifier) {
                                // Shift+Enter = new line
                                return;
                            }
                            
                            event.accepted = true;
                            sendMessage();
                        }
                    }
                }
                
                Button {
                    text: "Send"
                    enabled: messageInput.text.trim().length > 0 && ChannelStore.currentChannel
                    onClicked: sendMessage()
                }
            }
        }
    }
    
    function sendMessage() {
        if (!ChannelStore.currentChannel || messageInput.text.trim().length === 0) {
            return;
        }
        
        MessageService.sendMessage(
            ChannelStore.currentChannel.id,
            messageInput.text.trim()
        );
        
        messageInput.text = "";
    }
}
