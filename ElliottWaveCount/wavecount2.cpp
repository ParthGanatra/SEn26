//#include <stdio.h>
//#include "wavecount.h"
//#include "wave_description.h"
//#include "rules_check.h"
//#include "util.h"
//#include <vector>
//# include <iostream>
//# include <algorithm>
//# include <cstdio>
//# include <cstdlib>
//# include <ctime>
//# include <cmath>
//# include <set>
//# include <vector>
//# include <map>
//# include <queue>
//#define MAXLEVEL 10
//#define MAXLEN 100000
//#define pb push_back
//#define mp make_pair
//#define delta 1.2
//
//#define WAVETYPES 22
//#define impulse 0
//#define leading_diagonals 1
//#define diagonals 2
//#define zigzag 3
//#define flat 4
//#define double_zigzag 5
//#define tripple_zigzag 6
//#define double_threes 7
//#define tripple_threes 8
//#define c_traingle 9
//#define e_triangle 10
//#define MAXSIZE 500
//
//
//using namespace std;
//
//class Wavecount{
//	  public:
//	  vector<double> prices;
//	  vector < vector <int> > wavecount;
//	  
//	  private:
//	  vector< vector <int> >  dp[MAXLEVEL][22][5];
//	  vector< vector <int> >  subwave[MAXLEVEL][22][5];
//	  vector<Monowave> monowave;
//	  
//	  public:
//	  void add_point(double price){
//	  	   if(prices.size()==MAXSIZE)
//	  	   {
//			    prices.erase(prices.begin());
// 				remove_first_point();
//		   }
//		   if(!add_point_in_monowave(price)) return;
//		   check_dp();
//		   find_waves(MAXLEVEL-1,0,monowave.size()-1);
//	  }
//	  private:
//  	  void remove_first_point(){
//  	       if(monowave[0].startindex==monowave[0].endindex){
//  	          monowave.erase(monowave.begin());
//  	          for(int i=0;i<MAXLEVEL;i++)
//  	             for(int j=0;j<22;j++)
//  	                for(int k=0;k<5;k++){
//  	                   dp[i][j][k].erase(dp[i][j][k].begin());
//  	                   subwave[i][j][k].erase(subwave[i][j][k].begin());
//                    }
//		   }
//		   else
//		      monowave[0].startindex++;
//           for(int i=0;i<monowave.size();i++){
//              monowave[i].startindex--;
//              monowave[i].endindex--;
//		   }
//      }
//  	  bool add_point_in_monowave(double price){
// 	       if(monowave.size()==0)
// 	          monowave.push_back(Monowave(0,0));
//           else{
//       		    int last = monowave.size()-1;
//       		   	int dir=prices[monowave[last].endindex]-prices[monowave[last].startindex];
//				int current_dir=price-prices[monowave[last].endindex];
//				
//				if((current_dir<=0 && dir<=0 )||(current_dir>=0 && dir>=0 )){
//					monowave[monowave.size()-1].endindex++;
//					return false;
//				}
//				else{
//					monowave.push_back(Monowave(monowave[monowave.size()-1].endindex,monowave[monowave.size()-1].endindex+1));
//					return true;
//				}
//		   }
//  	  }
//	  void check_dp(){
//         for(int wave_number = 0; wave_number<22;wave_number++){
//		    for(int ind=4;ind>=0;ind--){
//		       	
//			    for(int i=0;i<dp[0][wave_number][0].size();i++){
//		   	 	   dp[0][wave_number][0][i].push_back(-1);
//		   	 	   subwave[0][wave_number][0][i].push_back(-1);
//			 	}
//				vector<int> tmp;
//				tmp.push_back(-1);
//				dp[0][wave_number][0].push_back(tmp);
//		    	int j= dp[0][wave_number][0].size()-1;
//	       		int i= j - 4;
//	       		int x = i;
//	       		if(sub_wave[wave_number/2][3].size()==0)
//	       		   i=j-2;
//    	        vector<double> zero_points;
//		    	zero_points.push_back(prices[monowave[i].startindex]);
//		    	for(i;i<=j;i++)
//		    	   zero_points.push_back(prices[monowave[i].endindex]);
//   	            
//		    	if(check_rule(zero_points,wave_number))
//		    	   dp[0][wave_number][0][x][-x+ j]=x+1;
//            }
//         }
//         for(int l = 1; l<MAXLEVEL ; l++){
//			 for(int wave_number = 0; wave_number<22;wave_number++){
//			    for(int ind=4;ind>=0;ind--){
//		     	   for(int i=0;i<dp[0][wave_number][0].size();i++){
//	   		   	      dp[l][wave_number][ind][i].push_back(-1);
//			       }
//			       vector<int> tmp;
//	               tmp.push_back(-1);
//				   dp[l][wave_number][ind].push_back(tmp);
//		           
//				   for(int i=0;i<dp[l][wave_number][ind].size();i++){
//	                  int j=dp[l][wave_number][ind].size()-1;
//	                  bool done=false;
//					  for(int k=i;k<=j && !done;k++){
//	              		  for(int sub=0;sub<sub_wave[wave_number/2][ind].size() && !done ;sub++){
//	              		     if(dp[l-1][sub_wave[wave_number/2][ind][sub]][0][i][-i+ k]==-1) continue;;
//	                         int maxindex=4;
//	                         if(sub_wave[wave_number/2][3].size()==0)
//	                            maxindex=2;
//							 if(ind<maxindex && dp[l][wave_number][ind+1][k+1][-k-1+j]==-1) continue;
//					         if(ind==0){
//		                        vector<double> points;
//		                        points.push_back(prices[monowave[i].startindex]);
//		                        points.push_back(prices[monowave[i].endindex]);
//		                        int x=dp[l][wave_number][1][k+1][-k-1+j];
//		                        points.push_back(prices[monowave[x].endindex]);
//		                        x=dp[l][wave_number][2][x+1][-x-1+j];
//		                        points.push_back(prices[monowave[x].endindex]);
//		                        if(maxindex==4){
//		                           x=dp[l][wave_number][3][x+1][-x-1+j];
//		                           points.push_back(prices[monowave[x].endindex]);
//		                           x=dp[l][wave_number][4][x+1][-x-1+j];
//		                           points.push_back(prices[monowave[x].endindex]);
//								}
//								if(!check_rule(points,wave_number)) continue;
//							 }
//							 dp[l][wave_number][ind][i][-i+ j]=k;
//		                     done = true;
//	              	      }
//					  }
//				   }
//				}
//			 }
//		 }
//      }
//	  void find_waves(int level,int i,int j){
//	  	   for(int start=i;start<=j;start++){
//	  	   	   for(int wave_number=0;wave_number<22;wave_number++){
//	  	       	   for(int end= start;end<=j;end++){
//	  	       	       if(dp[level][wave_number][0][start][end]!=-1){
//	  	       	           assign_wavecount(start,end,level,wave_number);
//	  	       	           if(level>0)
//	  	       	              find_waves(level-1,i,start-1);
//	       	               if(end<j)
//	       	               find_waves(level,start+1,j);
//	       	               return;
//				       }
//			       }
//	  	       }
//		   }
//		   if(level>0)
//		      find_waves(level-1,i,j);
//	  }
//	  void assign_wavecount(int i,int j, int level,int wave_number){
//	  	   int ind=0;
//	 	   for(int x=i;x<=j;ind++){
//  	          int k=dp[level][wave_number][ind][x][j];
//   			  if(level>0)
//	       	     assign_wavecount(x,k,level-1,sub_wave[wave_number][ind]);
//              x=k+1;
//			  wavecount[monowave[k]].push_back(ind+1);
//           }
//      }
//};
//

