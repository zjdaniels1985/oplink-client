import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import "components"
import "views"

ApplicationWindow {
    id: root
    width: 1280
    height: 720
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    title: "OpLink - Mission Critical Gaming Communications"
    
    color: Theme.backgroundColor
    
    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        // Left rail - Server list
        ServerList {
            Layout.fillHeight: true
            Layout.preferredWidth: 72
        }
        
        // Server view - Channel list + main content
        ServerView {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
    
    // Status bar at bottom
    StatusBar {
        id: statusBar
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 52
    }
    
    // Login dialog (shown if not authenticated)
    LoginDialog {
        id: loginDialog
        visible: !SessionStore.authenticated
    }
}
