#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QString>
#include "stock.h"
#include <vector>
#include <QList>
#include "elliott.h"
#include "database.h"
#include <QQmlListProperty>
#include <QObject>
#include "all_popups_model.h"


class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> allpopupsmodel READ getAllPopups NOTIFY allPopupsListChanged)
    Q_PROPERTY(QQmlListProperty<QObject> trigpopupsmodel READ getTrigPopups NOTIFY trigPopupsListChanged)
    QJsonArray Popup_data;

public:
    explicit Backend(QObject *parent = 0);
    virtual ~Backend();
    int no_of_stocks = 0;

    Database *db;

    QStringList indlist;
    QStringList stocklist;

    QList<QObject*> *all_popups_list;
    QList<QObject*> *trig_popups_list;
    QQmlListProperty<QObject> getAllPopups();
    QQmlListProperty<QObject> getTrigPopups();

    Elliott e;
    Stock * stocks[100];
//    vector<bool> condition;
//    vector<double> threshold;


    void checkConditions(StockPrice & sp,string name);
    map<string,int> hmap;

signals:
    void pop_satisfied(QJsonObject popup);  //add data to give to popup.
    void add_indicator_data(QJsonArray indicator_data);  //json array containing the indiactor data.
//    void get_data();
    void set_elliott_count(vector<int> count);
    void allPopupsListChanged();
    void trigPopupsListChanged();

public slots:
    void add_data(int );  //notification as data came.

public slots:
    void addPopupList(QList<QObject*> *popups_list);
    void trigPopupList(QList<QObject*> *trig_popups_list);
    void get_all_popup_conditions();
//    void init();
    void addDatabse(Database *temp);

//    void set_data(QJsonArray data);  //set data for elliott.
//    void change_pop_condition(QString stock, bool gret, double thr); // data consisting the change of thresold.
//    void add_popup_data(QString s, QString i, QString c);
    void remove_popup_condition(QString stock,QString indicator,QString condition,QString threshold);
    void remove_popup_trigger(QString stock,QString indicator,QString condition,QString threshold);
    void add_popup_condition(QString stock,QString indicator,QString condition,QString threshold);
//    void add_popup_data();
//    void remove_popup_data(QString stock,QString ind);
    QJsonArray get_elliott_count(QString stock, int start, int end, int lev);
//  QJsonArray get_Popup_data();
//  int get_Popup_size();
    int get_index(string stock);
};


#endif // BACKEND_H
