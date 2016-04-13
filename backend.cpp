#include "backend.h"
#include <QJsonObject>
#include <QString>
#include "stock.h"
#include "elliott.h"
#include <QJsonDocument>
using namespace std;



Backend::Backend(QObject *parent) :
    QObject(parent)
{

        indlist.append("RSI");
        indlist.append("CCI");
        indlist.append("MA");
        indlist.append("SO");
}


void Backend::init(){
    vector<QString> stock_name;

}

void Backend::add_data(QStringList data){           // count other indicators and pass it to databse
    for(int i=0;i<data.size();i++){
        QString str = data.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        int t = json["index"].toInt();
        string name = json["name"].toString().toStdString();
        string date = json["date"].toString().toStdString();
        double o = json["open"].toDouble();
        double c = json["close"].toDouble();
        double h = json["high"].toDouble();
        double l = json["low"].toDouble();
        double v = json["volume"].toDouble();
        int index = get_index(name);
        StockPrice sp(o,c,h,l,t,date,v);
        stocks[index].addData(sp);



        QJsonObject tmp;
        tmp["index"] = sp.time;
        tmp["date"] = QString::fromStdString(sp.date);
        tmp["name"] = QString::fromStdString(name);
        tmp["rsi"] = sp.rsi;
        tmp["cci"] = sp.cci;
        tmp["ma"] = sp.ma;
        tmp["so"] = sp.soD;

        //      db.storeIndicators(tmp);      // call databse method for storing indicators
    }
}
// popup json : name,indicator,condition,threshold
void Backend::checkConditions(StockPrice & sp,string name){ // check popup conditions and send signal for popup to frontend
    QStringList conditions;
    //    conditions = db.getConditions(name,"rsi");
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
    //    conditions = db.getConditions(name,"cci");
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
    //    conditions = db.getConditions(name,"ma");
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
    //    conditions = db.getConditions(name,"so");
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

//void Backend::change_pop_condition(QString stock, bool gret, double thr){

//}

void Backend::get_elliott_count(QString stock, int start, int end, int lev){
    QStringList data = db.getTickInterval(stock,start,end);
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
    vector<int> wc = e.wavecount[lvl-1];
    emit set_elliott_count(wc);
}
void Backend::remove_popup_condition(QString stock,QString indicator,QString condition,QString threashold){
    QJsonObject tmp;
    tmp["name"] =  stock;
    tmp["indicator"] =  indicator;
    tmp["condition"] =  condition;
    tmp["threashold"] =  threashold;

}
void Backend::add_popup_condition(QString data){
    db.add_popup_condition(data);
}

int Backend::get_index(string stock){
    return hmap[stock] ;
}

