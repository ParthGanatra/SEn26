#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <qqmlcontext.h>
#include "backend.h"
#include "frontend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath("qml/StockAnalyser/modules");
    engine.load(QUrl(QStringLiteral("qml/StockAnalyser/main.qml")));

    Backend backend;
    backend.add_popup_data();

    Frontend forntent;
    //forntent.add_popup_data();

    engine.rootContext()->setContextProperty("_backend", &backend);
    engine.rootContext()->setContextProperty("_forntent", &forntent);

    return app.exec();
}
