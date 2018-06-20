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
#include <cstring>
#include "input.hpp"

#define MAX_NODE 75
#define MAX_DSIZE 5600
class costMat{
    
public:
    costMat(){}
    costMat(int _cvd, int _ced, int _cvs, int _ces, chemgraph g1, chemgraph g2, float mat_delta[MAX_DSIZE][MAX_DSIZE]):cvd(_cvd), ced(_ced), cvs(_cvs), ces(_ces){
        //memset(mat_delta, 0, sizeof(mat_delta));
        memset(cost, 0, sizeof(cost));
        getCost(g1, g2);
        getDelta(g1, g2, mat_delta);
    }
    void printCost();
    void printDelta(float mat_delta[MAX_DSIZE][MAX_DSIZE]);
    
    int cost[MAX_NODE][MAX_NODE];
    int n_d, n_c, m_c;
    int cvd, ced, cvs, ces;
    
private:
    int computecord(int i, int k, int node_cnt);
    void getDelta(chemgraph g1, chemgraph g2, float mat_delta[MAX_DSIZE][MAX_DSIZE]);
    void getCost(chemgraph g1, chemgraph g2);
};

#endif /* genCost_hpp */
