#ifndef BACKEND1_H
#define BACKEND1_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QString>
#include <stock.h>
#include <elliott.h>

class Backend : public QObject
{
    Q_OBJECT

    QJsonArray Popup_data;



public:
    explicit Backend(QObject *parent = 0);
    int no_of_stocks;
    void init();
    int get_index(QString stock);
    vector<stock> stocks;
    vector<boolean> condition;
    vector<double> threshold;
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

};


#endif // BACKEND1_H
