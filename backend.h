#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QString>
#include <stock.h>
#include <elliott.h>
#include "database.h"
using namespace std;

class Backend : public QObject
{
    Q_OBJECT

    QJsonArray Popup_data;



public:
    explicit Backend(QObject *parent = 0);
    int no_of_stocks;
    Database db;
    void init();

    vector<Stock> stocks;
    vector<bool> condition;
    vector<double> threshold;
signals:
    void pop_satisfied(QJsonObject popup);  //add data to give to popup.
    void add_indicator_data(QJsonArray indicator_data);  //jason array containing the indiactor data.
    void get_data();
    void set_elliott_count(int* count);

public slots:
    void add_data(QJsonObject data);  //notification as data came.
    void set_data(QJsonArray data);  //set data for elliott.
    void change_pop_condition(QString stock, bool gret, double thr); // data consisting the change of thresold.
//    void add_popup_data(QString s, QString i, QString c);
    void add_popup_data();
//    void remove_popup_data(QString stock);
    void get_elliott_count(QString stock, int start, int end, int lev);
    //QJsonArray get_Popup_data();
    //int get_Popup_size();
    int get_index(QString stock);
private:
    void checkConditions(StockPrice & sp);
};


#endif // BACKEND_H
