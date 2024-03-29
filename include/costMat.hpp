//
//  genCost.hpp
//  
//
//  Created by 吴怡凡 on 20/06/2018.
//
//

#ifndef GENCOST_HPP
#define GENCOST_HPP

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "chemgraph.hpp"

#define MAX_NODE 75
#define MAX_DSIZE 5600

class costMat {

public:
    double *mat_delta;  //delta = 1/2 d
    double *mat_d;      //matrix d
    double *cost;       // matrix c
    int d_n, c_n, c_m;  //size of matrix, where d = d_n * d_n, c = c_n (rows) * c_m (columns)
    int cvd, ced, cvs, ces; //modifying costs

    costMat() {}

    costMat(int _cvd, int _ced, int _cvs, int _ces, const chemgraph &g1, const chemgraph &g2) : cvd(_cvd), ced(_ced), cvs(_cvs),
                                                                                  ces(_ces) {
        //memset(mat_delta, 0, sizeof(mat_delta));
        c_n = g1.node_cnt + 1, c_m = g2.node_cnt + 1;
        d_n = c_n * c_m;

        cost = (double *) calloc(c_n * c_m, sizeof(double));
        mat_delta = (double *) calloc(d_n * d_n, sizeof(double));
        mat_d = (double *) calloc(d_n * d_n, sizeof(double));

        getCost(g1, g2);
        getDelta(g1, g2);
    }

    ~costMat() {
        free(cost);
        free(mat_delta);
    }


    void printCost();

    void printDelta();

    double computeCost(double *x);


private:
    int computecord(int i, int k, int node_cnt);

    void getDelta(const chemgraph &g1, const chemgraph &g2);

    void getCost(const chemgraph &g1, const chemgraph &g2);
};

#endif //GENCOST_HPP
