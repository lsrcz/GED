//
// Created by 卢思睿 on 2018/6/4.
//

#include "lsap.hpp"
#include <cstring>
#include <algorithm>
#include <iostream>

// maximum points, 140 is sufficient
const int N = 150;
const int INF = 0x3f3f3f3f;
const long long TINF = 0x7f7f7f7f7f7f7f7f;
const double DINF = *(reinterpret_cast<const double *>(&TINF));
bool visitx[N], visity[N];
double lx[N], ly[N];
double slack[N];
int match[N];

bool Hungary(double *mat, int size, int u) {
    visitx[u] = true;
    for (int i = 0; i < size; ++i) {
        if (visity[i])
            continue;
        if (lx[u] + ly[i] == -mat[u * size + i]) {
            visity[i] = true;
            if (match[i] == -1 || Hungary(mat, size, match[i])) {
                match[i] = u;
                return true;
            }
        } else
            slack[i] = std::min(slack[i], lx[u] + ly[i] + mat[u * size + i]);
    }
    return false;
}

void solveLSAP(double *mat, int *b, int size) {
    double temp;
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    memset(match, -1, sizeof(match));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            lx[i] = std::max(lx[i], -mat[i * size + j]);
    for (int i = 0; i < size; ++i) {
        memset(slack, 0x7f, sizeof(slack));
        while (true) {
            memset(visitx, false, sizeof(visitx));
            memset(visity, false, sizeof(visity));
            if (Hungary(mat, size, i))
                break;
            else {
                temp = DINF;
                for (int j = 0; j < size; ++j)
                    if (!visity[j])
                        if (temp > slack[j])
                            temp = slack[j];
                for (int j = 0; j < size; ++j) {
                    if (visitx[j])
                        lx[j] -= temp;
                    if (visity[j])
                        ly[j] += temp;
                    else
                        slack[j] -= temp;
                }
            }
        }
    }
    double ans;
    memset(b, 0, sizeof(int) * size * size);
    for (int i = 0; i < size; ++i) {
        b[match[i] * size + i] = 1;
    }
}
