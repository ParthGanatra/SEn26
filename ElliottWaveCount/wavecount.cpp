#include <stdio.h>
#include "wavecount.h"
#include "wave_description.h"
#include "rules_check.h"
#include "util.h"
#include <vector>
# include <iostream>
# include <algorithm>
# include <cstdio>
# include <cstdlib>
# include <ctime>
# include <cmath>
# include <set>
# include <vector>
# include <map>
# include <queue>
#define MAXLEVEL 10
#define MAXLEN 100000
#define pb push_back
#define mp make_pair
#define delta 1.2

#define WAVETYPES 22
#define impulse 0
#define leading_diagonals 1
#define diagonals 2
#define zigzag 3
#define flat 4
#define double_zigzag 5
#define tripple_zigzag 6
#define double_threes 7
#define tripple_threes 8
#define c_traingle 9
#define e_triangle 10
#define MAXSIZE 500


using namespace std;

      void Wavecount::add_point(double price){
		   if(prices.size()==MAXSIZE)
	  	   {
			    prices.erase(prices.begin());
 				remove_first_point();
		   }
		   prices.push_back(price);
		   if(!add_point_in_monowave(price)) return;
		   printf("point added\n");
		   check_dp();
		   printf("check dp done\n");
		   wavecount.clear();
		   for(int i=0;i<prices.size();i++){
		      vector<int> tmp;
		      tmp.push_back(-1);
			  wavecount.push_back(tmp);
		   }
//		   printf("here");
		   find_waves(MAXLEVEL-1,0,monowave.size()-1);
		   printf("final done\n");
	  }

  	  void Wavecount::remove_first_point(){
  	       if(monowave[0].startindex==monowave[0].endindex){
  	          monowave.erase(monowave.begin());
  	          for(int i=0;i<MAXLEVEL;i++)
  	             for(int j=0;j<22;j++)
  	                for(int k=0;k<5;k++){
  	                   dp[i][j][k].erase(dp[i][j][k].begin());
  	                   subwave_used[i][j][k].erase(subwave_used[i][j][k].begin());
                    }
		   }
		   else
		      monowave[0].startindex++;
           for(int i=0;i<monowave.size();i++){
              monowave[i].startindex--;
              monowave[i].endindex--;
		   }
      }
  	  bool Wavecount::add_point_in_monowave(double price){
  	  	   if(monowave.size()==0)
 	       {
 	       	   monowave.push_back(Monowave(0,0));
 	       	   return true;
           }
		   else{
 	       
       		    int last = monowave.size()-1;
       		   	int dir=prices[monowave[last].endindex]-prices[monowave[last].startindex];
				int current_dir=price-prices[monowave[last].endindex];
				
				if((current_dir<=0 && dir<=0 )||(current_dir>=0 && dir>=0 )){
					monowave[monowave.size()-1].endindex++;
					return false;
				}
				else{
					monowave.push_back(Monowave(monowave[monowave.size()-1].endindex,monowave[monowave.size()-1].endindex+1));
					return true;
				}
		   }
  	  }
	  void Wavecount::check_dp(){
         for(int wave_number = 0; wave_number<22;wave_number++){
//		       	printf("here 4");
			    for(int ind=4;ind>=0;ind--){
                    for(int i=0;i<dp[0][wave_number][ind].size();i++){
		   	 	        dp[0][wave_number][ind][i].push_back(-1);
		   	 	        subwave_used[0][wave_number][ind][i].push_back(-1);
                    }
//                 	printf("here 5");
		  			vector<int> tmp;
					tmp.push_back(-1);
					dp[0][wave_number][ind].push_back(tmp);
					
//					printf("here 6");
					vector<int> tmp2;
					tmp2.push_back(-1);
					subwave_used[0][wave_number][ind].push_back(tmp2);
			 	}
				
//			 	printf("here 7");
		    	int j= dp[0][wave_number][0].size()-1;
	       		int i= j - 4;
	       		
//			 	printf("here 8");
	       		
	       		if(sub_wave[wave_number/2][3].size()==0)
	       		   i=j-2;
	       		   
     		    int x = i;
    	        if(i<0)
    	           continue;
    	           
//			 	printf("here 9");
				vector<double> zero_points;
				
		    	zero_points.push_back(prices[monowave[i].startindex]);
		    	
//			 	printf("here 10\n\n\n");
				for(;i<=j;i++)
		    	{
//		    		printf("%d %d %d\n",i,j,monowave.size());
				   zero_points.push_back(prices[monowave[i].endindex]);
   	            }
//                printf("\n\n\nhere 11");
		    	if(check_rule(zero_points,wave_number)){
//	    		   printf("here 12");
		    	   dp[0][wave_number][0][x][-x+ j]=x;
		    	   dp[0][wave_number][1][x+1][-x-1+ j]=x+1;
		    	   dp[0][wave_number][2][x+2][-x-2+ j]=x+2;
		    	   if(x+3<j){
		    	      dp[0][wave_number][3][x+3][-x-3+ j]=x+3;
		    	      dp[0][wave_number][4][x+4][-x-4+ j]=x+4;
		           }
//    		       printf("here 13");
		        }
            
         }
//         printf("first loop done :)\n");
         for(int l = 1; l<MAXLEVEL ; l++){
			 for(int wave_number = 0; wave_number<22;wave_number++){
			    for(int ind=4;ind>=0;ind--){
//			    	printf("just entered\n");
		     	   for(int i=0;i<dp[l][wave_number][ind].size();i++){
	   		   	      dp[l][wave_number][ind][i].push_back(-1);
	   		   	      subwave_used[l][wave_number][ind][i].push_back(-1);
			       	  													 }
//			       printf("here");
			       vector<int> tmp;
	               tmp.push_back(-1);
				   dp[l][wave_number][ind].push_back(tmp);
//		           printf("here2");
		           vector<int> tmp2;
				   tmp2.push_back(-1);
				   subwave_used[l][wave_number][ind].push_back(tmp2);
//		           printf("here3\n\n\n");
				   for(int i=0;i<dp[l][wave_number][ind].size();i++){
//	                  printf("for 1");
					  int j=dp[l][wave_number][ind].size()-1;
	                  bool done=false;
//	                  printf("for 2");
					  for(int k=i;k<=j && !done;k++){
//					  	printf("%d %d\n",k,sub_wave[wave_number/2][ind].size());
	              		  for(int sub=0;sub<sub_wave[wave_number/2][ind].size() && !done ;sub++){
//	              		     printf("if 1");
				             if(dp[l-1][sub_wave[wave_number/2][ind][sub]][0][i][-i+ k]==-1) continue;;
	                         int maxindex=4;
//	                         printf("if 2");
							 if(sub_wave[wave_number/2][3].size()==0)
	                            maxindex=2;
							 
//				   			 printf("if 3");
				   			 
							 if(ind<maxindex && (k+1-j>0 || dp[l][wave_number][ind+1][k+1][-k-1+j]==-1)) continue;
					         
//				   			 printf("if 4");
							 if(ind==0){
		                        vector<double> points;
		                        points.push_back(prices[monowave[i].startindex]);
		                        points.push_back(prices[monowave[k].endindex]);
		                        int x=dp[l][wave_number][1][k+1][-k-1+j];
		                        points.push_back(prices[monowave[x].endindex]);
		                        x=dp[l][wave_number][2][x+1][-x-1+j];
		                        points.push_back(prices[monowave[x].endindex]);
		                        if(maxindex==4){
		                           x=dp[l][wave_number][3][x+1][-x-1+j];
		                           points.push_back(prices[monowave[x].endindex]);
		                           x=dp[l][wave_number][4][x+1][-x-1+j];
		                           points.push_back(prices[monowave[x].endindex]);
								}
								if(!check_rule(points,wave_number)) continue;
							 }
//							 printf("if 5");
							 dp[l][wave_number][ind][i][-i+ j]=k;
							 subwave_used[l][wave_number][ind][i][-i+ j]=sub;
		                     done = true;
	              	      }
					  }
				   }
//				   printf("\n\n\nhere4");
				}
			 }
		 }
//         printf("finally done :)");

      }
	  void Wavecount::find_waves(int level,int i,int j){
	  	   for(int start=i;start<=j;start++){
	  	   	   for(int wave_number=0;wave_number<22;wave_number++){
	  	       	   for(int end= start;end<=j;end++){
	  	       	       
//						printf("if 1");	
			            if(dp[level][wave_number][0][start][-start+end]!=-1){
	  	       	       	   printf("herehere %d %d %d %d %d\n",level,wave_number,start,end,dp[level][wave_number][0][start].size());
	  	       	           assign_wavecount(start,end,level,wave_number);
//	  	       	       	   printf("here3");
	  	       	           if(level>0)
	  	       	              find_waves(level-1,i,start-1);
	       	               if(end<j)
	       	               find_waves(level,end+1,j);
//	       	               printf("here2");
	       	               return;
				       }
//				       printf("endif 1");
			       }
	  	       }
		   }
		   if(level>0)
		      find_waves(level-1,i,j);
	  }
	  void Wavecount::assign_wavecount(int i,int j, int level,int wave_number){
	  	   int ind=0;
//	  	   printf("\nawawaw %d %d %d %d\n",i,j,level,wave_number);
	 	   for(int x=i;x<=j;ind++){
//	 	   	  printf("aw 1");
  	          int k=dp[level][wave_number][ind][x][-x+j];
//	 	   	  printf("aw 2\n\n\n");
  	          if(k>j)
  	             break;
//  	             printf("%d %d %d %d",i,j,level,subwave_used[level][wave_number][ind][i][j]);
   			  if(level>0 && subwave_used[level][wave_number][ind][i][-i+j]!=-1)
	       	     assign_wavecount(x,k,level-1,sub_wave[wave_number/2][ind][subwave_used[level][wave_number][ind][i][-i+j]]);
              x=k+1;
//	 	   	  printf("\n\naw 3    %d %d %d",wavecount.size(),k,ind);
			  wavecount[monowave[k].endindex].push_back(ind+1);
//	 	   	  printf("aw 4");
           }
//           printf("aw done");
      }














































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
//int levelDiff[MAXLEVEL];
//
//vector<Monowave> mono_wave;
//int ** addwavecount(double * p, int n){
//	vector <vector <int> > dp[MAXLEVEL][22][5];   //1: start index 2:end index 3:wave name 4:wave number 5:level 
//	
//}
//vector< vector<int> > ans;
//void findLevel(vector < vector< int > >*** dp,int i,int j,int level){
//   	 
//   	 
//}
//void assignLevel(vector < vector< int > >*** dp,int i,int j,int level,int wave_number,vector<monowave> mono_wave){
//	 int ind=0;
//	 for(int x=i;x<=j;ind++){
//	    int k=dp[level][wave_number][ind][x][j];
//	    if(level>0)
//	       assignlevel(dp,x,k,level-1,sub_wave[wave_number][ind],mono_wave);
//		x=k+1;
//		ans[mono_wave[k]].push_back(ind+1);
//	 }
//	 
//}
//
//
//
//void addPoint(double price,vector <double>  p, vector < vector< int > >*** dp,vector<monowave> mono_wave){
//	 if(!addmonowave(price,mono_wave))
//	     return;
//   /*	 if(p.size()==MAXSIZE) 
//	    p.erase(p.begin());
//	 p.push_back(price);*/
//	 for(int wave_number = 0; wave_number<22;wave_number++){
//        for(int ind=4;ind>=0;ind--){
//       	   if(dp[0][wave_number][ind].size()==MAXSIZE){
//	 		      dp[0][wave_number][ind].erase(dp[0][wave_number][ind].begin());
//           }
//	    }
//	    for(int i=0;i<dp[0][wave_number][0].size();i++){
//   	 	   dp[0][wave_number][0][i].push_back(-1);
//	 	}
//		vector<int> tmp;
//		tmp.push_back(-1);
//		dp[0][wave_number][0].push_back(tmp);
//	    int j= dp[0][wave_number][0].size()-1;
//       	int i= j - 4;
//       	int x = i;
//       	if(sub_wave[wave_number/2][3].size()==0)
//       	   i=j-2;
//   	   
//        vector<double> zero_points;
//	    zero_points.push_back(mono_wave[i].startprice);
//	    for(i;i<=j;i++){
//	       zero_points.push_back(mono_wave[i].endprice);
//	    }
//	    if(check_rule(zero_points,wave_number))
//	      dp[0][wave_number][0][x][-x+ j]=x+1;
//     }
//     
//	 for(int l = 1; l<MAXLEVEL ; l++){
//		 for(int wave_number = 0; wave_number<22;wave_number++){
//		    for(int ind=4;ind>=0;ind--){
//		       if(dp[l][wave_number][ind].size()==MAXSIZE){
//			      dp[l][wave_number][ind].erase(dp[l][wave_number][ind].begin());
//			   }
//	     	   for(int i=0;i<dp[0][wave_number][0].size();i++){
//   		   	      dp[l][wave_number][ind][i].push_back(-1);
//		       }
//		       vector<int> tmp;
//               tmp.push_back(-1);
//			   dp[0][wave_number][0].push_back(tmp);
//	           
//			   for(int i=0;i<dp[l][wave_number][ind].size();i++){
//                  int j=dp[l][wave_number][ind].size()-1;
//                  bool done=false;
//				  for(int k=i;k<=j && !done;k++){
//              		  for(int sub=0;sub<sub_wave[wave_number/2][ind].size() && !done ;sub++){
//              		     if(dp[l-1][sub_wave[wave_number/2][ind][sub]][0][i][-i+ k]==-1) continue;;
//                         int maxindex=4;
//                         if(sub_wave[wave_number/2][3].size()==0)
//                            maxindex=2;
//						 if(ind<maxindex && dp[l][wave_number][ind+1][k+1][-k-1+j]==-1) continue;
//				         if(ind==0){
//	                        vector<double> points;
//	                        points.push_back(mono_wave[i].startprice);
//	                        points.push_back(mono_wave[k].endprice);
//	                        int x=dp[l][wave_number][1][k+1][-k-1+j];
//	                        points.push_back(mono_wave[x].endprice);
//	                        x=dp[l][wave_number][2][x+1][-x-1+j];
//	                        points.push_back(mono_wave[x].endprice);
//	                        if(maxindex==4){
//	                           x=dp[l][wave_number][3][x+1][-x-1+j];
//	                           points.push_back(mono_wave[x].endprice);
//	                           x=dp[l][wave_number][4][x+1][-x-1+j];
//	                           points.push_back(mono_wave[x].endprice);
//							}
//							if(!check_rule(points,wave_number)) continue;
//						 }
//						 dp[l][wave_number][ind][i][-i+ j]=k;
//	                     done = true;
//              	      }
//				  }
//			   }
//			}
//		 }
//	 }
//}
//
//bool addmonowave(double price,vector<monowave> mono_wave)
//{
//	if(mono_wave.size()==0){
//	     mono_wave.push_back(monowave(0,1,0,price));
//	     return true;
//	}
//	int dir=mono_wave[mono_wave.size()-1].endprice-mono_wave[mono_wave.size()-1].startprice;
//	int current_dir=price-mono_wave[mono_wave.size()-1].endprice;
//	
//	if((current_dir<=0 && dir<=0 )||(current_dir>=0 && dir>=0 )){
//		mono_wave[mono_wave.size()-1].endprice=price;
//		mono_wave[mono_wave.size()-1].endindex++;
//		return false;
//	}
//	else{
//		if(mono_wave.size()==MAXSIZE){
//			mono_wave.erase(mono_wave.begin());
//		}
//		mono_wave.push_back(monowave(mono_wave[mono_wave.size()-1].endindex,mono_wave[mono_wave.size()-1].endindex+1,mono_wave[mono_wave.size()-1].endprice,price));
//		return true;
//	}
//}
//
//
///*
//
//void addPoint(double price,vector <double>  p, vector < vector< int > >*** dp){
//	 if(p.size()==MAXSIZE) 
//	    p.erase(p.begin());
//	 p.push_back(price);
//	 for(int wave_number = 0; wave_number<22;wave_number++){
//        for(int ind=4;ind>=0;ind--){
//       	   if(dp[0][wave_number][ind].size()==MAXSIZE){
//	 		      dp[0][wave_number][ind].erase(dp[0][wave_number][ind].begin());
//           }
//  		   for(int i=0;i<dp[0][wave_number][ind].size();i++){
//       	      int j=dp[0][wave_number][ind].size();      
//           }
//	    }
//	 }
//	
//	 for(int l = 1; l<MAXLEVEL ; l++){
//		 for(int wave_number = 0; wave_number<22;wave_number++){
//		    for(int ind=4;ind>=0;ind--){
//		       if(dp[l][wave_number][ind].size()==MAXSIZE){
//			      dp[l][wave_number][ind].erase(dp[l][wave_number][ind].begin());
//			   }
//			   loop:
//			   for(int i=0;i<dp[l][wave_number][ind].size();i++){
//                  int j=dp[l][wave_number][ind].size();
//                  for(int k=i+1;k<j;k++){
//              		  for(int sub=0;sub<sub_wave[wave_number/2][ind].size();sub++){
//              		     if(dp[l-1][sub_wave[wave_number/2][ind][sub]][0][i][-i+ k]==-1) continue;;
//                         int maxindex=4;
//                         if(sub_wave[wave_number/2][3].size()==0)
//                            maxindex=2;
//						 if(ind<maxindex && dp[l][wave_number][ind+1][k][-k+j]==-1) continue;
//				         if(ind==0){
//	                        vector<double> points;
//	                        points.push_back(p[i]);
//	                        points.push_back(p[k]);
//	                        int x=dp[l][wave_number][1][k][-k+j];
//	                        points.push_back(p[x]);
//	                        x=dp[l][wave_number][2][x][-x+j];
//	                        points.push_back(p[x]);
//	                        if(maxindex==4){
//	                           x=dp[l][wave_number][3][x][-x+j];
//	                           points.push_back(p[x]);
//	                           x=dp[l][wave_number][4][x][-x+j];
//	                           points.push_back(p[x]);
//							}
//							if(!check_rule(points,wave_number)) continue;
//						 }
//						 dp[l][wave_number][ind][i].push_back(k);
//						 goto loop;
//              	      }
//              	      dp[l][wave_number][ind][i].push_back(-1);
//				  }
//			   }
//			}
//		 }
//	 }
//}
//
//
//
//
//*/
//	
//

