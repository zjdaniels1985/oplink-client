import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: Theme.backgroundSecondary
    
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        
        // Server name header
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 48
            color: Theme.backgroundSecondary
            
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Theme.paddingLarge
                anchors.rightMargin: Theme.paddingLarge
                
                Text {
                    Layout.fillWidth: true
                    text: ServerStore.currentServer ? ServerStore.currentServer.name : "OpLink"
                    color: Theme.textPrimary
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                }
            }
            
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: Theme.divider
            }
        }
        
        // Text channels section
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 24
            color: "transparent"
            
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Theme.paddingLarge
                anchors.rightMargin: Theme.paddingMedium
                
                Text {
                    Layout.fillWidth: true
                    text: "TEXT CHANNELS"
                    color: Theme.textMuted
                    font.pixelSize: Theme.fontSizeSmall
                    font.bold: true
                }
                
                Text {
                    text: "+"
                    color: Theme.textMuted
                    font.pixelSize: Theme.fontSizeMedium
                }
            }
        }
        
        // Channel list
        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 2
            clip: true
            
            model: ServerStore.currentServer ? 
                   ChannelStore.channelsForServer(ServerStore.currentServer.id) : []
            
            delegate: Rectangle {
                width: ListView.view.width
                height: 32
                color: ChannelStore.currentChannel === modelData ? 
                       Theme.backgroundAccent : "transparent"
                
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.rightMargin: Theme.paddingMedium
                    spacing: Theme.paddingMedium
                    
                    Text {
                        text: "#"
                        color: Theme.channelDefault
                        font.pixelSize: Theme.fontSizeLarge
                    }
                    
                    Text {
                        Layout.fillWidth: true
                        text: modelData.name || "channel"
                        color: ChannelStore.currentChannel === modelData ? 
                               Theme.channelSelected : Theme.channelDefault
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }
                
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    
                    onEntered: {
                        if (ChannelStore.currentChannel !== modelData) {
                            parent.color = Theme.backgroundAccent
                        }
                    }
                    onExited: {
                        if (ChannelStore.currentChannel !== modelData) {
                            parent.color = "transparent"
                        }
                    }
                    onClicked: {
                        ChannelStore.currentChannel = modelData
                    }
                }
            }
        }
        
        // Voice channels section
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 24
            color: "transparent"
            
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Theme.paddingLarge
                anchors.rightMargin: Theme.paddingMedium
                
                Text {
                    Layout.fillWidth: true
                    text: "VOICE CHANNELS"
                    color: Theme.textMuted
                    font.pixelSize: Theme.fontSizeSmall
                    font.bold: true
                }
                
                Text {
                    text: "+"
                    color: Theme.textMuted
                    font.pixelSize: Theme.fontSizeMedium
                }
            }
        }
        
        // Placeholder voice channel
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 32
            color: "transparent"
            
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Theme.paddingMedium
                anchors.rightMargin: Theme.paddingMedium
                spacing: Theme.paddingMedium
                
                Text {
                    text: "🔊"
                    font.pixelSize: Theme.fontSizeMedium
                }
                
                Text {
                    Layout.fillWidth: true
                    text: "General"
                    color: Theme.channelDefault
                    font.pixelSize: Theme.fontSizeMedium
                }
            }
            
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    // TODO: Join voice channel
                    VoiceService.joinVoiceChannel("voice-general")
                }
            }
        }
        
        Item {
            Layout.fillHeight: true
        }
    }
}
