#include "chartdata.h"

#include <QtCore/QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <cstdlib>

Chartdata::Chartdata(QObject *parent)
    : QObject(parent)
{
    Backend * backend = new Backend();
    Database * datbase = new Database();
}

Chartdata::~Chartdata()
{}

void Chartdata::addBackend_data(Backend *temp, Database *temp1){
    backend = temp;
    database = temp1;
}

QJsonObject Chartdata::getWH() const
{
    qDebug()<<"asdasd";
    QJsonObject temp;
    temp["width"] = Width;
    temp["height"] = Height;
    return temp;
}

void Chartdata::setWH(int width, int height){
    Width = width;
    Height = height;
}

/*
 *  database
 *  stockList
 *  getTick(stock,start_index, end_index)
 *
 *  backend
 *
 *  get_elliette_count(stock, start_index, end_index, level)
 *  add_data(start_index)
*/


QJsonObject Chartdata::getStockList(){
    QJsonArray arr;
    for(int i=0;i<7;i++){
        QJsonObject temp;

        QString printable = QStringLiteral("Stock %1").arg(i+1);
        temp["name"] = printable;
        temp["maxlevels"] = 4;

        arr.append(temp);
    }
    QJsonObject list1;
    list1["list"] = arr;

    return list1;
}
