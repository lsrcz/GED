//
//  genCost.cpp
//  
//
//  Created by 吴怡凡 on 20/06/2018.
//
//

#include "genCost.hpp"
#include "stdio.h"
#include <algorithm>
using std::min;

int costMat::computecord(int i, int k, int node_cnt){return i*(node_cnt+1)+k;}

void costMat::getCost(chemgraph g1, chemgraph g2){
    n_c=g1.node_cnt+1, m_c=g2.node_cnt+1;
    for (int i=0; i<=g1.node_cnt; i++){
        for (int j=0; j<=g2.node_cnt; j++){
            if ((i==g1.node_cnt&&j!=g2.node_cnt)||(i!=g1.node_cnt&&j==g2.node_cnt)){
                cost[i][j]=cvd;
            }
            else if (i!=g1.node_cnt&&j!=g2.node_cnt&&g1.node[i]!=g2.node[j]){
                cost[i][j]=cvs;
            }
        }
    }
}

void costMat::getDelta(chemgraph g1, chemgraph g2, float mat_delta[MAX_DSIZE][MAX_DSIZE]){
    n_d=n_c*m_c;
    for (int i=0; i<=g1.node_cnt; i++){
        for (int k=0; k<=g2.node_cnt; k++){
            for (int j=0; j<=g1.node_cnt; j++){
                for (int l=0; l<=g2.node_cnt; l++){
                    if (i==j||k==l||(g1.g[i][j]==0&&g2.g[k][l]==0))
                        continue;
                    
                    if (g1.g[i][j]!=0&&g2.g[k][l]!=0){
                        mat_delta[computecord(i, k, g2.node_cnt)][computecord(j, l, g2.node_cnt)]=min(2*ced, g1.g[i][j]==g2.g[k][l]? 0 : ces)/2;
                    }
                    else{
                        mat_delta[computecord(i, k, g2.node_cnt)][computecord(j, l, g2.node_cnt)]=ced/2.0;
                    }
                }
            }
        }
    }
    
    for (int i=0; i<=g1.node_cnt; i++){
        for (int j=0; j<=g2.node_cnt; j++){
            int cord=computecord(i, j, g2.node_cnt);
            mat_delta[cord][cord]+=cost[i][j];
        }
    }
}

void costMat::printCost(){
    printf("cost matrix C:\n");
    for (int i=0; i<n_c; i++){
        for (int j=0; j<m_c; j++){
            printf("%d ", cost[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void costMat::printDelta(float mat_delta[MAX_DSIZE][MAX_DSIZE]){
    printf("cost matrix Delta:\n");
    for (int i=0; i<n_d; i++){
        for (int j=0; j<n_d; j++){
            printf("%.1f ", mat_delta[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

