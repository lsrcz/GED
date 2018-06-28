#include <iostream>
#include "input.hpp"
#include "genCost.hpp"
#include "quadratic.hpp"
#include "lsape.hpp"
//#include <omp.h>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "matop.hpp"
#define MAX_NODE 75
#define MAX_DSIZE 5600
int cvd=4, ced=2, cvs=2, ces=1;
char filename1[]="g1.gxl", filename2[]="g2.gxl";
//chemgraph g1, g2;
//costMat delta;

void IPFPmin(double* x, const costMat& delta){
    double* mult_x_delta = new double[delta.d_n];
    double* mat_cost = new double[delta.d_n];
    int* b = new int[delta.d_n];
    vecMulMat(x, delta.mat_delta, mult_x_delta, delta.d_n, delta.d_n);
    matAdd(mult_x_delta, delta.cost, delta.d_n, 1, mat_cost);

    double s_k = dot(mat_cost, x, delta.d_n);
    double l = dot(delta.cost, x, delta.d_n);

    solveLSAPE(mat_cost, delta.c_n-1, delta.c_m-1, b);

    printf("mat b\n");
    for (int i=0; i<delta.c_n; i++){
      for(int j=0; j<delta.c_m; j++)
        printf("%d ", b[i*delta.c_m+j]);
      printf("\n");
    }
    solveQuadratic(delta, x, b, s_k, l, mult_x_delta);
    delete[] mult_x_delta;
    delete[] mat_cost;
    delete[] b;
}


int main()
{
    //cin>>cvd>>ced>>cvs>>ces;
    chemgraph g1=chemgraph(filename1), g2=chemgraph(filename2);
    costMat delta(cvd, ced, cvs, ces, g1, g2);
    //g1.printchem(), g2.printchem();
    //delta.printCost();
    //delta.printDelta();
    srand(time(NULL));
    double* x = (double*)calloc(delta.d_n, sizeof(double));

    for (int i=0; i<std::min(delta.c_n, delta.c_m); i++)
    	x[i*delta.c_m+i]=1;
   	if (delta.c_n>delta.c_m){
   		for (int i=delta.c_m; i<delta.c_n; i++)
   			x[(i+1)*delta.c_m-1]=1;
   	}
   	else{
   		for(int i=delta.c_n; i<delta.c_m; i++)
   			x[(delta.c_n-1)*delta.c_m+i]=1;
   	}
   	x[delta.c_n*delta.c_m-1]=1;
   	for (int i=0; i<delta.c_n; i++){
   		for(int j=0; j<delta.c_m; j++)
   			printf("%f ", x[i*delta.c_m+j]);
   		printf("\n");
   	}
    IPFPmin(x, delta);
    printf("mat x\n");
    for (int i=0; i<delta.c_n; i++){
      for(int j=0; j<delta.c_m; j++)
        printf("%f ", x[i*delta.c_m+j]);
      printf("\n");
    }
}
