#include <iostream>
#include "input.hpp"
#include "genCost.hpp"
#include "quadratic.hpp"
#include "lsape.hpp"
#include "utils.hpp"
//#include <omp.h>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "matop.hpp"
#define MAX_NODE 75
#define MAX_DSIZE 5600
int cvd=4, ced=2, cvs=2, ces=1;
char filename1[]="../gdc-c1/alkane/molecule001.gxl",
        filename2[]="../gdc-c1/alkane/molecule091.gxl";
//char filename1[]="../gdc-c1/alkane/molecule003.gxl",
//        filename2[]="../gdc-c1/alkane/molecule004.gxl";
//chemgraph g1, g2;
//costMat delta;

void IPFPmin(double* x, const costMat& delta){
    auto clk = clock();
    double* mult_x_d = new double[delta.d_n];
    double* mat_cost = new double[delta.d_n];
    int* b = new int[delta.d_n];
    double* x_k = new double[delta.d_n];
    memcpy(x_k, x, delta.d_n*sizeof(double));

    vecMulMat(x, delta.mat_d, mult_x_d, delta.d_n, delta.d_n);
    matAdd(mult_x_d, delta.cost, delta.d_n, 1, mat_cost);

    double s_k = dot(mat_cost, x, delta.d_n);
    double l = dot(delta.cost, x, delta.d_n);
    //printMat(mult_x_d, delta.d_n, 1, "mult_x_d");
    //printMat(delta.cost, delta.d_n, 1, "delta_cost");
    //printMat(mat_cost, delta.d_n, 1, "mult_cost");
    int it = 0;
    while (true){
        printf("it%d\n", ++it);
      solveLSAPE(mat_cost, delta.c_n-1, delta.c_m-1, b);

      //printMat(b, delta.c_n, delta.c_m, "mat b");

      solveQuadratic(delta, x, b, s_k, l, mult_x_d);
      if (vecEq(x, x_k, delta.d_n))
        break;
      if (clock() - clk > 10 * CLOCKS_PER_SEC)
          break;
      vecMulMat(x, delta.mat_d, mult_x_d, delta.d_n, delta.d_n);
      matAdd(mult_x_d, delta.cost, delta.d_n, 1, mat_cost);
      memcpy(x_k, x, delta.d_n*sizeof(double));


    }

    if (!vecEq(x, b, delta.d_n)){
      vecMulMat(x, delta.mat_d, mult_x_d, delta.d_n, delta.d_n);
      matAdd(mult_x_d, delta.cost, delta.d_n, 1, mat_cost);
      solveLSAPE(mat_cost, delta.c_n-1, delta.c_m-1, b);
      for (int i=0; i<delta.d_n; i++)
        x[i] = b[i];
    }

    delete[] mult_x_d;
    delete[] mat_cost;
    delete[] b;
}

double compute_cost(double* x, const costMat& c){
  double* delta_hat = new double[c.d_n * c.d_n];
  double* mult_x_deltahat = new double[c.d_n];
  memcpy(delta_hat, c.mat_delta, c.d_n*c.d_n*sizeof(double));
  for (int i=0; i<c.d_n; i++)
    delta_hat[i*c.d_n+i] = c.cost[i];
  vecMulMat(x, delta_hat, mult_x_deltahat, c.d_n, c.d_n);
  double ret = dot(mult_x_deltahat, x, c.d_n);
  delete[] delta_hat;
  delete[] mult_x_deltahat;
  return ret;
}

void randomInit(double *x, int c_n, int c_m, int max_row_sample_times, int max_col_sample_times, int max_assign_times) {
    srand(time(NULL));
    memset(x, 0, sizeof(double) * c_n * c_m);
    int assigned_times = 0;
    bool *row_assigned = new bool[c_n - 1];
    bool *col_assigned = new bool[c_m - 1];
    memset(row_assigned, 0, sizeof(bool) * (c_n - 1));
    memset(col_assigned, 0, sizeof(bool) * (c_m - 1));
    for (int i = 0; i < max_row_sample_times; ++i) {
        int row = rand() % (c_n - 1);
        if (row_assigned[row]) {
            continue;
        } else {
            for (int j = 0; j < max_col_sample_times; ++j) {
                int col = rand() % (c_m - 1);
                if (col_assigned[col])
                    continue;
                x[row * c_m + col] = 1;
                col_assigned[col] = true;
                row_assigned[row] = true;
                ++assigned_times;
                break;
            }
        }
        if (assigned_times == max_assign_times)
            break;
    }
    for (int i = 0; i < c_m; ++i) {
        if (col_assigned[i])
            continue;
        x[(c_n - 1) * c_m + i] = true;
    }
    for (int i = 0; i < c_n; ++i) {
        if (row_assigned[i])
            continue;
        x[(i + 1) * c_m - 1] = true;
    }
    x[c_n * c_m - 1] = true;
}


int main()
{
    //cin>>cvd>>ced>>cvs>>ces;
    chemgraph g1=chemgraph(filename1), g2=chemgraph(filename2);
    costMat delta(cvd, ced, cvs, ces, g1, g2);
    //g1.printchem(), g2.printchem();
    //delta.printCost();
    //delta.printDelta();
    double* x = (double*)calloc(delta.d_n, sizeof(double));

    /*
    for (int i=0; i<std::min(delta.c_n, delta.c_m); i++)
    	x[i*delta.c_m+delta.c_m - 1 - i]=1;
   	if (delta.c_n>delta.c_m){
   		for (int i=delta.c_m; i<delta.c_n; i++)
   			x[(i+1)*delta.c_m-1]=1;
   	}
   	else{
   		for(int i=delta.c_n; i<delta.c_m; i++)
   			x[(delta.c_n-1)*delta.c_m+i]=1;
   	}
   	x[delta.c_n*delta.c_m-1]=1;*/
    randomInit(x, delta.c_n, delta.c_m, delta.c_n, delta.c_m, 10000);

    //printMat(x, delta.c_n, delta.c_m, "mat x");

    IPFPmin(x, delta);

    //printMat(x, delta.c_n, delta.c_m, "mat x");

    printf("%f\n", compute_cost(x, delta));

    printMat(x, delta.c_n, delta.c_m, "mat x");


}
