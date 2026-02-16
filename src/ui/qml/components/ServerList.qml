import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: Theme.backgroundTertiary
    
    ColumnLayout {
        anchors.fill: parent
        spacing: 8
        
        // Home button
        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 8
            width: 48
            height: 48
            radius: 24
            color: Theme.accentPrimary
            
            Text {
                anchors.centerIn: parent
                text: "H"
                color: "white"
                font.pixelSize: 20
                font.bold: true
            }
            
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    // TODO: Navigate to home/DM view
                }
            }
        }
        
        Rectangle {
            Layout.fillWidth: true
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            height: 2
            color: Theme.backgroundAccent
        }
        
        // Server icons (placeholder)
        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 8
            
            spacing: 8
            clip: true
            
            model: ServerStore.servers
            
            delegate: Rectangle {
                width: 48
                height: 48
                radius: 24
                color: Theme.backgroundAccent
                anchors.horizontalCenter: parent.horizontalCenter
                
                Text {
                    anchors.centerIn: parent
                    text: modelData.name ? modelData.name.substring(0, 1).toUpperCase() : "?"
                    color: Theme.textPrimary
                    font.pixelSize: 20
                    font.bold: true
                }
                
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        ServerStore.currentServer = modelData
                    }
                }
            }
        }
        
        // Add server button
        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 8
            width: 48
            height: 48
            radius: 24
            color: Theme.backgroundAccent
            
            Text {
                anchors.centerIn: parent
                text: "+"
                color: Theme.accentSuccess
                font.pixelSize: 28
            }
            
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    // TODO: Show add server dialog
                }
            }
        }
    }
}
