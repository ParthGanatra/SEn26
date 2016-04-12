#ifndef ELLIOTT_H
#define ELLIOTT_H


#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QString>
#include<Vector>
#include<QJason>

struct StockPrice{
    double high,low,open,close,volume;
    double time;
    double rsi,cci,ma,soD,soK;
    StockPrice(double o,double c,double h,double l,double t,double v = 0):high(h),close(c),open(o),low(l),volume(v),time(t){
    }
};

class Elliott : public QObject
{
    Q_OBJECT
public:
    vector<double> prices;
    vector<int> wavecount[MAXLEVEL];
    void addPoints(double* price,int size);
    double maxLen[MAXLEVEL];
    double minLen[MAXLEVEL];
    void init();
private:
    void assignWavecount(int start,int end, int level);
};



#endif // ELLIOTT_H
