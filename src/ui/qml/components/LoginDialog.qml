import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: root
    modal: true
    anchors.centerIn: Overlay.overlay
    
    width: 400
    height: 500
    
    background: Rectangle {
        color: Theme.backgroundColor
        radius: Theme.radiusMedium
    }
    
    header: Rectangle {
        width: parent.width
        height: 60
        color: Theme.backgroundColor
        
        Text {
            anchors.centerIn: parent
            text: "Welcome to OpLink"
            color: Theme.textPrimary
            font.pixelSize: Theme.fontSizeTitle
            font.bold: true
        }
    }
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Theme.paddingLarge
        spacing: Theme.paddingLarge
        
        // Tab buttons
        Row {
            Layout.alignment: Qt.AlignHCenter
            spacing: 0
            
            Button {
                text: "Login"
                flat: true
                checked: !registerMode
                onClicked: registerMode = false
                
                background: Rectangle {
                    color: !registerMode ? Theme.accentPrimary : "transparent"
                    radius: Theme.radiusSmall
                }
                
                contentItem: Text {
                    text: parent.text
                    color: Theme.textPrimary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            
            Button {
                text: "Register"
                flat: true
                checked: registerMode
                onClicked: registerMode = true
                
                background: Rectangle {
                    color: registerMode ? Theme.accentPrimary : "transparent"
                    radius: Theme.radiusSmall
                }
                
                contentItem: Text {
                    text: parent.text
                    color: Theme.textPrimary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
        
        // Login form
        ColumnLayout {
            Layout.fillWidth: true
            spacing: Theme.paddingMedium
            visible: !registerMode
            
            TextField {
                id: loginUsername
                Layout.fillWidth: true
                placeholderText: "Username"
                color: Theme.textPrimary
                background: Rectangle {
                    color: Theme.backgroundAccent
                    radius: Theme.radiusSmall
                }
            }
            
            TextField {
                id: loginPassword
                Layout.fillWidth: true
                placeholderText: "Password"
                echoMode: TextInput.Password
                color: Theme.textPrimary
                background: Rectangle {
                    color: Theme.backgroundAccent
                    radius: Theme.radiusSmall
                }
            }
            
            Button {
                Layout.fillWidth: true
                text: "Login"
                enabled: loginUsername.text.length > 0 && loginPassword.text.length > 0
                
                background: Rectangle {
                    color: parent.enabled ? Theme.accentPrimary : Theme.backgroundAccent
                    radius: Theme.radiusSmall
                }
                
                contentItem: Text {
                    text: parent.text
                    color: Theme.textPrimary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }
                
                onClicked: {
                    AuthService.login(loginUsername.text, loginPassword.text)
                }
            }
        }
        
        // Register form
        ColumnLayout {
            Layout.fillWidth: true
            spacing: Theme.paddingMedium
            visible: registerMode
            
            TextField {
                id: registerUsername
                Layout.fillWidth: true
                placeholderText: "Username"
                color: Theme.textPrimary
                background: Rectangle {
                    color: Theme.backgroundAccent
                    radius: Theme.radiusSmall
                }
            }
            
            TextField {
                id: registerEmail
                Layout.fillWidth: true
                placeholderText: "Email"
                color: Theme.textPrimary
                background: Rectangle {
                    color: Theme.backgroundAccent
                    radius: Theme.radiusSmall
                }
            }
            
            TextField {
                id: registerPassword
                Layout.fillWidth: true
                placeholderText: "Password"
                echoMode: TextInput.Password
                color: Theme.textPrimary
                background: Rectangle {
                    color: Theme.backgroundAccent
                    radius: Theme.radiusSmall
                }
            }
            
            Button {
                Layout.fillWidth: true
                text: "Register"
                enabled: registerUsername.text.length > 0 && 
                        registerEmail.text.length > 0 && 
                        registerPassword.text.length > 0
                
                background: Rectangle {
                    color: parent.enabled ? Theme.accentPrimary : Theme.backgroundAccent
                    radius: Theme.radiusSmall
                }
                
                contentItem: Text {
                    text: parent.text
                    color: Theme.textPrimary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }
                
                onClicked: {
                    AuthService.registerUser(
                        registerUsername.text,
                        registerEmail.text,
                        registerPassword.text
                    )
                }
            }
        }
        
        Item { Layout.fillHeight: true }
        
        Text {
            Layout.fillWidth: true
            text: errorMessage
            color: Theme.accentDanger
            font.pixelSize: Theme.fontSizeMedium
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            visible: errorMessage.length > 0
        }
    }
    
    property bool registerMode: false
    property string errorMessage: ""
    
    Connections {
        target: AuthService
        
        function onLoginSuccess() {
            root.close()
        }
        
        function onLoginFailed(error) {
            errorMessage = error
        }
        
        function onRegisterSuccess() {
            registerMode = false
            errorMessage = "Registration successful! Please log in."
        }
        
        function onRegisterFailed(error) {
            errorMessage = error
        }
    }
}
