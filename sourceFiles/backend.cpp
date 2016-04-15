#include "backend.h"
#include <QJsonObject>
#include <QString>
#include <vector>
#include "stock.h"
#include "elliott.h"
#include <QJsonDocument>
#include <QFile>
#include "all_popups_model.h"

using namespace std;



Backend::Backend(QObject *parent) :
    QObject(parent)
{
    indlist.append("RSI");
    indlist.append("CCI");
    indlist.append("MA");
    indlist.append("SO");


    QFile file("qml/StockAnalyser/To_Dump/stocklist");               // Enter your own path

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

void Backend::addPopupList(QList<QObject*> *popups_list)
{
    all_popups_list = popups_list;
}

void Backend::trigPopupList(QList<QObject*> *popups_list)
{
    trig_popups_list = popups_list;
}
//void Backend::add_data(QStringList data){           // count other indicators and pass it to databse
//    for(int i=0;i<data.size();i++){
//        QString str = data.at(i);

void Backend::addDatabse(Database *temp){
    db = temp;
}

void Backend::add_data(QStringList data){// count other indicators and pass it to databse
    int ind = 0;
    for(int i=0;i<stocklist.size();i++){
        QString str = db->getTick(ind,stocklist.at(i));
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        int t = json["index"].toString().toInt();
        string name = stocklist.at(i).toStdString();
        string date = json["date"].toString().toStdString();
        double o = json["open"].toString().toDouble();
        double c = json["close"].toString().toDouble();
        double h = json["high"].toString().toDouble();
        double l = json["low"].toString().toDouble();
        double v = json["volume"].toString().toDouble();
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
        double threshold = json["threshold"].toString().toDouble();
        if(json["condition"].toString().compare(">")==0){
            if(sp.rsi>threshold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "rsi";
                tmp["value"] = sp.rsi;

                trig_popups_list->append(new All_Popups_Model(QString::fromStdString(name),QString::fromStdString("rsi"),json["condition"].toString(),json["threshold"].toString()));
                emit trigPopupsListChanged();
            }
        }
        else{
            if(sp.rsi<threshold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "rsi";
                tmp["value"] = sp.rsi;

                trig_popups_list->append(new All_Popups_Model(QString::fromStdString(name),QString::fromStdString("rsi"),json["condition"].toString(),json["threshold"].toString()));
                emit trigPopupsListChanged();
            }
        }
    }
    //    conditions = db->getConditions(name,"cci");
    conditions = db->getallpopupscondition(QString::fromStdString(name),QString::fromStdString("cci"));
    for(int i=0;i<conditions.size();i++){
        QString str = conditions.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        double threshold = json["threshold"].toString().toDouble();
        if(json["condition"].toString().compare(">")==0){
            if(sp.cci>threshold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "cci";
                tmp["value"] = sp.cci;
                trig_popups_list->append(new All_Popups_Model(QString::fromStdString(name),QString::fromStdString("cci"),json["condition"].toString(),json["threshold"].toString()));
                emit trigPopupsListChanged();
            }
        }
        else{
            if(sp.cci<threshold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "cci";
                tmp["value"] = sp.cci;
                trig_popups_list->append(new All_Popups_Model(QString::fromStdString(name),QString::fromStdString("cci"),json["condition"].toString(),json["threshold"].toString()));
                emit trigPopupsListChanged();
            }
        }
    }
    //    conditions = db->getConditions(name,"ma");
    conditions = db->getallpopupscondition(QString::fromStdString(name),QString::fromStdString("ma"));
    for(int i=0;i<conditions.size();i++){
        QString str = conditions.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        double threshold = json["threshold"].toString().toDouble();
        if(json["condition"].toString().compare(">")==0){
            if(sp.ma>threshold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "ma";
                tmp["value"] = sp.ma;
                trig_popups_list->append(new All_Popups_Model(QString::fromStdString(name),QString::fromStdString("ma"),json["condition"].toString(),json["threshold"].toString()));
                emit trigPopupsListChanged();
            }
        }
        else{
            if(sp.ma<threshold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "ma";
                tmp["value"] = sp.ma;
                trig_popups_list->append(new All_Popups_Model(QString::fromStdString(name),QString::fromStdString("ma"),json["condition"].toString(),json["threshold"].toString()));
                emit trigPopupsListChanged();
            }
        }
    }
    //    conditions = db->getConditions(name,"so");
    conditions = db->getallpopupscondition(QString::fromStdString(name),QString::fromStdString("so"));
    for(int i=0;i<conditions.size();i++){
        QString str = conditions.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        double threshold = json["threshold"].toString().toDouble();
        if(json["condition"].toString().compare(">")==0){
            if(sp.soD>threshold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "so";
                tmp["value"] = sp.soD;
                trig_popups_list->append(new All_Popups_Model(QString::fromStdString(name),QString::fromStdString("so"),json["condition"].toString(),json["threshold"].toString()));
                emit trigPopupsListChanged();
            }
        }
        else{
            if(sp.soD<threshold){
                QJsonObject tmp;
                tmp["name"] = QString::fromStdString(name);
                tmp["indicator"] = "so";
                tmp["value"] = sp.soD;

                trig_popups_list->append(new All_Popups_Model(QString::fromStdString(name),QString::fromStdString("so"),json["condition"].toString(),json["threshold"].toString()));
                emit trigPopupsListChanged();
            }
        }
    }
}


QJsonArray Backend::get_elliott_count(QString stock, int start, int end, int lev){
    QStringList data = db->getTickInterval(start,end,stock);
    vector<double> price;
    qDebug()<<stock<<start<<end<<lev;
    for(int i=0;i<data.size();i++){
        QString str = data.at(i);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();
        qDebug()<<json << "  **********  " << str;
//        int t = json["index"].toInt();
//        string name = json["name"].toString().toStdString();
//        string date = json["date"].toString().toStdString();
        QString temp = json["close"].toString();
        double c = temp.toDouble();
        qDebug() <<"prices "<< c << " "<<temp;
        price.push_back(c);
    }

    e.addPoints(price);
    vector<int> wc = e.wavecount[lev];

    QJsonArray output;
    for(int i = 0; i<wc.size();i++){
        QJsonObject temp;
        qDebug() << wc[i];
        temp["value"] = wc[i];
        output.append(temp);
    }

    return output;
}
void Backend::remove_popup_condition(QString stock,QString indicator,QString condition,QString threshold){
    qDebug() << "Removing popup condition";
    //    all_popups_list->removeAt(2);
    for(int i= 0; i < all_popups_list->size();i++){
        All_Popups_Model* popup = (All_Popups_Model *)(all_popups_list->at(i));
        if(popup->stock() == stock && popup->indicator()==indicator && popup->condition()==condition && popup->threshold()==threshold){
            all_popups_list->removeAt(i);
            i--;
        }
    }


    emit allPopupsListChanged();
        db->removePopup(stock,indicator,condition,threshold);
}
void Backend::remove_popup_trigger(QString stock,QString indicator,QString condition,QString threshold){
    qDebug() << "Removing popup condition";
    //    all_popups_list->removeAt(2);
    for(int i= 0; i < trig_popups_list->size();i++){
        All_Popups_Model* popup = (All_Popups_Model *)(trig_popups_list->at(i));
        if(popup->stock() == stock && popup->indicator()==indicator && popup->condition()==condition && popup->threshold()==threshold){
            trig_popups_list->removeAt(i);
            i--;
            qDebug() << stock;
        }
    }


    emit trigPopupsListChanged();
//        db->removePopup(stock,indicator,condition,threshold);
}
void Backend::add_popup_condition(QString stock,QString indicator,QString condition,QString threshold){
//    trig_popups_list->append(new All_Popups_Model(stock,indicator,condition,threshold));
//    emit trigPopupsListChanged();
    all_popups_list->append(new All_Popups_Model(stock,indicator,condition,threshold));
    emit allPopupsListChanged();
    qDebug() << "Added new condition for popup";
    //    db.add_popup_condition(data);
//        db->addPopup(stock,indicator,condition,threshold);
}
void Backend::get_all_popup_conditions(){
    for(int i=0;i<stocklist.size();i++){
        QString stock = stocklist.at(i);
        QStringList conditions= db->getallpopupscondition(stock,QString::fromStdString("rsi"));
        for(int i=0;i<conditions.size();i++){
            QString str = conditions.at(i);
            QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject json = doc.object();
            all_popups_list->append(new All_Popups_Model(json["name"].toString(),json["indicator"].toString(),json["condition"].toString(),json["threshold"].toString()));
        }
        conditions= db->getallpopupscondition(stock,QString::fromStdString("cci"));
        for(int i=0;i<conditions.size();i++){
            QString str = conditions.at(i);
            QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject json = doc.object();
            all_popups_list->append(new All_Popups_Model(json["name"].toString(),json["indicator"].toString(),json["condition"].toString(),json["threshold"].toString()));
        }
        conditions= db->getallpopupscondition(stock,QString::fromStdString("ma"));
        for(int i=0;i<conditions.size();i++){
            QString str = conditions.at(i);
            QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject json = doc.object();
            all_popups_list->append(new All_Popups_Model(json["name"].toString(),json["indicator"].toString(),json["condition"].toString(),json["threshold"].toString()));
        }
        conditions= db->getallpopupscondition(stock,QString::fromStdString("so"));
        for(int i=0;i<conditions.size();i++){
            QString str = conditions.at(i);
            QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject json = doc.object();
            all_popups_list->append(new All_Popups_Model(json["name"].toString(),json["indicator"].toString(),json["condition"].toString(),json["threshold"].toString()));
        }
    }
    emit allPopupsListChanged();
}

int Backend::get_index(string stock){
    return hmap[stock] ;
}

QQmlListProperty<QObject> Backend::getAllPopups(){
    return QQmlListProperty<QObject>(this, *all_popups_list);
}

QQmlListProperty<QObject> Backend::getTrigPopups(){
    return QQmlListProperty<QObject>(this, *trig_popups_list);
}
