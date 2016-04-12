#include "elliott.h"
#include <QJsonObject>
#include <QString>
#include<vector.h>
#include <vector>
#include<stdio.h>
#define MAXLEVEL 10
#define impulseUp 0
#define impulseDown 1
#define correctiveUp 2
#define correctiveDown 3

using namespace std;
Stock::Stock(Object *parent) :
    QObject(parent)
{

    double phi = 1.618;
    double ratio = phi;
    double cur = ratio;
    for(int i=1;i<MAXLEVEL;i++){
       minLen[i] = cur;
       cur *= ratio;
    }
    for(int i=0;i< MAXLEVEL-1 ;i++)
       maxLen[i] = minLen[i+1];
    maxLen[MAXLEVEL-1] = 1e10;
    minLen[0] = 0;
}


//void Elliott::init(){
//     double phi = 1.618;
//     double ratio = phi;
//     double cur = ratio;
//     for(int i=1;i<MAXLEVEL;i++){
//        minLen[i] = cur;
//        cur *= ratio;
//     }
//     for(int i=0;i< MAXLEVEL-1 ;i++)
//        maxLen[i] = minLen[i+1];
//     maxLen[MAXLEVEL-1] = 1e10;
//     minLen[0] = 0;
//}
void Elliott::addPoints(double* price,int size){
    for(int i=0;i<MAXLEVEL;i++){
       wavecount[i].clear();
       for(int j=0;j<size;j++){
           wavecount[i].push_back(-1);
       }
    }
    prices.clear();
    for(int i=0;i<size;i++)
       prices.push_back(price[i]);
    assignWavecount(0,size-1,MAXLEVEL-1);
}

void Elliott::assignWavecount(int start,int end,int level){

   if(level<0 || start>=end || end>prices.size() || start<0)
      return;
   int max,min;
   max = start;
   min = start;
   int ind = 1;
   int x = start;
   bool increasing = false;
   if(prices[start+1] > prices[start] )
      increasing = true;
//   printf("%d %d %d\n",start,end,level);

   for(int i=start ; i<=end;i++){
       if(!increasing && prices[i] - prices[min] >= minLen[level]){
//          printf("----- %d %d %d\n",i,min,x);
//		  if(!increasing && -prices[min] + prices[x]>=minLen[level] && -prices[min] + prices[x] <= maxLen[level]){
              if(ind < 5)
              {
                 wavecount[level][min] = ind ;
                 ind++;
              }
//	      }
//	      else if(x!=0){
//   	          if(ind < 5)
//			  {
//			  	 wavecount[level][min] = ind ;
//	             ind++;
//	          }
//	      }
          assignWavecount(x , min , level-1);
          x = min;
          max = i;
          increasing = true;
       }
       else if(increasing && prices[max] - prices[i] >= minLen[level]){
//          printf("+++++ %d %d %d\n",i,max,x);
//		  if(increasing && prices[max] - prices[x]>=minLen[level] && prices[max] - prices[x] <= maxLen[level]){
              if(ind < 5)
              {
                 wavecount[level][max] = ind ;
                 ind++;
              }
//	      }
//	      else if(x!=0){
//   	          if(ind < 5)
//			  {
//			     wavecount[level][max] = ind ;
//	             ind++;
//	          }
//	      }
          assignWavecount(x , max , level-1);
          x = max;
          min = i;
          increasing = false;
       }

//	   printf("HERE\n");
       if(prices[max] < prices[i])
          max = i;
       if(prices[min] > prices[i])
          min = i;

   }
//   if(increasing && prices[end] - prices[x]>=minLen[level] && prices[end] - prices[x] <= maxLen[level])
    if(x!=start)
      wavecount[level][end] = ind ;
//   if(!increasing && -prices[end] + prices[x]>=minLen[level] && -prices[end] + prices[x] <= maxLen[level])
//      wavecount[level][end] = ind ;

   assignWavecount(x,end,level-1);
}
