#include "input.hpp"
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;
#define MAX_NODE 75

map<string, int> chemgraph::ele;
int chemgraph::ele_cnt = 0;

int chemgraph::match_ele(const char atom[]) {
    string tmp = atom;
    auto it = ele.find(tmp);
    if (it != ele.end())
        return it->second;
    ele[tmp] = ++ele_cnt;
    return ele_cnt;
}

void s_strncpy(char *dst, char *src, int len) {
    strncpy(dst, src, len);
    dst[len] = '\0';
}

chemgraph::chemgraph(char filename[]) {
    FILE *pfile;
    char buffer[200], str1[3];
    char *pstr, *tmp;
    int cnt = 0, a, b;

    for (int i = 0; i < MAX_NODE; i++)
        memset(g[i], 0, sizeof(g[i]));

    pfile = fopen(filename, "r");
    if (pfile == nullptr) {
        perror("Error opening file");
        return;
    }
    while (fgets(buffer, 200, pfile), buffer[1] != 'n');
    pstr = strchr(buffer, '\"');
    if (pstr[1] != '_') muta = true;

    do {
        if (muta) {
            pstr = strchr(buffer, '>');
            pstr = strchr(pstr + 1, '>');
            pstr = strchr(pstr + 1, '>');
            tmp = strchr(pstr, '<');
            s_strncpy(str1, pstr + 1, tmp - pstr - 1);
            node[cnt++] = match_ele(str1);    //element
        } else {
            fgets(buffer, 200, pfile);    //element
            pstr = strchr(buffer, '>');
            pstr = strchr(pstr + 1, '>');
            tmp = strchr(pstr, '<');
            s_strncpy(str1, pstr + 1, tmp - pstr - 1);
            //node[cnt++] = atoi(str1);
            node[cnt++] = match_ele(str1);
            fgets(buffer, 200, pfile);
        }
    } while (fgets(buffer, 200, pfile), buffer[1] == 'n');
    node_cnt = cnt;


    if (node_cnt == 1)
        return;


    do {
        if (muta) {
            pstr = strchr(buffer, '\"');
            tmp = strchr(pstr + 1, '\"');
            s_strncpy(str1, pstr + 1, tmp - pstr - 1);
            a = atoi(str1) - 1;
            pstr = strchr(tmp + 1, '\"');
            tmp = strchr(pstr + 1, '\"');
            s_strncpy(str1, pstr + 1, tmp - pstr - 1);
            b = atoi(str1) - 1;

            pstr = strchr(tmp + 2, '>');
            pstr = strchr(pstr + 1, '>');
            if (pstr[1] == '0')
                g[a][b] = g[b][a] = 1000000; //valence=0 qu nin ma de
            else g[a][b] = g[b][a] = pstr[1] - '0';
        } else {
            pstr = strchr(buffer, '_');
            tmp = strchr(pstr + 1, '\"');
            s_strncpy(str1, pstr + 1, tmp - pstr - 1);
            a = atoi(str1) - 1;
            pstr = strchr(tmp + 1, '_');
            tmp = strchr(pstr + 1, '\"');
            s_strncpy(str1, pstr + 1, tmp - pstr - 1);
            b = atoi(str1) - 1;

            fgets(buffer, 200, pfile);
            pstr = strchr(buffer, '>');
            pstr = strchr(pstr + 1, '>');
            if (pstr[1] == '0')
                g[a][b] = g[b][a] = 1000000; //valence=0 qu nin ma de
            else g[a][b] = g[b][a] = pstr[1] - '0';
            fgets(buffer, 200, pfile);
        }
    } while (fgets(buffer, 200, pfile), buffer[1] == 'e');


    if (node_cnt < 40)
        muta = false;
    
}

void chemgraph::graph_for_matching(){
    graph_new = new int[node_cnt*node_cnt];
    for (int i=0; i<node_cnt; i++)
        for (int j=0; j<node_cnt; j++){
            graph_new[i*node_cnt+j] = g[i][j];
        }
    for (int i=0; i<node_cnt; i++)
        graph_new[i*node_cnt+i] = node[i];
}

void chemgraph::muta_avoid_H() {
    printf("original:\n");
    printchem();
    if (muta) {
        map<string, int>::iterator it = ele.find("H");
        if (it == ele.end()) {
            muta = false;
            return;
        }
        int H_num = it->second;
        int node_cnt_new = 0;
        int node_new[MAX_NODE];
        int graph_new[MAX_NODE][MAX_NODE];
        memset(node_with_H, 0, sizeof(node_with_H));
        memset(graph_new, 0, sizeof(graph_new));
        for (int i = 0; i < node_cnt; i++)
            if (node[i] != H_num) {
                node_new[node_cnt_new] = node[i];
                node_cnt_new++;
            }
        int tmp_node = 0;
        printf("%d\n", H_num);
        for (int i = 0; i < node_cnt; i++) {
            if (node[i] == H_num)
                continue;
            int tmp_node_cnt = 0;
            for (int j = 0; j < node_cnt; j++) {
                if (node[i] == H_num && g[i][j] > 0) {
                    node_with_H[tmp_node]++;
                } else if (g[i][j] > 0) {
                    graph_new[tmp_node][tmp_node_cnt] = g[i][j];
                    tmp_node_cnt++;
                }
            }
            tmp_node++;
        }

        node_cnt = node_cnt_new;
        memset(node, 0, sizeof(node));
        memset(g, 0, sizeof(g));
        for (int i = 0; i < node_cnt; i++) {
            node[i] = node_new[i];
            for (int j = 0; j < node_cnt; j++)
                g[i][j] = graph_new[i][j];
        }
        for (int i = 0; i < node_cnt; i++)
            printf("%d ", node_with_H[i]);
    }
    printf("then:\n");
    printchem();
}

void chemgraph::printchem() {
    printf("nodes and there tags: \n");
    for (int i = 0; i < node_cnt; i++)
        printf("%d ", node[i]);
    printf("\n");
    printf("edges: \n");
    for (int i = 0; i < node_cnt; i++) {
        for (int j = 0; j < node_cnt; j++)
            printf("%d ", g[i][j]);
        printf("\n");
    }
    printf("\n");
}
