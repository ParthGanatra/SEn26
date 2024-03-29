#include "chartdata.h"

#include <QtCore/QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <cstdlib>

Chartdata::Chartdata(QObject *parent)
    : QObject(parent)
{
    //    Backend * backend = new Backend();
    //    Database * datbase = new Database();
}

Chartdata::~Chartdata()
{}

void Chartdata::addBackend_data(QQmlApplicationEngine *engin){//Backend *temp, Database *temp1){
    //    backend = temp;
    //    database = temp1;
    engine = engin;
}

QJsonObject Chartdata::getWH() const
{
    QJsonObject temp;
    temp["width"] = Width;
    temp["height"] = Height;
    return temp;
}

QJsonObject Chartdata::timeUpdate(QString stockName, int start, int end){
    //            backend.add_data(start);
    //    qDebug()<<"ASF";
    emit addData(start);
    //    qDebug()<<"ASF4656";
    return getstockPriceData(stockName,start,end);
}

void Chartdata::print(QString str){
    qDebug()<<str;
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
    temp["list"] = backend.get_elliott_count(stock,start,end,lev);

    return temp;
}

QJsonObject Chartdata::getindicatorData(QString stockName, int start, int end){
    QStringList str = database.getTickIntervalIndicator(start,end,stockName);
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
    return list1;
}

QJsonObject Chartdata::getstockPriceData(QString stockName, int start, int end){
    QStringList str = database.getTickInterval(start,end,stockName);
    QJsonArray arr;
    QJsonObject temp;

    for(int i=1;i<str.length();i++){
        //        qDebug()<<str.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.at(i).toUtf8());
        temp = doc.object();

        arr.append(temp);
        //        qDebug()<<temp["high"].toString();
    }
    arr.append(temp);
    arr.append(temp);

    QJsonObject list1;
    list1["list"] = arr;

    return list1;
}

QJsonObject Chartdata::getstockPriceDataIndex(QString stockName, int index){

    QString str = database.getTick(index,stockName);
    QJsonObject temp;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    temp = doc.object();
    return temp;
}

QJsonObject Chartdata::getStockList(){
    QJsonArray arr;

    for(int i=0;i<backend.stocklist.length();i++){
        QJsonObject temp;

        temp["name"] = backend.stocklist.at(i);
        temp["maxlevels"] = 5;

        arr.append(temp);
    }
    QJsonObject list1;
    list1["list"] = arr;

    return list1;
}

Backend * Chartdata::getdata(){
    return &backend;
}

int Chartdata::onLogin(QString user){    
    user = user.toLower();
    user = user.simplified();
    user.replace(" ", "");
    user.replace("/", "");
    user.replace("\\", "");
    user.replace(".", "");
    user.replace("“", "");
    user.replace("*", "");
    user.replace("<", "");
    user.replace(">", "");
    user.replace(":", "");
    user.replace("|", "");
    user.replace("?", "");
    user.replace("$", "");

    qDebug()<<user<<"\\";

    database.setUser(user);
    database.stocklist = backend.stocklist;
    database.run();
    backend.addDatabse(&database);
    QObject::connect(this,SIGNAL(addData(int)), &backend,SLOT(add_data(int)));
    backend.addPopupList(&all_popups_list);

    backend.trigPopupList(&trig_popups_list);
    backend.get_all_popup_conditions();
    return 1;
}
