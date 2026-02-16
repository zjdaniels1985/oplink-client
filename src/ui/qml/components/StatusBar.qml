import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: Theme.backgroundSecondary
    
    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.paddingMedium
        anchors.rightMargin: Theme.paddingMedium
        spacing: Theme.paddingMedium
        
        // User info section
        Rectangle {
            Layout.preferredWidth: 240
            Layout.fillHeight: true
            color: Theme.backgroundTertiary
            radius: Theme.radiusSmall
            
            RowLayout {
                anchors.fill: parent
                anchors.margins: Theme.paddingMedium
                spacing: Theme.paddingMedium
                
                // Avatar
                Rectangle {
                    width: 32
                    height: 32
                    radius: 16
                    color: Theme.accentPrimary
                    
                    Text {
                        anchors.centerIn: parent
                        text: SessionStore.currentUser ? 
                              SessionStore.currentUser.username.substring(0, 1).toUpperCase() : "?"
                        color: "white"
                        font.pixelSize: 14
                        font.bold: true
                    }
                }
                
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 0
                    
                    Text {
                        text: SessionStore.currentUser ? 
                              SessionStore.currentUser.username : "Not logged in"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontSizeMedium
                        font.bold: true
                    }
                    
                    Text {
                        text: "#0001"
                        color: Theme.textMuted
                        font.pixelSize: Theme.fontSizeSmall
                    }
                }
            }
        }
        
        Item { Layout.fillWidth: true }
        
        // Voice controls
        Row {
            spacing: Theme.paddingSmall
            
            // Mute button
            Button {
                width: 36
                height: 36
                flat: true
                
                background: Rectangle {
                    color: VoiceService.muted ? Theme.accentDanger : Theme.backgroundAccent
                    radius: Theme.radiusSmall
                }
                
                contentItem: Text {
                    text: VoiceService.muted ? "🔇" : "🎤"
                    color: Theme.textPrimary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 18
                }
                
                onClicked: VoiceService.muted = !VoiceService.muted
                
                ToolTip.text: VoiceService.muted ? "Unmute" : "Mute"
                ToolTip.visible: hovered
            }
            
            // Deafen button
            Button {
                width: 36
                height: 36
                flat: true
                
                background: Rectangle {
                    color: VoiceService.deafened ? Theme.accentDanger : Theme.backgroundAccent
                    radius: Theme.radiusSmall
                }
                
                contentItem: Text {
                    text: VoiceService.deafened ? "🔇" : "🎧"
                    color: Theme.textPrimary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 18
                }
                
                onClicked: VoiceService.deafened = !VoiceService.deafened
                
                ToolTip.text: VoiceService.deafened ? "Undeafen" : "Deafen"
                ToolTip.visible: hovered
            }
            
            // Settings button
            Button {
                width: 36
                height: 36
                flat: true
                
                background: Rectangle {
                    color: Theme.backgroundAccent
                    radius: Theme.radiusSmall
                }
                
                contentItem: Text {
                    text: "⚙️"
                    color: Theme.textPrimary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 18
                }
                
                onClicked: {
                    // TODO: Show settings dialog
                }
                
                ToolTip.text: "Settings"
                ToolTip.visible: hovered
            }
        }
    }
}
