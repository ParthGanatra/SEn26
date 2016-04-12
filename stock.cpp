#include "stock.h"
#include <QJsonObject>
#include <QString>
#include<vector.h>
using namespace std;
Stock::Stock(Object *parent) :
    QObject(parent)
{
}
void Stock::addData(StockPrice & val){
    prices.push_back(val);
    computeCCI();
    computeMA();
    computeRSI();
    computeSO();

}
void Stock::computeCCI(){
    if(prices.size()<lookBackTime)
           return;
    double avg = 0;
    double deviation = 0;
    int last = prices.size()-1;
    double deviatiion = 0;
    for(int i = 0; i < prices.size() ; i++)
       avg += (prices[i].high + prices[i].low + prices[i].close)/3/lookBackTime;
    for(int i = 0; i < prices.size() ; i++)
       deviation += abs(avg - ((prices[i].high + prices[i].low + prices[i].close)/3));
    prices[last].cci = ((prices[last].high + prices[last].low + prices[last].close)/3 - avg) / (0.15 * deviation);
}

void Stock::computeRSI(){
    double change = prices[prices.size()-1].close - prices[prices.size()-2].close;
    double curGain = 0;
    double curLoss = 0;
    if(change > 0)
       curGain = change;
    else
       curLoss = -change;
    if(prices.size()<lookBackTime){
       rsiAvgGain += change / lookBackTime;
    }
    else{
       rsiAvgGain = (rsiAvgGain * 13 + curGain)/14;
       rsiAvgLoss = (rsiAvgLoss * 13 + curLoss)/14;
       double rs = rsiAvgGain / rsiAvgLoss;
       prices[prices.size()-1].rsi = 100 - (100 / (1 + rs));
    }
}
void Stock::computeMA(){
    double total = 0;
    for(int i=0;i<prices.size();i++)
        total += prices[i].close;
    double avg = total/prices.size();
    prices[prices.size()-1].ma = avg;
}
void Stock::computeSO(){
    StockPrice st = prices[prices.size()-1];
    soHighestHigh = max(soHighestHigh , st.high);
    soLowestLow = max(soLowestLow , st.low);
    st.soK =  (st.close - soLowestLow)/(soHighestHigh - soLowestLow);
    if(prices.size()>3){
       st.soD = prices[prices.size()-1].soK + prices[prices.size()-2].soK +prices[prices.size()-3].soK;
       st.soD /= 3;
    }
}
