#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine/qtwebengineglobal.h>

#include <QUrl>
#include <QDebug>

#include <QtWebChannel>
#include <QtWebSockets/QWebSocketServer>

#include "shared/websocketclientwrapper.h"
#include "shared/websockettransport.h"
#include "chartdata.h"


#include <qqmlcontext.h>
#include "backend.h"
#include "frontend.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtWebEngine::initialize();

    QQmlApplicationEngine engine;
    engine.addImportPath("qml/StockAnalyser/modules");
    engine.load(QUrl(QStringLiteral("qml/StockAnalyser/main.qml")));

    Backend backend;
    backend.add_popup_data();

    Frontend frontend;
    Database db;
    db.run();


    engine.rootContext()->setContextProperty("_backend", &backend);
    engine.rootContext()->setContextProperty("_frontend", &frontend);
    engine.rootContext()->setContextProperty("_database", &backend);

    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"),
                                QWebSocketServer::NonSecureMode);
    if (!server.listen(QHostAddress::LocalHost, 12345)) {
        qFatal("Failed to open web socket server.");
        return 1;
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper clientWrapper(&server);

    // setup the channel
    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    // setup the dialog and publish it to the QWebChannel
    Chartdata chartdata;
    channel.registerObject("chartdata", &chartdata);
    engine.rootContext()->setContextProperty("_chartdata", &chartdata);

    return app.exec();
}
