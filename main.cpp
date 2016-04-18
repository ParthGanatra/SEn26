#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine/qtwebengineglobal.h>
#include <QUrl>
#include <QDebug>
#include <QtWebChannel>
#include <QtWebSockets/QWebSocketServer>
#include <QObject>
#include <QList>
#include <qqmlcontext.h>

#include "shared/websocketclientwrapper.h"
#include "shared/websockettransport.h"
#include "sourceFiles/chartdata.h"
#include "sourceFiles/backend.h"
#include "sourceFiles/frontend.h"
#include "sourceFiles/database.h"
#include "sourceFiles/userconfig.h"
#include "sourceFiles/helper.h"
#include "sourceFiles/all_popups_model.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtWebEngine::initialize();

    QQmlApplicationEngine engine;
    engine.addImportPath("qml/StockAnalyser/modules");
    engine.load(QUrl(QStringLiteral("qml/StockAnalyser/main.qml")));

    Backend backend;
    UserConfig uc;
    Frontend frontend;

    Database db;
    db.setUser("user");
    db.stocklist = backend.stocklist;
    db.run();

    backend.addDatabse(&db);

    Helper login_helper;

    engine.rootContext()->setContextProperty("myModel", QVariant::fromValue(backend.stocklist));
    engine.rootContext()->setContextProperty("_backend", &backend);
    engine.rootContext()->setContextProperty("_frontend", &frontend);
    //    engine.rootContext()->setContextProperty("_database", &db);
    engine.rootContext()->setContextProperty("_userconfig", &uc);
    engine.rootContext()->setContextProperty("_helper", &login_helper);

    QWebSocketServer server(QStringLiteral("QWebChannel Server"),QWebSocketServer::NonSecureMode);

    int add = 12345;
    while(!server.listen(QHostAddress::LocalHost, add)){
        add = add + 1;
    }

    WebSocketClientWrapper clientWrapper(&server);

    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    Chartdata chartdata;
    chartdata.addBackend_data(&backend,&db);

    QObject::connect(&chartdata,SIGNAL(addData(int)), &backend,SLOT(add_data(int)));
    channel.registerObject("chartdata", &chartdata);
    engine.rootContext()->setContextProperty("_chartdata", &chartdata);

    QList<QObject*> all_popups_list;
    backend.addPopupList(&all_popups_list);

    QList<QObject*> trig_popups_list;
    backend.trigPopupList(&trig_popups_list);
    backend.get_all_popup_conditions();

    return app.exec();
}
