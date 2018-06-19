//
// Created by 卢思睿 on 2018/6/8.
//

#ifndef GED_LSAPE_H
#define GED_LSAPE_H

void
preProcessing(double *cost, int *rho, int *varrho,
              double *u, double *v,
              int n, int m, int &nass, int &mass);

void
augmentCol(int k, double *cost, const int *rho, const int *varrho,
           int *U, int *SV, int *pred, double *pi, // for reuse, pred is a return value
           int &zi, int &zj, double *u, double *v, // returns
           int n, int m);

void
augmentRow(int k, double *cost, const int *rho, const int *varrho,
           int *V, int *SU, int *pred, double *pi, // for reuse, pred is a return value
           int &zi, int &zj, double *u, double *v, // returns
           int n, int m);

void
hungarianLSAPE(double *cost, int n, int m, int *rho, int *varrho, double *u, double *v);

#endif //GED_LSAPE_H
