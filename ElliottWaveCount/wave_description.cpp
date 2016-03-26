#include <stdio.h>
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
#include "wave_description.h"
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
#define c_triangle 9
#define e_triangle 10

using namespace std;
 std::vector<int>  sub_wave[11][5];

void init(){
	   sub_wave[impulse][0].push_back(impulse);
	   sub_wave[impulse][0].push_back(leading_diagonals);
	   
	   sub_wave[impulse][1].push_back(zigzag);
	   sub_wave[impulse][1].push_back(flat);
	   sub_wave[impulse][1].push_back(double_zigzag);
	   sub_wave[impulse][1].push_back(tripple_zigzag);
	   sub_wave[impulse][1].push_back(double_threes);
	   sub_wave[impulse][1].push_back(tripple_threes);
	   
	   sub_wave[impulse][2].push_back(impulse);
	   
	   sub_wave[impulse][3].push_back(zigzag);
	   sub_wave[impulse][3].push_back(flat);
	   sub_wave[impulse][3].push_back(double_zigzag);
	   sub_wave[impulse][3].push_back(tripple_zigzag);
	   sub_wave[impulse][3].push_back(double_threes);
	   sub_wave[impulse][3].push_back(tripple_threes);
	   sub_wave[impulse][3].push_back(c_triangle);
	   sub_wave[impulse][3].push_back(e_triangle);
	   
	   sub_wave[impulse][4].push_back(impulse);
	   sub_wave[impulse][4].push_back(diagonals);
	   
	   sub_wave[leading_diagonals][0].push_back(impulse);
	   sub_wave[leading_diagonals][0].push_back(leading_diagonals);
	   
	   sub_wave[leading_diagonals][1].push_back(zigzag);
	   sub_wave[leading_diagonals][1].push_back(flat);
	   sub_wave[leading_diagonals][1].push_back(double_zigzag);
	   sub_wave[leading_diagonals][1].push_back(tripple_zigzag);
	   sub_wave[leading_diagonals][1].push_back(double_threes);
	   sub_wave[leading_diagonals][1].push_back(tripple_threes);
	   
	   sub_wave[leading_diagonals][2].push_back(impulse);
	   
	   sub_wave[leading_diagonals][3].push_back(zigzag);
	   sub_wave[leading_diagonals][3].push_back(flat);
	   sub_wave[leading_diagonals][3].push_back(double_zigzag);
	   sub_wave[leading_diagonals][3].push_back(tripple_zigzag);
	   sub_wave[leading_diagonals][3].push_back(double_threes);
	   sub_wave[leading_diagonals][3].push_back(tripple_threes);
	   sub_wave[leading_diagonals][3].push_back(c_triangle);
	   sub_wave[leading_diagonals][3].push_back(e_triangle);
	   
	   sub_wave[leading_diagonals][4].push_back(impulse);
	   sub_wave[leading_diagonals][4].push_back(diagonals);
	   
       
	   sub_wave[diagonals][0].push_back(zigzag);
	   sub_wave[diagonals][0].push_back(flat);
	   sub_wave[diagonals][0].push_back(double_zigzag);
	   sub_wave[diagonals][0].push_back(tripple_zigzag);
	   sub_wave[diagonals][0].push_back(double_threes);
	   sub_wave[diagonals][0].push_back(tripple_threes);
	   
	   sub_wave[diagonals][1].push_back(zigzag);
	   sub_wave[diagonals][1].push_back(flat);
	   sub_wave[diagonals][1].push_back(double_zigzag);
	   sub_wave[diagonals][1].push_back(tripple_zigzag);
	   sub_wave[diagonals][1].push_back(double_threes);
	   sub_wave[diagonals][1].push_back(tripple_threes);
	   
	   sub_wave[diagonals][2].push_back(zigzag);
	   sub_wave[diagonals][2].push_back(flat);
	   sub_wave[diagonals][2].push_back(double_zigzag);
	   sub_wave[diagonals][2].push_back(tripple_zigzag);
	   sub_wave[diagonals][2].push_back(double_threes);
	   sub_wave[diagonals][2].push_back(tripple_threes);
	   
	   
	   sub_wave[diagonals][3].push_back(zigzag);
	   sub_wave[diagonals][3].push_back(flat);
	   sub_wave[diagonals][3].push_back(double_zigzag);
	   sub_wave[diagonals][3].push_back(tripple_zigzag);
	   sub_wave[diagonals][3].push_back(double_threes);
	   sub_wave[diagonals][3].push_back(tripple_threes);
	   sub_wave[diagonals][3].push_back(c_triangle );
	   sub_wave[diagonals][3].push_back(e_triangle );
	   
	   sub_wave[diagonals][4].push_back(zigzag);
	   sub_wave[diagonals][4].push_back(flat);
	   sub_wave[diagonals][4].push_back(double_zigzag);
	   sub_wave[diagonals][4].push_back(tripple_zigzag);
	   sub_wave[diagonals][4].push_back(double_threes);
	   sub_wave[diagonals][4].push_back(tripple_threes);
	   sub_wave[diagonals][4].push_back(c_triangle );
	   sub_wave[diagonals][4].push_back(e_triangle );
	   
	   sub_wave[zigzag][0].push_back(impulse);
	   sub_wave[zigzag][0].push_back(leading_diagonals);
	   
	   sub_wave[zigzag][1].push_back(zigzag);
	   sub_wave[zigzag][1].push_back(flat);
	   sub_wave[zigzag][1].push_back(double_zigzag);
	   sub_wave[zigzag][1].push_back(tripple_zigzag);
	   sub_wave[zigzag][1].push_back(double_threes);
	   sub_wave[zigzag][1].push_back(tripple_threes);
	   sub_wave[zigzag][1].push_back(c_triangle );
	   sub_wave[zigzag][1].push_back(e_triangle );
	   
	   sub_wave[zigzag][2].push_back(impulse);
	   sub_wave[zigzag][2].push_back(diagonals);
	   
	   sub_wave[flat][0].push_back(zigzag);
	   sub_wave[flat][0].push_back(flat);
	   sub_wave[flat][0].push_back(double_zigzag);
	   sub_wave[flat][0].push_back(tripple_zigzag);
	   sub_wave[flat][0].push_back(double_threes);
	   sub_wave[flat][0].push_back(tripple_threes);
	   
	   sub_wave[flat][1].push_back(zigzag);
	   sub_wave[flat][1].push_back(flat);
	   sub_wave[flat][1].push_back(double_zigzag);
	   sub_wave[flat][1].push_back(tripple_zigzag);
	   sub_wave[flat][1].push_back(double_threes);
	   sub_wave[flat][1].push_back(tripple_threes);
	   sub_wave[flat][1].push_back(c_triangle );
	   sub_wave[flat][1].push_back(e_triangle );
	   
	   sub_wave[flat][2].push_back(impulse);
	   sub_wave[flat][2].push_back(diagonals);
	   
	   sub_wave[double_zigzag][0].push_back(zigzag);
	   
	   sub_wave[double_zigzag][1].push_back(zigzag);
	   sub_wave[double_zigzag][1].push_back(flat);
	   sub_wave[double_zigzag][1].push_back(double_zigzag);
	   sub_wave[double_zigzag][1].push_back(tripple_zigzag);
	   sub_wave[double_zigzag][1].push_back(double_threes);
	   sub_wave[double_zigzag][1].push_back(tripple_threes);
	   sub_wave[double_zigzag][1].push_back(c_triangle );
	   sub_wave[double_zigzag][1].push_back(e_triangle );
	   
	   sub_wave[double_zigzag][2].push_back(zigzag);
	   
	   sub_wave[tripple_zigzag][0].push_back(zigzag);
	   
	   sub_wave[tripple_zigzag][1].push_back(zigzag);
	   sub_wave[tripple_zigzag][1].push_back(flat);
	   sub_wave[tripple_zigzag][1].push_back(double_zigzag);
	   sub_wave[tripple_zigzag][1].push_back(tripple_zigzag);
	   sub_wave[tripple_zigzag][1].push_back(double_threes);
	   sub_wave[tripple_zigzag][1].push_back(tripple_threes);
	   
	   sub_wave[tripple_zigzag][2].push_back(zigzag);
	   
	   sub_wave[tripple_zigzag][3].push_back(zigzag);
	   sub_wave[tripple_zigzag][3].push_back(flat);
	   sub_wave[tripple_zigzag][3].push_back(double_zigzag);
	   sub_wave[tripple_zigzag][3].push_back(tripple_zigzag);
	   sub_wave[tripple_zigzag][3].push_back(double_threes);
	   sub_wave[tripple_zigzag][3].push_back(tripple_threes);
	   sub_wave[tripple_zigzag][3].push_back(c_triangle );
	   sub_wave[tripple_zigzag][3].push_back(e_triangle );
	   
	   sub_wave[tripple_zigzag][4].push_back(zigzag);
	   
	   sub_wave[double_threes][0].push_back(zigzag);
	   sub_wave[double_threes][0].push_back(flat);
	   sub_wave[double_threes][0].push_back(double_zigzag);
	   sub_wave[double_threes][0].push_back(tripple_zigzag);
	   sub_wave[double_threes][0].push_back(double_threes);
	   sub_wave[double_threes][0].push_back(tripple_threes);
	   
	   sub_wave[double_threes][1].push_back(zigzag);
	   sub_wave[double_threes][1].push_back(flat);
	   sub_wave[double_threes][1].push_back(double_zigzag);
	   sub_wave[double_threes][1].push_back(tripple_zigzag);
	   sub_wave[double_threes][1].push_back(double_threes);
	   sub_wave[double_threes][1].push_back(tripple_threes);
	   sub_wave[double_threes][1].push_back(c_triangle );
	   sub_wave[double_threes][1].push_back(e_triangle );
	   
	   sub_wave[double_threes][2].push_back(zigzag);
	   sub_wave[double_threes][2].push_back(flat);
	   sub_wave[double_threes][2].push_back(double_zigzag);
	   sub_wave[double_threes][2].push_back(tripple_zigzag);
	   sub_wave[double_threes][2].push_back(double_threes);
	   sub_wave[double_threes][2].push_back(tripple_threes);
	   sub_wave[double_threes][2].push_back(c_triangle );
	   sub_wave[double_threes][2].push_back(e_triangle );
	   
	   
	   sub_wave[tripple_threes][0].push_back(zigzag);
	   sub_wave[tripple_threes][0].push_back(flat);
	   sub_wave[tripple_threes][0].push_back(double_zigzag);
	   sub_wave[tripple_threes][0].push_back(tripple_zigzag);
	   sub_wave[tripple_threes][0].push_back(double_threes);
	   sub_wave[tripple_threes][0].push_back(tripple_threes);
	   
	   sub_wave[tripple_threes][1].push_back(zigzag);
	   sub_wave[tripple_threes][1].push_back(flat);
	   sub_wave[tripple_threes][1].push_back(double_zigzag);
	   sub_wave[tripple_threes][1].push_back(tripple_zigzag);
	   sub_wave[tripple_threes][1].push_back(double_threes);
	   sub_wave[tripple_threes][1].push_back(tripple_threes);
	   
	   sub_wave[tripple_threes][2].push_back(zigzag);
	   sub_wave[tripple_threes][2].push_back(flat);
	   sub_wave[tripple_threes][2].push_back(double_zigzag);
	   sub_wave[tripple_threes][2].push_back(tripple_zigzag);
	   sub_wave[tripple_threes][2].push_back(double_threes);
	   sub_wave[tripple_threes][2].push_back(tripple_threes);
	   
	   
	   sub_wave[tripple_threes][3].push_back(zigzag);
	   sub_wave[tripple_threes][3].push_back(flat);
	   sub_wave[tripple_threes][3].push_back(double_zigzag);
	   sub_wave[tripple_threes][3].push_back(tripple_zigzag);
	   sub_wave[tripple_threes][3].push_back(double_threes);
	   sub_wave[tripple_threes][3].push_back(tripple_threes);
	   sub_wave[tripple_threes][3].push_back(c_triangle);
	   sub_wave[tripple_threes][3].push_back(e_triangle);
	   
	   sub_wave[tripple_threes][4].push_back(zigzag);
	   sub_wave[tripple_threes][4].push_back(flat);
	   sub_wave[tripple_threes][4].push_back(double_zigzag);
	   sub_wave[tripple_threes][4].push_back(tripple_zigzag);
	   sub_wave[tripple_threes][4].push_back(double_threes);
	   sub_wave[tripple_threes][4].push_back(tripple_threes);
	   sub_wave[tripple_threes][4].push_back(c_triangle);
	   sub_wave[tripple_threes][4].push_back(e_triangle);
	   
	   sub_wave[c_triangle][0].push_back(zigzag);
	   sub_wave[c_triangle][0].push_back(flat);
	   sub_wave[c_triangle][0].push_back(double_zigzag);
	   sub_wave[c_triangle][0].push_back(tripple_zigzag);
	   sub_wave[c_triangle][0].push_back(double_threes);
	   sub_wave[c_triangle][0].push_back(tripple_threes);
	   
	   sub_wave[c_triangle][1].push_back(zigzag);
	   sub_wave[c_triangle][1].push_back(flat);
	   sub_wave[c_triangle][1].push_back(double_zigzag);
	   sub_wave[c_triangle][1].push_back(tripple_zigzag);
	   sub_wave[c_triangle][1].push_back(double_threes);
	   sub_wave[c_triangle][1].push_back(tripple_threes);
	   
	   sub_wave[c_triangle][2].push_back(zigzag);
	   sub_wave[c_triangle][2].push_back(flat);
	   sub_wave[c_triangle][2].push_back(double_zigzag);
	   sub_wave[c_triangle][2].push_back(tripple_zigzag);
	   sub_wave[c_triangle][2].push_back(double_threes);
	   sub_wave[c_triangle][2].push_back(tripple_threes);
	   
	   
	   sub_wave[c_triangle][3].push_back(zigzag);
	   sub_wave[c_triangle][3].push_back(flat);
	   sub_wave[c_triangle][3].push_back(double_zigzag);
	   sub_wave[c_triangle][3].push_back(tripple_zigzag);
	   sub_wave[c_triangle][3].push_back(double_threes);
	   sub_wave[c_triangle][3].push_back(tripple_threes);
	   sub_wave[c_triangle][3].push_back(c_triangle);
	   sub_wave[c_triangle][3].push_back(e_triangle);
	   
	   sub_wave[c_triangle][4].push_back(zigzag);
	   sub_wave[c_triangle][4].push_back(flat);
	   sub_wave[c_triangle][4].push_back(double_zigzag);
	   sub_wave[c_triangle][4].push_back(tripple_zigzag);
	   sub_wave[c_triangle][4].push_back(double_threes);
	   sub_wave[c_triangle][4].push_back(tripple_threes);
	   sub_wave[c_triangle][4].push_back(c_triangle);
	   sub_wave[c_triangle][4].push_back(e_triangle);
	   
	   sub_wave[e_triangle][0].push_back(zigzag);
	   sub_wave[e_triangle][0].push_back(flat);
	   sub_wave[e_triangle][0].push_back(double_zigzag);
	   sub_wave[e_triangle][0].push_back(tripple_zigzag);
	   sub_wave[e_triangle][0].push_back(double_threes);
	   sub_wave[e_triangle][0].push_back(tripple_threes);
	   
	   sub_wave[e_triangle][1].push_back(zigzag);
	   sub_wave[e_triangle][1].push_back(flat);
	   sub_wave[e_triangle][1].push_back(double_zigzag);
	   sub_wave[e_triangle][1].push_back(tripple_zigzag);
	   sub_wave[e_triangle][1].push_back(double_threes);
	   sub_wave[e_triangle][1].push_back(tripple_threes);
	   
	   sub_wave[e_triangle][2].push_back(zigzag);
	   sub_wave[e_triangle][2].push_back(flat);
	   sub_wave[e_triangle][2].push_back(double_zigzag);
	   sub_wave[e_triangle][2].push_back(tripple_zigzag);
	   sub_wave[e_triangle][2].push_back(double_threes);
	   sub_wave[e_triangle][2].push_back(tripple_threes);
	   
	   
	   sub_wave[e_triangle][3].push_back(zigzag);
	   sub_wave[e_triangle][3].push_back(flat);
	   sub_wave[e_triangle][3].push_back(double_zigzag);
	   sub_wave[e_triangle][3].push_back(tripple_zigzag);
	   sub_wave[e_triangle][3].push_back(double_threes);
	   sub_wave[e_triangle][3].push_back(tripple_threes);
	   sub_wave[e_triangle][3].push_back(c_triangle);
	   sub_wave[e_triangle][3].push_back(e_triangle);
	   
	   sub_wave[e_triangle][4].push_back(zigzag);
	   sub_wave[e_triangle][4].push_back(flat);
	   sub_wave[e_triangle][4].push_back(double_zigzag);
	   sub_wave[e_triangle][4].push_back(tripple_zigzag);
	   sub_wave[e_triangle][4].push_back(double_threes);
	   sub_wave[e_triangle][4].push_back(tripple_threes);
	   sub_wave[e_triangle][4].push_back(c_triangle);
	   sub_wave[e_triangle][4].push_back(e_triangle);
}


