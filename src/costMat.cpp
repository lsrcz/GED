//
//  genCost.cpp
//  
//
//  Created by 吴怡凡 on 20/06/2018.
//
//

#include <cstdio>
#include <algorithm>
#include "matop.hpp"
#include "costMat.hpp"

using std::min;

int costMat::computecord(int i, int k, int n) { return i * n + k; }

void costMat::getCost(const chemgraph &g1, const chemgraph &g2) {
    //n_c=g1.node_cnt+1, c_m=g2.node_cnt+1;
    for (int i = 0; i < c_n; i++) {
        for (int j = 0; j < c_m; j++) {
            if ((i == g1.node_cnt && j != g2.node_cnt) || (i != g1.node_cnt && j == g2.node_cnt)) {
                cost[computecord(i, j, c_m)] = cvd;
            } else if (i != g1.node_cnt && j != g2.node_cnt && g1.node[i] != g2.node[j]) {
                cost[computecord(i, j, c_m)] = cvs;
            }
        }
    }
}

void costMat::getDelta(const chemgraph &g1, const chemgraph &g2) {
    for (int i = 0; i < c_n; i++) {
        for (int k = 0; k < c_m; k++) {
            for (int j = 0; j < c_n; j++) {
                for (int l = 0; l < c_m; l++) {
                    if ((i == j && i != c_n - 1) || (k == l && k != c_m - 1) || (g1.g[i][j] == 0 && g2.g[k][l] == 0))
                        continue;

                    if (g1.g[i][j] != 0 && g2.g[k][l] != 0) {
                        mat_d[computecord(computecord(i, k, c_m), computecord(j, l, c_m), d_n)] = min(2 * ced,
                                                                                                      g1.g[i][j] ==
                                                                                                      g2.g[k][l] ? 0
                                                                                                                 : ces);
                    } else {
                        mat_d[computecord(computecord(i, k, c_m), computecord(j, l, c_m), d_n)] = ced;
                    }
                }
            }
        }
    }

    for (int i = 0; i < d_n; i++)
        for (int j = 0; j < d_n; j++)
            mat_delta[computecord(i, j, d_n)] = mat_d[computecord(i, j, d_n)] / 2.0;
    /*
    for (int i=0; i<c_n; i++){
        for (int j=0; j<c_m; j++){
            int cord=computecord(i, j, g2.node_cnt);
            mat_delta[cord][cord]+=cost[i][j];
        }
    }*/
}

void costMat::printCost() {
    printf("cost matrix C:\n");

    for (int i = 0; i < c_n; i++) {
        for (int j = 0; j < c_m; j++) {
            printf("%.1f ", cost[computecord(i, j, c_m)]);
        }
        printf("\n");
    }
    printf("\n");
}

void costMat::printDelta() {
    printf("cost matrix Delta:\n");
    for (int i = 0; i < d_n; i++) {
        for (int j = 0; j < d_n; j++) {
            printf("%.1f ", mat_delta[computecord(i, j, d_n)]);
        }
        printf("\n");
    }
    printf("\n");
}

double costMat::computeCost(double *x) {
    auto delta_hat = new double[d_n * d_n];
    auto mult_x_deltahat = new double[d_n];
    memcpy(delta_hat, mat_delta, d_n * d_n * sizeof(double));
    for (int i = 0; i < d_n; i++)
        delta_hat[i * d_n + i] = cost[i];
    vecMulMat(x, delta_hat, mult_x_deltahat, d_n, d_n);
    double ret = dot(mult_x_deltahat, x, d_n);
    delete[] delta_hat;
    delete[] mult_x_deltahat;
    return ret;
}
