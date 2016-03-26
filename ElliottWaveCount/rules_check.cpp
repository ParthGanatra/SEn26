#include <stdio.h>
#include "wavecount.h"
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
#define impulse 1
#define leading_diagonals 2
#define diagonals 3
#define zigzag 4
#define flat 5
#define double_zigzag 6
#define tripple_zigzag 7
#define double_threes 8
#define tripple_threes 9
#define c_triangle 10
#define e_triangle 11

using namespace std;

bool check_rule(vector<double> wave, int wave_number){
	if(wave_number%2!=0){
		for(int i=0;i<wave.size();i++)
				wave[i] = - wave[i];
	}
	wave_number/=2;
	if(wave_number==impulse){
        if(wave[0]>wave[2])
           return false;
        if(wave[3]<wave[1])
           return false;
        if(wave[4]<wave[1])
           return false;
        if(wave[3]-wave[2] < wave[1]-wave[0])
           if(wave[3]-wave[2] < wave[5]-wave[4])
              return false;
	}
	if(wave_number == leading_diagonals){
	    if(wave[0]>wave[2])
           return false;
        if(wave[3]<wave[1])
           return false;
	    if(wave[4]>wave[1])
	       return false;
        if(wave[4]<wave[2])
           return false;
        if(wave[3]-wave[2] < wave[1]-wave[0])
           if(wave[3]-wave[2] < wave[5]-wave[4])
              return false;			   
	}
	if(wave_number == leading_diagonals){
	    if(wave[0]>wave[2])
           return false;
        if(wave[3]<wave[1])
           return false;
	    if(wave[4]>wave[1])
	       return false;
        if(wave[4]<wave[2])
           return false;
        if(wave[3]-wave[2] < wave[1]-wave[0])
           if(wave[3]-wave[2] < wave[5]-wave[4])
              return false;			   
	}
	if(wave_number == zigzag){
        if(wave[3]<wave[1])
           return false;
        if(wave[2]<wave[0])
           return false;
	}
	if(wave_number==flat){
        
	}
	if(wave_number == double_zigzag){
        if(wave[3]<wave[1])
           return false;
        if(wave[2]<wave[0])
           return false;
	}
	if(wave_number == tripple_zigzag){
        if(wave[5]<wave[3])
           return false;
        if(wave[4]<wave[2])
           return false;
		if(wave[3]<wave[1])
           return false;
        if(wave[2]<wave[0])
           return false;
	}
	if(wave_number == c_triangle){
        if(wave[3]<wave[1])
           return false;
        if(wave[4]>wave[2])
           return false;
        if(wave[5]<wave[3])
           return false;
	}
	if(wave_number == e_triangle){
        if(wave[3]>wave[1])
           return false;
        if(wave[4]<wave[2])
           return false;
        if(wave[5]>wave[3])
           return false;
	}  
	return true;
}
