import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: Theme.backgroundColor
    
    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        // Channel list
        ChannelList {
            Layout.fillHeight: true
            Layout.preferredWidth: 240
        }
        
        // Main content area
        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 0
            
            // Chat view
            ChatView {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
        
        // Member list (right sidebar)
        MemberList {
            Layout.fillHeight: true
            Layout.preferredWidth: 240
        }
    }
}
