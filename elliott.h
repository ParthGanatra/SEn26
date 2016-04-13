#ifndef ELLIOTT_H
#define ELLIOTT_H


#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QString>
#include<vector>
#include<QJsonObject>
using namespace std;

#define MAXLEVEL 10

class Elliott : public QObject
{
    Q_OBJECT
public:
    explicit Elliott(QObject *parent = 0);
    struct StockPrice{
        double high,low,open,close,volume;
        int time;
        string date;
        double rsi,cci,ma,soD,soK;
        StockPrice(double o,double c,double h,double l,int t,string d,double v = 0):high(h),close(c),open(o),low(l),volume(v),time(t),date(d){
        }
    };

    vector<double> prices;
    vector<int> wavecount[MAXLEVEL];
    void addPoints(vector<double> price);
    double maxLen[MAXLEVEL];
    double minLen[MAXLEVEL];
    void init();
private:
    void assignWavecount(int start,int end, int level);
};



#endif // ELLIOTT_H
