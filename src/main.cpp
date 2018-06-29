#include <iostream>
#include "input.hpp"
#include "genCost.hpp"
#include "quadratic.hpp"
#include "lsape.hpp"
#include "utils.hpp"
#include "IPFP.hpp"
#include "init.hpp"
//#include <omp.h>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "matop.hpp"
#define MAX_NODE 75
#define MAX_DSIZE 5600
int cvd=4, ced=2, cvs=2, ces=1;
//char filename1[]="../gdc-c1/alkane/molecule002.gxl",
//        filename2[]="../gdc-c1/alkane/molecule003.gxl";
//char filename1[]="../gdc-c1/MUTA-GED/Mutagenicity/molecule_3875.gxl",
//        filename2[]="../gdc-c1/MUTA-GED/Mutagenicity/molecule_3419.gxl";
//char filename1[]="../gdc-c1/MUTA-GED/Mutagenicity/molecule_2876.gxl",
//        filename2[]="../gdc-c1/MUTA-GED/Mutagenicity/molecule_3990.gxl";
char filename1[]="../gdc-c1/MUTA-GED/Mutagenicity/molecule_42.gxl",
        filename2[]="../gdc-c1/MUTA-GED/Mutagenicity/molecule_4018.gxl";
//char filename1[]="../gdc-c1/mao/molecule18.gxl",
//        filename2[]="../gdc-c1/mao/molecule63.gxl";
//chemgraph g1, g2;
//costMat delta;


int main()
{
    //cin>>cvd>>ced>>cvs>>ces;
    chemgraph g1=chemgraph(filename1), g2=chemgraph(filename2);
    costMat delta(cvd, ced, cvs, ces, g1, g2);
    g1.printchem(), g2.printchem();
    //delta.printCost();
    //delta.printDelta();
    double* x = (double*)calloc(delta.d_n, sizeof(double));

    // diagonalInit(x, delta.c_n, delta.c_m);
    randomInit(x, delta.c_n, delta.c_m, delta.c_n, delta.c_m, 10000);
    //readMatrix("mat_muta", x, sizeof(double), delta.d_n);
    //writeMatrix("mat_1", x, sizeof(double), delta.d_n);
    printMat(x, delta.c_m, delta.c_n, "x");
    IPFPmin(x, delta);

    printAssignment(x,delta.c_n - 1, delta.c_m - 1);

    printf("%f\n", delta.computeCost(x));

    //writeMatrix("mat", x, sizeof(double), delta.d_n);
}
