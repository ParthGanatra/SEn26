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
//    backend.add_popup_data();
    UserConfig uc;
    Frontend frontend;

    Database db;
    db.setUser("user");
    db.stocklist = backend.stocklist;
    db.run();

    backend.addDatabse(&db);
    db.database_test();


    db.getTick(10,"apple");



    Helper login_helper;

//    engine.rootContext()->setContextProperty("_backend", &backend);

        engine.rootContext()->setContextProperty("myModel", QVariant::fromValue(backend.stocklist));

   // Helper login_helper;
    engine.rootContext()->setContextProperty("_backend", &backend);
   engine.rootContext()->setContextProperty("_frontend", &frontend);
//    engine.rootContext()->setContextProperty("_database", &db);
    engine.rootContext()->setContextProperty("_userconfig", &uc);
    engine.rootContext()->setContextProperty("_helper", &login_helper);


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
    chartdata.addBackend_data(&backend,&db);

//    QObject::connect(chartdata,&Chartdata::addData, &backend,&Backend::add_data);
    channel.registerObject("chartdata", &chartdata);
    engine.rootContext()->setContextProperty("_chartdata", &chartdata);

    QList<QObject*> all_popups_list;
//    all_popups_list.append(new All_Popups_Model("Stock1","Indicator1",">","50"));
//    all_popups_list.append(new All_Popups_Model("Stock2","Indicator3",">","70"));
//    QDeclarativeContext *ctxt all_popups_list= engine.rootContext();
    backend.addPopupList(&all_popups_list);

    QList<QObject*> trig_popups_list;
    backend.trigPopupList(&trig_popups_list);
//    engine.rootContext()->setContextProperty("all_popup_model",QVariant::fromValue(all_popups_list));
    backend.get_all_popup_conditions();

    return app.exec();
}
