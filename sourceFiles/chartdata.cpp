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
    qDebug()<<"Sfdds";
    QJsonObject temp;
    temp["list"] = backend->get_elliott_count(stock,start,end,lev);
    qDebug()<<"Sfdds";
    return temp;
}

QJsonObject Chartdata::getstockPriceData(QString stockName, int start, int end){
    qDebug()<<"Sfdds";
    QStringList str = database->getTickInterval(start,end,stockName);
    QJsonArray arr;
    QJsonObject temp;

    for(int i=1;i<str.length();i++){
        QJsonDocument doc = QJsonDocument::fromJson(str.at(i).toUtf8());
        temp = doc.object();

        arr.append(temp);
    }
    arr.append(temp);
    arr.append(temp);

    QJsonObject list1;
    list1["list"] = arr;
    qDebug()<<"Sfdds";
    return list1;
}

QJsonObject Chartdata::getstockPriceDataIndex(QString stockName, int index){
    qDebug()<<"Sfdds";
    QString str = database->getTick(index,stockName);
    QJsonObject temp;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    temp = doc.object();
    return temp;
}




QJsonObject Chartdata::getStockList(){
    QJsonArray arr;
qDebug()<<"Sfdds";
    for(int i=0;i<backend->stocklist.length();i++){
        QJsonObject temp;

        temp["name"] = backend->stocklist.at(i);
        temp["maxlevels"] = 5;

        arr.append(temp);
    }
    QJsonObject list1;
    list1["list"] = arr;
qDebug()<<"Sfdds";
    return list1;
}
