#include "backend.h"
#include <QJsonObject>
#include <QString>

Backend::Backend(QObject *parent) :
    QObject(parent)
{
}


void Backend::init(){
    vector<QString> stock_name;

}

void Backend::add_data(QJsonObject data){

//    QString stock_name;  //CHANGE here according to jason.
//    double index=get_index(stock_name);
//    double high=data.high;
//    double low=data.low;
//    double open=data.open;
//    double close=data.close;
//    double time=data.time;
//    stocks[index].prices.add_point(new StockPrice(open,close,high,low,time));
    //call signal for changing in db
    //check for popup

}

void Backend::change_pop_condition(QString stock, bool gret, double thr){
//     condition[get_index(stock)]=gret;
//     threshold[get_index(stock)]=thr;
}

void Backend::get_elliott_count(QString stock, int start, int end, int lev){
    Elliott e;
    emit get_data();

}

//void Backend::remove_popup_data(QString stock, QString indicator, QString condition){

//}

void Backend::set_data(QJsonArray data){

}

int Backend::get_index(QString stock){

}

void Backend::add_popup_data()
{
    for(int i=0;i<5;i++){
        QJsonObject temp1;
        temp1["stock"] = "STOCK1";
        temp1["indicator"] = "INDICATOR1";
        temp1["condition"] = "CONDITION1";
        if(i==2){
            temp1["stock"] = "STOCK112";
            temp1["indicator"] = "INDICATOR1123";
            temp1["condition"] = "CONDITION1132";
        }
        Popup_data.append(temp1);
    }
}
