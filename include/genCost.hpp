//
//  genCost.hpp
//  
//
//  Created by 吴怡凡 on 20/06/2018.
//
//

#ifndef genCost_hpp
#define genCost_hpp

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "input.hpp"

#define MAX_NODE 75
#define MAX_DSIZE 5600
class costMat{
    
public:
    costMat(){}
    costMat(int _cvd, int _ced, int _cvs, int _ces, chemgraph g1, chemgraph g2):cvd(_cvd), ced(_ced), cvs(_cvs), ces(_ces){
        //memset(mat_delta, 0, sizeof(mat_delta));
        c_n=g1.node_cnt+1, c_m=g2.node_cnt+1;
        d_n=c_n*c_m;

        cost = (int**)calloc(c_n, sizeof(int*));
        for (int i=0; i<c_n; i++)
            cost[i]=(int*)calloc(c_m, sizeof(int));

        mat_delta = (float**) calloc(d_n, sizeof(float*));
        for (int i=0; i<d_n; i++)
            mat_delta[i]=(float*)calloc(d_n, sizeof(float));
        
        getCost(g1, g2);
        getDelta(g1, g2);
    }

    ~costMat(){
        for (int i=0; i<c_n; i++)
            free(cost[i]);
        free(cost);
        for (int i=0; i<d_n; i++)
            free(mat_delta[i]);
        free(mat_delta);
    }


    void printCost();
    void printDelta();
    
    float** mat_delta;
    int** cost;//[MAX_NODE][MAX_NODE];
    int d_n, c_n, c_m;
    int cvd, ced, cvs, ces;
    
private:
    int computecord(int i, int k, int node_cnt);
    void getDelta(chemgraph g1, chemgraph g2);
    void getCost(chemgraph g1, chemgraph g2);
};

#endif /* genCost_hpp */
