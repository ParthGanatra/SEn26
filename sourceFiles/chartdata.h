#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QObject>
#include <QJsonObject>
#include "backend.h"
#include "database.h"
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>

class Chartdata : public QObject
{
    Q_OBJECT
    int Width, Height;
    Backend backend;
    Database database;
    QQmlApplicationEngine *engine;
    QList<QObject*> all_popups_list;
    QList<QObject*> trig_popups_list;

public:
    explicit Chartdata(QObject *parent = 0);
    virtual ~Chartdata();

signals:
    void showTrigPopup(QString stockName);
    void addData(int index);

public:
    Q_INVOKABLE int onLogin(QString user);
    Q_INVOKABLE QJsonObject getWH() const;
    Q_INVOKABLE QJsonObject getStockList();
    Q_INVOKABLE void setWH(int width, int height);
    Q_INVOKABLE void addBackend_data(QQmlApplicationEngine *engin);
    Q_INVOKABLE QJsonObject getstockPriceData(QString stockName, int start, int end);
    Q_INVOKABLE QJsonObject getEllietteCount(QString stock, int start, int end, int lev);
    Q_INVOKABLE QJsonObject getstockPriceDataIndex(QString stockName, int index);
    Q_INVOKABLE QJsonObject timeUpdate(QString stockName, int start, int end);
    Q_INVOKABLE QJsonObject getindicatorData(QString stockName, int start, int end);
    Q_INVOKABLE void print(QString str);
    Q_INVOKABLE Backend * getdata();
};

#endif // CHARTDATA_H
