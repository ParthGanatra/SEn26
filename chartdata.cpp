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

QJsonObject Chartdata::getEllietteCount(QString stock, int start, int end, int lev){
    QJsonObject temp;
    temp["list"] = backend->get_elliott_count(stock,start,end,lev);
    return temp;
}

QJsonObject Chartdata::getstockPriceData(QString stockName, int start, int end){
    QStringList str = database->getTickInterval(start,end,stockName);
    QJsonArray arr;
    for(int i=0;i<str.length();i++){
        QJsonObject temp;

        QJsonDocument doc = QJsonDocument::fromJson(str.at(i).toUtf8());
        temp = doc.object();

        arr.append(temp);
    }
    QJsonObject list1;
    list1["list"] = arr;

    return list1;
}


QJsonObject Chartdata::getStockList(){
    QJsonArray arr;
    for(int i=0;i<backend->stocklist.length();i++){
        QJsonObject temp;

        temp["name"] = backend->stocklist.at(i);
        temp["maxlevels"] = 5;

        arr.append(temp);
    }
    QJsonObject list1;
    list1["list"] = arr;

    return list1;
}
