#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_NODE 75
int node[2][MAX_NODE], g[2][MAX_NODE][MAX_NODE];
int node_cnt[2]={0};
const char ele[80][3]={
"H","He","Li","Be","B","C","N","O",
"F","Ne","Na","Mg","Al","Si","P","S",
"Cl","Ar","K","Ca","Sc","Ti","V","Cr",
"Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge",
"As","Se","Br","Kr","Rb","Sr","Y","Zr",
"Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd",
"In","Sn","Sb","Te","I","Xe","Cs","Ba",
"La","Ce","Pr","Nd","Pm","Sm","Eu","Gd",
"Tb","Dy","Ho","Er","Tm","Yb","Lu","Hf",
"Ta","W","Re","Os","Ir","Pt","Au","Hg",
};
int match_ele(const char atom[]){
	for (int i=0; i<80; i++)
		if (atom[0]==ele[i][0]&&atom[1]==ele[i][1])
			return i;
	printf("Element not listed!\n");
	return -1;
}

void read_gxl(char filename[], int graph)
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
			strncpy(str1, pstr+1, tmp-pstr-1);
			node[graph][cnt++]=match_ele(str1);	//element
		}
		else{
			fgets(buffer, 200, pfile);	//element
			pstr=strchr(buffer, '>');
			pstr=strchr(pstr+1, '>');
			tmp=strchr(pstr, '<');
			strncpy(str1, pstr+1, tmp-pstr-1);
			node[graph][cnt++]=atoi(str1);
			fgets(buffer, 200, pfile);
		}
	}while (fgets(buffer, 200, pfile), buffer[1]=='n');
	node_cnt[graph]=cnt;

	do{
		if (flag){
			pstr=strchr(buffer, '\"');
			tmp=strchr(pstr+1, '\"');
			strncpy(str1, pstr+1, tmp-pstr-1);
			a=atoi(str1)-1;
			pstr=strchr(tmp+1, '\"');
			tmp=strchr(pstr+1, '\"');
			strncpy(str1, pstr+1, tmp-pstr-1);
			b=atoi(str1)-1;

			pstr=strchr(tmp+2, '>');
			pstr=strchr(pstr+1, '>');
			g[graph][a][b]=g[graph][b][a]=pstr[1]-'0';
		}
		else{
			pstr=strchr(buffer, '_');
			tmp=strchr(pstr+1, '\"');
			strncpy(str1, pstr+1, tmp-pstr-1);
			a=atoi(str1)-1;
			pstr=strchr(tmp+1, '_');
			tmp=strchr(pstr+1, '\"');
			strncpy(str1, pstr+1, tmp-pstr-1);
			b=atoi(str1)-1;

			fgets(buffer, 200, pfile);
			pstr=strchr(buffer, '>');
			pstr=strchr(pstr+1, '>');
			g[graph][a][b]=g[graph][b][a]=pstr[1]-'0';
			fgets(buffer, 200, pfile);
		}
	}while (fgets(buffer, 200, pfile), buffer[1]=='e');
	
}

int main()
{
	read_gxl("g2.gxl", 0);
	for (int i=0; i<node_cnt[0]; i++)
		printf("%d", node[0][i]);
	printf("\n\n");
	for(int i=0; i<node_cnt[0]; i++)
	{
		for (int j=0; j<node_cnt[0]; j++)
			printf("%d", g[0][i][j]);
		printf("\n");
	}
}