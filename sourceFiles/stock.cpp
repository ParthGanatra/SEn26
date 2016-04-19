#include "stock.h"
#include <QJsonObject>
#include <QString>
#include<vector>

using namespace std;

Stock::Stock(QObject *parent) :
    QObject(parent)
{
}

void Stock::addData(StockPrice & val){
    if(prices.size()==lookBackTime)
        prices.erase(prices.begin());
    prices.push_back(val);
    //    computeCCI();
    //    computeMA();
    //    computeRSI();
    //    computeSO();

}
double Stock::computeCCI(){
    //    qDebug() << "CCI in";
    if(prices.size()<lookBackTime)
        return -1000;
    //    qDebug() << "CCI 22";
    double avg = 0;
    double deviation = 0;
    int last = prices.size()-1;
    double deviatiion = 0;
    for(int i = 0; i < prices.size() ; i++)
        avg += (prices[i].high + prices[i].low + prices[i].close)/3/lookBackTime;
    for(int i = 0; i < prices.size() ; i++)
        deviation += abs(avg - ((prices[i].high + prices[i].low + prices[i].close)/3));
    prices[last].cci = ((prices[last].high + prices[last].low + prices[last].close)/3 - avg) / (0.15 * deviation);
    //    qDebug() << "CCI "<< prices[last].cci;
    return prices[last].cci;
}

double Stock::computeRSI(){
    double change = prices[prices.size()-1].close - prices[prices.size()-2].close;
    double curGain = 0;
    double curLoss = 0;
    if(change > 0)
        curGain = change;
    else
        curLoss = -change;
    if(prices.size()<lookBackTime){
        rsiAvgGain += change / lookBackTime;
        return -1000;
    }
    else{
        rsiAvgGain = (rsiAvgGain * 13 + curGain)/14;
        rsiAvgLoss = (rsiAvgLoss * 13 + curLoss)/14;
        double rs = rsiAvgGain / rsiAvgLoss;
        prices[prices.size()-1].rsi = 100 - (100 / (1 + rs));
        return prices[prices.size()-1].rsi;
    }
}
double Stock::computeMA(){
    double total = 0;
    for(int i=0;i<prices.size();i++)
        total += prices[i].close;
    double avg = total/prices.size();
    prices[prices.size()-1].ma = avg;
    return prices[prices.size()-1].ma;
}
double Stock::computeSO(){
    StockPrice st = prices[prices.size()-1];
    double max = 0;
    double min = 1e10;
    for(int i = 0;i < prices.size();i++){
        if(max<prices[i].close)
            max = prices[i].close;
        if(min>prices[i].close)
            min = prices[i].close;
    }
    st.soK =  (st.close - min)/(max - min);
    if(prices.size()>3){
        st.soD = prices[prices.size()-1].soK + prices[prices.size()-2].soK +prices[prices.size()-3].soK;
        st.soD /= 3;
    }
    return st.soD;
}
