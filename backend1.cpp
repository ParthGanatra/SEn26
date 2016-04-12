#include "backend1.h"
#include <QJsonObject>
#include <QString>

Backend::Backend(QObject *parent) :
    QObject(parent)
{
}

/*
    void init();
signals:
    void pop_satisfied(Qstring stock, QString ind, int value);  //add data to give to popup.
    void add_indicator_data(QJasonArray indicator_data);  //jason array containing the indiactor data.
    void get_data();
    void set_elliott_count(int* count);

public slots:
    void add_data(QJason data);  //notification as data came.
    void set_data(QJasonArray data);  //set data for elliott.
    void cahnge_pop_condition(QString stock, boolean gret, double thr); // data consisting the change of thresold.
    //void add_popup_data(QString s, QString i, QString c);
    void remove_popup_data(QString stock);
    void get_elliott_count(QString stock, int start, int end, int lev);
    //QJsonArray get_Popup_data();
    //int get_Popup_size();


*/

void Backend::init(){
    vector<QString> stock_name;

}

void Backend::add_data(QJason data){

    Qstring stock_name;  //CHANGE here according to jason.
    double index=get_index(stock_name);
    double high=data.high;
    double low=data.low;
    double open=data.open;
    double close=data.close;
    double time=data.time;
    stocks[index].prices.add_point(new StockPrice(open,close,high,low,time));
    //call signal for changing in db
    //check for popup

}

void Backend::cahnge_pop_condition(QString stock, boolean gret, double thr){
     condition[get_index(stock)]=gret;
     threshold[get_index(stock)]=thr;
}

void Backend::get_elliott_count(QString stock, int start, int end, int lev){
    Elliott e;
    emmit get_data();

}
void Backend::remove_popup_data(QString stock){

}

void Backend::set_data(QJasonArray data){

}

void Backend::get_index(QString stock){

}

