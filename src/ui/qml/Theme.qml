pragma Singleton
import QtQuick

QtObject {
    // Dark theme colors (Discord-like)
    readonly property color backgroundColor: "#36393f"
    readonly property color backgroundSecondary: "#2f3136"
    readonly property color backgroundTertiary: "#202225"
    readonly property color backgroundAccent: "#40444b"
    
    readonly property color textPrimary: "#dcddde"
    readonly property color textSecondary: "#b9bbbe"
    readonly property color textMuted: "#72767d"
    readonly property color textLink: "#00b0f4"
    
    readonly property color accentPrimary: "#5865f2"
    readonly property color accentSecondary: "#4752c4"
    readonly property color accentSuccess: "#3ba55d"
    readonly property color accentWarning: "#faa61a"
    readonly property color accentDanger: "#ed4245"
    
    readonly property color channelDefault: "#8e9297"
    readonly property color channelHover: "#dcddde"
    readonly property color channelSelected: "#ffffff"
    
    readonly property color divider: "#202225"
    
    // Typography
    readonly property int fontSizeSmall: 12
    readonly property int fontSizeMedium: 14
    readonly property int fontSizeLarge: 16
    readonly property int fontSizeTitle: 20
    
    readonly property string fontFamily: "Segoe UI"
    
    // Spacing
    readonly property int paddingSmall: 4
    readonly property int paddingMedium: 8
    readonly property int paddingLarge: 16
    
    readonly property int radiusSmall: 3
    readonly property int radiusMedium: 5
    readonly property int radiusLarge: 8
}
