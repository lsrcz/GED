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
int cvd = 4, ced = 2, cvs = 2, ces = 1;
//char filename1[]="../gdc-c1/alkane/molecule002.gxl",
//        filename2[]="../gdc-c1/alkane/molecule003.gxl";
//char filename1[]="../gdc-c1/MUTA-GED/Mutagenicity/molecule_3875.gxl",
//        filename2[]="../gdc-c1/MUTA-GED/Mutagenicity/molecule_3419.gxl";
//char filename1[]="../gdc-c1/MUTA-GED/Mutagenicity/molecule_2876.gxl",
//        filename2[]="../gdc-c1/MUTA-GED/Mutagenicity/molecule_3990.gxl";
//char filename1[] = "../gdc-c1/MUTA-GED/Mutagenicity/molecule_42.gxl",
//        filename2[] = "../gdc-c1/MUTA-GED/Mutagenicity/molecule_4018.gxl";
char filename1[] = "../gdc-c1/MUTA-GED/Mutagenicity/molecule_3225.gxl",
        filename2[] = "../gdc-c1/MUTA-GED/Mutagenicity/molecule_3131.gxl";
//char filename1[]="../gdc-c1/mao/molecule18.gxl",
//        filename2[]="../gdc-c1/mao/molecule63.gxl";
//chemgraph g1, g2;
//costMat delta;

struct params {
    int cvs;
    int cvd;
    int ces;
    int ced;
    char path1[1000];
    char path2[1000];
    params(int argc, char *argv[]) {
        cvs = (int)strtol(argv[1], nullptr, 10);
        cvd = (int)strtol(argv[2], nullptr, 10);
        ces = (int)strtol(argv[3], nullptr, 10);
        ced = (int)strtol(argv[4], nullptr, 10);
        // no overflow check
        strcpy(path1, argv[5]);
        strcpy(path2, argv[6]);
    }
};

int main(int argc, char *argv[]) {
    auto start = clock();
    if (argc < 7) {
        printf("missing arguments, expect 6\n");
        printf("Cost for node substitution\n");
        printf("Cost for node deletion/insertion\n");
        printf("Cost for edge substitution\n");
        printf("Cost for edge deletion/insertion\n");
        printf("File name 1\n");
        printf("File name 2\n");
        exit(-1);
    }

    params param(argc, argv);

    chemgraph g1 = chemgraph(param.path1), g2 = chemgraph(param.path2);
    costMat delta(param.cvd, param.ced, param.cvs, param.ces, g1, g2);
#ifdef DEBUG
    g1.printchem(), g2.printchem();
    delta.printCost();
    delta.printDelta();
#endif
    auto x = (double *) calloc(delta.d_n, sizeof(double));

    // diagonalInit(x, delta.c_n, delta.c_m);
    randomInit(x, delta.c_n, delta.c_m, delta.c_n, delta.c_m, 10000);
    IPFPmin(x, delta);
#ifdef DEBUG
    printAssignment(x, delta.c_n - 1, delta.c_m - 1);
    printf("%f\n", delta.computeCost(x));
#endif

    double running_time = (double)(clock() - start) / CLOCKS_PER_SEC;
    printAnswer((int)delta.computeCost(x), running_time, x, delta.c_n - 1, delta.c_m - 1);

    //writeMatrix("mat", x, sizeof(double), delta.d_n);
}
