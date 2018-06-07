#include <iostream>
#include "input.hpp"
using namespace std;
#define MAX_NODE 75
char filename1[]="g1.gxl", filename2[]="g2.gxl";
int mat1[MAX_NODE][MAX_NODE], mat2[MAX_NODE][MAX_NODE];
int node1[MAX_NODE], node2[MAX_NODE];
int node_cnt1, node_cnt2;

int main()
{
	initmat(filename1, mat1, node1, node_cnt1, filename2, mat2, node2, node_cnt2);
	printf("%d %d\n", node_cnt1, node_cnt2);
	for(int i=0; i<node_cnt1; i++)
		printf("%d ", node1[i]);
	printf("\n");
	for(int i=0; i<node_cnt1; i++){
		for(int j=0; j<node_cnt1; j++)
			printf("%d", mat1[i][j]);
		printf("\n");
	}

	for(int i=0; i<node_cnt2; i++)
		printf("%d ", node2[i]);
	printf("\n");
	for(int i=0; i<node_cnt2; i++){
		for(int j=0; j<node_cnt2; j++)
			printf("%d", mat2[i][j]);
		printf("\n");
	}

}