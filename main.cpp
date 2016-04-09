#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine/qtwebengineglobal.h>

#include <qqmlcontext.h>
#include "backend.h"
#include "frontend.h"

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
    //forntent.sendOTP("guptaanurag5395@gmail.com","123132");
    //forntent.add_popup_data();

    engine.rootContext()->setContextProperty("_backend", &backend);
    engine.rootContext()->setContextProperty("frontend", &frontend);

    return app.exec();
}
