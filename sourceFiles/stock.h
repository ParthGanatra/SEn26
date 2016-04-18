#ifndef STOCK_H
#define STOCK_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QString>
#include <vector>
#include<QJsonObject>
using namespace std;

struct StockPrice{
    double high,low,open,close,volume;
    int time;
    string date;
    double rsi= -1000,cci= -1000,ma=-1000,soD=-1000,soK=-1000;
    StockPrice(double o,double c,double h,double l,int t,string d,double v = 0):high(h),close(c),open(o),low(l),volume(v),time(t),date(d){
    }
};

class Stock : public QObject
{
    Q_OBJECT

public:
    explicit Stock(QObject *parent = 0);
    void addData(StockPrice & val);

    vector<StockPrice> prices;
    int lookBackTime = 14;
    double rsiAvgGain;
    double rsiAvgLoss;

    double computeRSI();
    double computeCCI();
    double computeMA();
    double computeSO();
};

#endif // STOCK_H
