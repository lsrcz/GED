#include "input.hpp"
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <map>
using namespace std;
#define MAX_NODE 75
map <string, int> ele;
int ele_cnt=0;
int match_ele(const char atom[]){
	string tmp=atom;
	//cout<<tmp<<endl;
	map <string, int>::iterator it=ele.find(tmp);
	if (it!=ele.end())
		return it->second;
	ele[tmp]=++ele_cnt;
	return ele_cnt;
}

void s_strncpy(char *dst, char *src, int len){strncpy(dst, src, len); dst[len]='\0';}

void read_gxl(char filename[], int g[][MAX_NODE], int* node, int &node_cnt)
{
	bool flag=false;
	FILE *pfile;
	char buffer[200], str1[3];
	char *pstr, *tmp;
	int cnt=0, a, b;

	pfile=fopen(filename, "r");
	if (pfile == NULL) {perror ("Error opening file");	return;}
	while (fgets(buffer, 200, pfile), buffer[1]!='n');
	pstr=strchr(buffer, '\"');
	if (pstr[1]!='_') flag=true;
	
	do{
		if (flag){
			pstr=strchr(buffer, '>');
			pstr=strchr(pstr+1, '>');
			pstr=strchr(pstr+1, '>');
			tmp=strchr(pstr, '<');
			s_strncpy(str1, pstr+1, tmp-pstr-1);
			node[cnt++]=match_ele(str1);	//element
		}
		else{
			fgets(buffer, 200, pfile);	//element
			pstr=strchr(buffer, '>');
			pstr=strchr(pstr+1, '>');
			tmp=strchr(pstr, '<');
			s_strncpy(str1, pstr+1, tmp-pstr-1);
			node[cnt++]=atoi(str1);
			fgets(buffer, 200, pfile);
		}
	}while (fgets(buffer, 200, pfile), buffer[1]=='n');
	node_cnt=cnt;

	do{
		if (flag){
			pstr=strchr(buffer, '\"');
			tmp=strchr(pstr+1, '\"');
			s_strncpy(str1, pstr+1, tmp-pstr-1);
			a=atoi(str1)-1;
			pstr=strchr(tmp+1, '\"');
			tmp=strchr(pstr+1, '\"');
			s_strncpy(str1, pstr+1, tmp-pstr-1);
			b=atoi(str1)-1;

			pstr=strchr(tmp+2, '>');
			pstr=strchr(pstr+1, '>');
			g[a][b]=g[b][a]=pstr[1]-'0';
		}
		else{
			pstr=strchr(buffer, '_');
			tmp=strchr(pstr+1, '\"');
			s_strncpy(str1, pstr+1, tmp-pstr-1);
			a=atoi(str1)-1;
			pstr=strchr(tmp+1, '_');
			tmp=strchr(pstr+1, '\"');
			s_strncpy(str1, pstr+1, tmp-pstr-1);
			b=atoi(str1)-1;

			fgets(buffer, 200, pfile);
			pstr=strchr(buffer, '>');
			pstr=strchr(pstr+1, '>');
			g[a][b]=g[b][a]=pstr[1]-'0';
			fgets(buffer, 200, pfile);
		}
	}while (fgets(buffer, 200, pfile), buffer[1]=='e');
}

void initmat(char filename1[], int mat1[MAX_NODE][MAX_NODE], int* node1, int &node_cnt1, char filename2[], int mat2[MAX_NODE][MAX_NODE], int* node2, int &node_cnt2){
    read_gxl(filename1, mat1, node1, node_cnt1);
    read_gxl(filename2, mat2, node2, node_cnt2);
}
