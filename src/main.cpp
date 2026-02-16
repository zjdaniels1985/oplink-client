#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "config/ConfigManager.h"
#include "stores/SessionStore.h"
#include "stores/ServerStore.h"
#include "stores/ChannelStore.h"
#include "stores/MessageStore.h"
#include "services/AuthService.h"
#include "services/MessageService.h"
#include "services/PresenceService.h"
#include "services/VoiceService.h"
#include "services/VideoService.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    app.setOrganizationName("OpLink");
    app.setOrganizationDomain("oplink.io");
    app.setApplicationName("OpLink Client");
    app.setApplicationVersion("0.1.0");
    
    // Load configuration
    ConfigManager::instance()->load();
    
    // Initialize services
    AuthService::instance();
    MessageService::instance();
    PresenceService::instance();
    VoiceService::instance();
    VideoService::instance();
    
    // Set up QML engine
    QQmlApplicationEngine engine;
    
    // Expose singletons to QML
    engine.rootContext()->setContextProperty("ConfigManager", ConfigManager::instance());
    engine.rootContext()->setContextProperty("SessionStore", SessionStore::instance());
    engine.rootContext()->setContextProperty("ServerStore", ServerStore::instance());
    engine.rootContext()->setContextProperty("ChannelStore", ChannelStore::instance());
    engine.rootContext()->setContextProperty("MessageStore", MessageStore::instance());
    engine.rootContext()->setContextProperty("AuthService", AuthService::instance());
    engine.rootContext()->setContextProperty("MessageService", MessageService::instance());
    engine.rootContext()->setContextProperty("PresenceService", PresenceService::instance());
    engine.rootContext()->setContextProperty("VoiceService", VoiceService::instance());
    engine.rootContext()->setContextProperty("VideoService", VideoService::instance());
    
    // Load main QML
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    engine.load(url);
    
    return app.exec();
}
