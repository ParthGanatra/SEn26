#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QObject>
#include <QJsonObject>
#include "backend.h"
#include "database.h"

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
};

#endif // CHARTDATA_H
