#include<stdio.h>
#include <iostream>
#include "wave_description.h"
#include "wavecount.h"
#include<time.h>
#include<stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	init();
	Wavecount w;
	int n=500;
	int input[n];
	srand(time(NULL));
	for(int i=0;i<n;i++)
	   input[i] = rand()%100000;
	for(int i=0;i<n;i++){
		printf("\n\n**************************  %d %d ******************************\n\n",i,input[i]);
		w.add_point(input[i]);	
	}
	for(int i=0; i<w.wavecount.size();i++){
	   printf("%f ->",w.prices[i]);
	   for(int j=0;j<w.wavecount[i].size();j++)
	      printf(" %d ",w.wavecount[i][j]);
       printf("\n");
	}
	
}
