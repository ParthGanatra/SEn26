#include "backend.h"
#include <QJsonObject>
#include <QString>
#include <vector>
#include "stock.h"
#include "elliott.h"
#include <QJsonDocument>
#include <QFile>
using namespace std;



Backend::Backend(QObject *parent) :
    QObject(parent)
{
        indlist.append("RSI");
        indlist.append("CCI");
        indlist.append("MA");
        indlist.append("SO");


        QFile file("stocklist");               // Enter your own path

        if (!file.open(QIODevice::ReadOnly)) {
               qDebug() << file.errorString();
               return;
        }

        while (!file.atEnd()) {
               stocklist.append(file.readLine());
        }

        for (int i=0;i<stocklist.size();i++)
        {
//            qDebug() << stocklist.at(i);
            hmap[stocklist.at(i).toStdString()] = i;

            stocks[i]=new Stock();
        }
}

Backend::~Backend()
{}

void Backend::addDatabse(Database *temp){
    db = temp;
}

void Backend::add_data(QStringList data){// count other indicators and pass it to databse
    int ind = 0;
    for(int i=0;i<stocklist.size();i++){
        QString str = db->getTick(ind,stocklist.at(i));
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        int t = json["index"].toInt();
        string name = stocklist.at(i).toStdString();
        string date = json["date"].toString().toStdString();
        double o = json["open"].toDouble();
        double c = json["close"].toDouble();
        double h = json["high"].toDouble();
        double l = json["low"].toDouble();
        double v = json["volume"].toDouble();
        int index = get_index(name);
        StockPrice sp(o,c,h,l,t,date,v);
        stocks[index]->addData(sp);

        checkConditions(sp,name);

        db->addIndicator(QString::number(sp.time),QString::fromStdString(sp.date),QString::fromStdString(name),QString::number(sp.rsi),QString::number(sp.cci),QString::number(sp.ma),QString::number(sp.soD));
//        db->storeIndicators(tmp);      // call databse method for storing indicators
    }
}
// popup json : name,indicator,condition,threshold
void Backend::checkConditions(StockPrice & sp,string name){ // check popup conditions and send signal for popup to frontend
    QStringList conditions;
    //    conditions = db->getConditions(name,"rsi");
    conditions = db->getallpopupscondition(QString::fromStdString(name),QString::fromStdString("rsi"));
    for(int i=0;i<conditions.size();i++){
        QString str = conditions.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        double threashold = json["threashold"].toDouble();
        if(json["condition"].toString().compare(">")==0){
            if(sp.rsi>threashold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "rsi";
                tmp["value"] = sp.rsi;
                emit pop_satisfied(tmp);
            }
        }
        else{
            if(sp.rsi<threashold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "rsi";
                tmp["value"] = sp.rsi;
                emit pop_satisfied(tmp);
            }
        }
    }
    //    conditions = db->getConditions(name,"cci");
    conditions = db->getallpopupscondition(QString::fromStdString(name),QString::fromStdString("cci"));
    for(int i=0;i<conditions.size();i++){
        QString str = conditions.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        double threashold = json["threashold"].toDouble();
        if(json["condition"].toString().compare(">")==0){
            if(sp.cci>threashold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "cci";
                tmp["value"] = sp.cci;
                emit pop_satisfied(tmp);
            }
        }
        else{
            if(sp.cci<threashold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "cci";
                tmp["value"] = sp.cci;
                emit pop_satisfied(tmp);
            }
        }
    }
    //    conditions = db->getConditions(name,"ma");
    conditions = db->getallpopupscondition(QString::fromStdString(name),QString::fromStdString("ma"));
    for(int i=0;i<conditions.size();i++){
        QString str = conditions.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        double threashold = json["threashold"].toDouble();
        if(json["condition"].toString().compare(">")==0){
            if(sp.ma>threashold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "ma";
                tmp["value"] = sp.ma;
                emit pop_satisfied(tmp);
            }
        }
        else{
            if(sp.ma<threashold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "ma";
                tmp["value"] = sp.ma;
                emit pop_satisfied(tmp);
            }
        }
    }
    //    conditions = db->getConditions(name,"so");
    conditions = db->getallpopupscondition(QString::fromStdString(name),QString::fromStdString("so"));
    for(int i=0;i<conditions.size();i++){
        QString str = conditions.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        double threashold = json["threashold"].toDouble();
        if(json["condition"].toString().compare(">")==0){
            if(sp.soD>threashold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "so";
                tmp["value"] = sp.soD;
                emit pop_satisfied(tmp);
            }
        }
        else{
            if(sp.soD<threashold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "so";
                tmp["value"] = sp.soD;
                emit pop_satisfied(tmp);
            }
        }
    }
}


QJsonArray Backend::get_elliott_count(QString stock, int start, int end, int lev){
    QStringList data = db->getTickInterval(start,end,stock);
    vector<double> price;

    for(int i=0;i<data.size();i++){
        QString str = data.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        int t = json["index"].toInt();
        string name = json["name"].toString().toStdString();
        string date = json["date"].toString().toStdString();
        double c = json["close"].toDouble();
        price.push_back(c);
    }

    e.addPoints(price);
    vector<int> wc = e.wavecount[lev-1];

    QJsonArray output;
    for(int i = 0; i<wc.size();i++){
        QJsonObject temp;
        temp["value"] = wc[i];
        output.append(temp);
    }
    return output;
}
void Backend::remove_popup_condition(QString stock,QString indicator,QString condition,QString threashold){
    db->removePopup(stock,indicator,condition,threashold);
}
void Backend::add_popup_condition(QString stock,QString indicator,QString condition,QString threashold){
    db->addPopup(stock,indicator,condition,threashold);
}

int Backend::get_index(string stock){
    return hmap[stock] ;
}

