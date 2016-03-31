#include<stdio.h>
#include<stdlib.h>
#include "util.h"
int * intArray(int size){
	int * ptr = (int *) malloc(sizeof(int) * size);
	return ptr;
}
int ** int2dArray(int r, int c){
	int ** ptr = (int **)malloc(sizeof(int *) * r);
	for(int i=0;i<r;i++)
		ptr[i] = (int *)malloc(sizeof(int) * c);
	return ptr;
}
double * doubleArray(int size){
	double * ptr = (double *) malloc(sizeof(double) * size);
	return ptr;
}
double ** double2dArray(int r, int c){
	double ** ptr = (double **)malloc(sizeof(double *) * r);
	for(int i=0;i<r;i++)
		ptr[i] = (double *)malloc(sizeof(double) * c);
	return ptr;
}

