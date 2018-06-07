#include <iostream>
#include "input.hpp"
#include <omp.h>
#include <cstring>
using namespace std;
#define MAX_NODE 75
#define MAX_DSIZE 22500
#define MAX_COST 1000000000
int cvd, ced, cvi, cei, cvs, ces;
char filename1[]="g1.gxl", filename2[]="g2.gxl";
int mat1[MAX_NODE][MAX_NODE], mat2[MAX_NODE][MAX_NODE];
int node1[MAX_NODE], node2[MAX_NODE];
int node_cnt1, node_cnt2;
int mat_delta[MAX_DSIZE][MAX_DSIZE];

bool matchnode(int i, int k){ return (x<node_cnt1&&k<node_cnt2)||(x>=node_cnt1||k>=node_cnt2)||(x>=node_cnt1&&x-node_cnt1==k)||(k>=node_cnt2&&k-node_cnt2==x);}

void get_mat_delta(){
	memset(mat_delta, 0, sizeof(mat_delta));
	int dsize=node_cnt1+node_cnt2;
	#pragma omp parallel for
	for (int i=0; i<dsize; i++)
		for (int j=0; j<dsize; j++)
		{
			int x=i*(node_cnt1+node_cnt2), y=j*(node_cnt1+node_cnt2);
			for (int k=0; k<dsize; x++, k++)
				for (int l=0; l<dsize; y++, l++){
					if (i==j&&k==l)continue;
					else if (i==j||k==l)mat_delta[x][y]=MAX_COST;
					else if (i<node_cnt1&&j<node_cnt1&&k<node_cnt2&&j<node_cnt2){
						int deltaij=(mat1[i][j]!=0), deltakl=(mat2[k][l]!=0);
						mat_delta[x][y]=ces*(mat1[i][j]!=mat2[k][l])*deltaij*deltakl+ced*deltaij*(1-deltakl)+cei(1-delaij)*deltakl;
					}
					else if (matchnode(i, k)&&matchnode(j, l)){
						if (i<node_cnt1&&j<node_cnt1)
							mat_delta[x][y]=ced*(mat1[i][j]!=0);
						else if (k<node_cnt2&&l<node_cnt2)
							mat_delta[x][y]=cei*(mat2[k][l]!=0);
					}
					else mat_delta[x][y]=MAX_COST;
				}
		}

}

int main()
{
	initmat(filename1, mat1, node1, node_cnt1, filename2, mat2, node2, node_cnt2);
	get_mat_delta();


}