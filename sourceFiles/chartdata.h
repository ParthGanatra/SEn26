#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QObject>
#include <QJsonObject>
#include "backend.h"
#include "database.h"
#include <QString>
#include <QStringList>
#include <QJsonDocument>

class Chartdata : public QObject
{
    Q_OBJECT
    int Width, Height;
    Backend *backend;
    Database *database;

    public:
        explicit Chartdata(QObject *parent = 0);
        virtual ~Chartdata();

    public:
        Q_INVOKABLE QJsonObject getWH() const;
        Q_INVOKABLE QJsonObject getStockList();
        Q_INVOKABLE void setWH(int width, int height);
        Q_INVOKABLE void addBackend_data(Backend *temp, Database *temp1);
        Q_INVOKABLE QJsonObject getstockPriceData(QString stockName, int start, int end);
        Q_INVOKABLE QJsonObject getEllietteCount(QString stock, int start, int end, int lev);
        Q_INVOKABLE QJsonObject getstockPriceDataIndex(QString stockName, int index);
};

#endif // CHARTDATA_H
