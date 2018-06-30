#include <iostream>
#include "chemgraph.hpp"
#include "costMat.hpp"
#include "quadratic.hpp"
#include "lsape.hpp"
#include "utils.hpp"
#include "IPFP.hpp"
#include "init.hpp"
#include <cstring>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "matop.hpp"
#include <chrono>

#define MAX_NODE 75

using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

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
    high_resolution_clock::time_point beginTime = high_resolution_clock::now();
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

    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    milliseconds timeInterval = std::chrono::duration_cast<milliseconds>(endTime - beginTime);
    double running_time = (double)(timeInterval.count()) / 1000;
    printAnswer((int)delta.computeCost(x), running_time, x, delta.c_n - 1, delta.c_m - 1);
}
