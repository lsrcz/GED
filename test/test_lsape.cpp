//
// Created by 卢思睿 on 2018/6/20.
//
#include "lsape.hpp"
#include "lsap.hpp"
#include "matop.hpp"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>

using std::cout;
using std::endl;

void test_augment() {
    double cost[] = {
            8, 2, 0, 1, 2, 1, 3,
            2, 4, 4, 6, 5, 7, 1,
            0, 4, 3, 1, 8, 5, 4,
            1, 3, 2, 0, 0, 0, 1,
            2, 0, 1, 3, 4, 5, 3,
            4, 0, 1, 7, 8, 4, 0
    };
    int k = 4;
    int rho[] = {3,0,1,4,0};
    int varrho[] = {3,6,1,4,0,0};
    int U[1000];
    int SV[1000];
    int pred[1000];
    double pi[1000];
    int zi = 0;
    int zj = 0;
    double u[] = {0,0,0,0,0};
    double v[] = {0,0,0,0,0,0};
    int n = 5, m = 6;
    augmentCol(k,cost,rho,varrho,U,SV,pred,pi,zi,zj,u,v,n,m);
    int j = 0;
}

void test_one() {
    double c[] = {
            7, 11, 9, 8, 9, 10,
            2, 8, 8, 5, 7, 3,
            1, 7, 6, 6, 9, 5,
            3, 7, 6, 2, 2, 3,
            4, 2, 2, 7, 8, 0
    };
    double c1[] = {
            7, 11, 9, 8, 9, 10, 1e300, 1e300, 1e300,
            2, 8, 8, 5, 7, 1e300, 3, 1e300, 1e300,
            1, 7, 6, 6, 9, 1e300, 1e300, 5, 1e300,
            3, 7, 6, 2, 2, 1e300, 1e300, 1e300, 3,
            4, 1e300, 1e300, 1e300, 1e300, 0, 0, 0, 0,
            1e300, 2, 1e300, 1e300, 1e300, 0, 0, 0, 0,
            1e300, 1e300, 2, 1e300, 1e300, 0, 0, 0, 0,
            1e300, 1e300, 1e300, 7, 1e300, 0, 0, 0, 0,
            1e300, 1e300, 1e300, 1e300, 8, 0, 0, 0, 0
    };
    int b[100];

    solveLSAP(c1, b, 9);
    double bc[100];
    for (int i = 0; i < 81; ++i)
        bc[i] = b[i];
    cout << "dot" << dot(c1,bc,81) << endl;

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (b[i * 9 + j] == 1)
                cout << j << endl;

    int n = 4;
    int m = 5;
    int rho[n];
    int varrho[m];
    double u[n + 1];
    double v[m + 1];
    int nass, mass;
    hungarianLSAPE(c, n, m, rho, varrho, u, v);
    //preProcessing(c,rho,varrho,u,v,n,m,nass,mass);
    cout << "u" << endl;
    for (int i = 0; i <= n; ++i) {
        cout << u[i] << " ";
    }
    cout << endl;
    cout << "v" << endl;
    for (int i = 0; i <= m; ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "rho" << endl;
    for (int i = 0; i < n; ++i) {
        cout << rho[i] << " ";
    }
    cout << endl;
    cout << "varrho" << endl;
    for (int i = 0; i < m; ++i) {
        cout << varrho[i] << " ";
    }
    cout << endl;
    int j = 0;
    int b1[1000];
    double b2[1000];
    solveLSAPE(c, n, m, b1);
    for (int i = 0; i < 50; ++i) {
        cout << b1[i] << endl;
        b2[i] = b1[i];
    }
    cout << "dot" << dot(c, b2, 30) << endl;
}

bool auto_compare_lsap_lsape(int n, int m) {
    auto clsape = new double[(n + 1) * (m + 1)];
    auto clsap = new double[(n + m) * (n + m)];
    memset(clsape, 0, sizeof(double) * (n + 1) * (m + 1));
    memset(clsap, 0, sizeof(double) * (n + m) * (n + m));
    for (int i = 0; i < n; ++i) {
        for (int j = m; j < m + n; ++j) {
            clsap[i * (m + n) + j] = 1e300;
        }
    }
    for (int i = n; i < m + n; ++i) {
        for (int j = 0; j < m; ++j) {
            clsap[i * (m + n) + j] = 1e300;
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i != n) {
                if (j != m) {
                    clsape[i * (m + 1) + j] = clsap[i * (m + n) + j] = rand();
                } else {
                    clsape[i * (m + 1) + j] = clsap[i * (m + n) + m + i] = rand();
                }
            } else {
                if (j != m) {
                    clsape[i * (m + 1) + j] = clsap[(m + j) * (m + n) + j] = rand();
                } else {

                }
            }
        }
    }
    auto blsape = new int[(n + 1) * (m + 1)];
    auto blsap = new int[(n + m) * (n + m)];
    solveLSAP(clsap, blsap, n + m);
    solveLSAPE(clsape, n, m, blsape);
    double dotlsape = dot(clsape, blsape, (n + 1) * (m + 1));
    double dotlsap = dot(clsap, blsap, (n + m) * (n + m));
    cout << dotlsap << " " << dotlsape << endl;
    delete[] blsap;
    delete[] blsape;
    delete[] clsap;
    delete[] clsape;
    return fabs(dotlsap - dotlsape) / dotlsap <= 1e-9;
}

int main() {
    srand(time(0));
    for (int i = 0; i < 10000; ++i) {
        cout << i << endl;
        assert(auto_compare_lsap_lsape(71, 71));
    }
}
