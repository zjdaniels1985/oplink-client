import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: Theme.backgroundSecondary
    
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        
        // Header
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 48
            color: Theme.backgroundSecondary
            
            Text {
                anchors.centerIn: parent
                text: "MEMBERS"
                color: Theme.textMuted
                font.pixelSize: Theme.fontSizeSmall
                font.bold: true
            }
            
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: Theme.divider
            }
        }
        
        // Member list (placeholder)
        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 4
            clip: true
            
            model: ListModel {
                ListElement { username: "You"; status: "online" }
                ListElement { username: "Player2"; status: "online" }
                ListElement { username: "Player3"; status: "idle" }
                ListElement { username: "Player4"; status: "offline" }
            }
            
            delegate: Rectangle {
                width: ListView.view.width
                height: 42
                color: "transparent"
                
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.rightMargin: Theme.paddingMedium
                    spacing: Theme.paddingMedium
                    
                    // Status indicator
                    Rectangle {
                        width: 10
                        height: 10
                        radius: 5
                        color: {
                            switch(model.status) {
                                case "online": return Theme.accentSuccess
                                case "idle": return Theme.accentWarning
                                default: return Theme.textMuted
                            }
                        }
                    }
                    
                    // Avatar
                    Rectangle {
                        width: 32
                        height: 32
                        radius: 16
                        color: Theme.accentPrimary
                        
                        Text {
                            anchors.centerIn: parent
                            text: model.username.substring(0, 1).toUpperCase()
                            color: "white"
                            font.pixelSize: 14
                            font.bold: true
                        }
                    }
                    
                    Text {
                        Layout.fillWidth: true
                        text: model.username
                        color: model.status === "online" ? 
                               Theme.textPrimary : Theme.textMuted
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }
                
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    
                    onEntered: parent.color = Theme.backgroundAccent
                    onExited: parent.color = "transparent"
                    onClicked: {
                        // TODO: Show user profile
                    }
                }
            }
        }
    }
}
