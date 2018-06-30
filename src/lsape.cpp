//
// Created by 卢思睿 on 2018/6/8.
//

#include <cstring>
#include <algorithm>
#include <cmath>
#include "utils.hpp"
#include "lsape.hpp"

using std::min;

void
preProcessing(double *cost, int *rho, int *varrho,
              double *u, double *v,
              int n, int m, int &nass, int &mass) {
    nass = mass = 0;
    u[n] = 0;
    v[m] = 0;
    for (int i = 0; i < n; ++i) {
        u[i] = cost[i * (m + 1)];
        for (int j = 1; j <= m; ++j) {
            u[i] = min(u[i], cost[i * (m + 1) + j]);
        }
    }
    for (int j = 0; j < m; ++j) {
        v[j] = cost[j] - u[0];
        for (int i = 1; i <= n; ++i) {
            v[j] = min(v[j], cost[i * (m + 1) + j] - u[i]);
        }
    }
    memset(rho, -1, sizeof(int) * n);
    memset(varrho, -1, sizeof(int) * m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (varrho[j] == -1 && doubleeq(u[i] + v[j], cost[i * (m + 1) + j])) {
                rho[i] = j;
                varrho[j] = i;
                ++nass;
                ++mass;
                break;
            }
        }
        if (rho[i] == -1 && doubleeq(cost[i * (m + 1) + m], u[i]))
            rho[i] = m, nass++;
    }
    for (int j = 0; j < m; ++j) {
        if (varrho[j] == -1 && doubleeq(cost[n * (m + 1) + j], v[j]))
            varrho[j] = n, mass++;
    }
}

void
augmentCol(int k, double *cost, const int *rho, const int *varrho,
           int *U, int *SV, int *pred, double *pi, // for reuse, pred is a return value
           int &zi, int &zj, double *u, double *v, // returns
           int n, int m) {
    int nrows = n + 1, mcols = m + 1;
    int j = k;
    int *SVptr = SV, *ulutop = U;
    const int *uend = U + n, *lusutop = U;

    // i in U
    for (int i = 0; i < n; ++i) {
        pi[i] = std::numeric_limits<double>::max();
        U[i] = i;
    }

    while (true) {
        // SV <- SV + {j}
        *SVptr = j;
        *(++SVptr) = -1;

        if (varrho[j] < n && cost[n * mcols + j] == v[j]) {
            zi = n;
            zj = j;
            return;
        }

        // i in U\LU
        for (int *uluptr = ulutop; uluptr != uend; ++uluptr) {
            int i = *uluptr;
            double cred = cost[i * mcols + j] - u[i] - v[j];
            if (cred < pi[i]) {
                pred[i] = j;
                pi[i] = cred;
                if (doubleeq(cred, 0)) {
                    if (rho[i] == -1 || rho[i] == m) {
                        zi = i;
                        zj = -1;
                        return;
                    }
                    // LU <- LU + {i}
                    int tmp = *ulutop;
                    *ulutop = i; // add i to LU, that is delete i from U/LU
                    *uluptr = tmp;
                    ++ulutop;
                }
            }
        }

        // update dual variables and find candidate nodes
        // LU\SU = empty
        if (lusutop == ulutop) {
            double delta = std::numeric_limits<double>::max();
            bool lstrw = false;
            // i in U\LU
            for (int *uluptr = ulutop; uluptr != uend; ++uluptr) {
                delta = std::min(delta, pi[*uluptr]);
            }
            // j in SV
            for (int *svptr = SV; *svptr != -1; ++svptr) {
                double cred = cost[n * mcols + *svptr] - v[*svptr];
                if (cred <= delta) {
                    delta = cred;
                    lstrw = true;
                    zj = *svptr;
                }
            }
            // j in SV
            for (int *svptr = SV; *svptr != -1; ++svptr)
                v[*svptr] += delta;
            // i in LU
            for (int *luptr = U; luptr != ulutop; ++luptr)
                u[*luptr] -= delta;
            if (lstrw) {
                zi = n;
                return;
            }
            // i in U\LU
            for (int *uluptr = ulutop; uluptr != uend; ++uluptr) {
                int i = *uluptr;
                pi[i] -= delta;
                if (doubleeq(pi[i], 0)) {
                    if (rho[i] == -1 || rho[i] == m) {
                        zi = i;
                        zj = -1;
                        return;
                    }
                    // LU <- LU + {i}
                    int tmp = *ulutop;
                    *ulutop = i;
                    *uluptr = tmp;
                    ++ulutop;
                }
            }
        }
        // SU <- top of LU\SU
        int i = *lusutop;
        ++lusutop;
        j = rho[i];
    }
}

void
augmentRow(int k, double *cost, const int *rho, const int *varrho,
           int *V, int *SU, int *pred, double *pi, // for reuse, pred is a return value
           int &zi, int &zj, double *u, double *v, // returns
           int n, int m) {
    int nrows = n + 1, mcols = m + 1;
    int i = k;
    int *SUptr = SU, *vlvtop = V;
    const int *vend = V + m, *lvsvtop = V;

    // j in V
    for (int j = 0; j < m; ++j) {
        pi[j] = std::numeric_limits<double>::max();
        V[j] = j;
    }

    while (true) {
        // SU <- SU + {i}
        *SUptr = i;
        *(++SUptr) = -1;

        if (rho[i] < m && cost[i * mcols + m] == u[m]) {
            zi = i;
            zj = m;
            return;
        }

        // j in V\LV
        for (int *vlvptr = vlvtop; vlvptr != vend; ++vlvptr) {
            int j = *vlvptr;
            double cred = cost[i * mcols + j] - u[i] - v[j];

            if (cred < pi[j]) {
                pred[j] = i;
                pi[j] = cred;
                if (doubleeq(cred, 0)) {
                    if (varrho[j] == -1 || varrho[j] == n) {
                        zi = -1;
                        zj = j;
                        return;
                    }
                    // LV <- LV + {j}
                    int tmp = *vlvtop;
                    *vlvtop = j; // add j to LV, that is delete j from V/LV
                    *vlvptr = tmp;
                    ++vlvtop;
                }
            }
        }

        // update dual variables and find candidate nodes
        // LV\SV = empty
        if (lvsvtop == vlvtop) {
            double delta = std::numeric_limits<double>::max();
            bool lstrw = false;
            // j in V\LV
            for (int *vlvptr = vlvtop; vlvptr != vend; ++vlvptr) {
                delta = std::min(delta, pi[*vlvptr]);
            }
            // i in SU
            for (int *suptr = SU; *suptr != -1; ++suptr) {
                double cred = cost[*suptr * mcols + m] - u[*suptr];
                if (cred <= delta) {
                    delta = cred;
                    lstrw = true;
                    zi = *suptr;
                }
            }
            // i in SU
            for (int *suptr = SU; *suptr != -1; ++suptr)
                u[*suptr] += delta;
            // j in LV
            for (int *lvptr = V; lvptr != vlvtop; ++lvptr)
                v[*lvptr] -= delta;
            if (lstrw) {
                zj = m;
                return;
            }
            // j in V\LV
            for (int *vlvptr = vlvtop; vlvptr != vend; ++vlvptr) {
                int j = *vlvptr;
                pi[j] -= delta;
                if (doubleeq(pi[j], 0)) {
                    if (varrho[j] == -1 || varrho[j] == n) {
                        zi = -1;
                        zj = j;
                        return;
                    }
                    // LV <- LV + {j}
                    int tmp = *vlvtop;
                    *vlvtop = j;
                    *vlvptr = tmp;
                    ++vlvtop;
                }
            }
        }
        // SV <- top of LV\SV
        int j = *lvsvtop;
        ++lvsvtop;
        i = varrho[j];
    }
}

void
hungarianLSAPE(double *cost, int n, int m, int *rho, int *varrho, double *u, double *v) {
    int nrows = n + 1, mcols = m + 1;
    int nass = 0, mass = 0;
    preProcessing(cost, rho, varrho, u, v, n, m, nass, mass);
    if (mass < m) {
        auto U = new int[nrows];
        auto SV = new int[mcols];
        auto pi = new double[n];
        auto pred = new int[n];
        for (int k = 0; k < m; ++k) {
            if (varrho[k] == -1) {
                int i, j;
                augmentCol(k, cost, rho, varrho, U, SV, pred, pi, i, j, u, v, n, m);
                if (i == n) {
                    int r = varrho[j];
                    varrho[j] = i;
                    i = r;
                } else {
                    j = -1;
                }
                while (j != k) {
                    j = pred[i];
                    rho[i] = j;
                    int r = varrho[j];
                    varrho[j] = i;
                    i = r;
                }
            }
        }
        delete[] U;
        delete[] SV;
        delete[] pi;
        delete[] pred;
    }
    if (nass < n) {
        auto V = new int[mcols];
        auto SU = new int[nrows];
        auto pi = new double[m];
        auto pred = new int[m];
        for (int k = 0; k < n; ++k) {
            if (rho[k] == -1) {
                int i, j;
                augmentRow(k, cost, rho, varrho, V, SU, pred, pi, i, j, u, v, n, m);
                if (j == m) {
                    int c = rho[i];
                    rho[i] = j;
                    j = c;
                } else {
                    i = -1;
                }
                while (i != k) {
                    i = pred[j];
                    varrho[j] = i;
                    int c = rho[i];
                    rho[i] = j;
                    j = c;
                }
            }
        }
        delete[] V;
        delete[] SU;
        delete[] pi;
        delete[] pred;
    }
}

void
solveLSAPE(double *cost, int n, int m, int *b) {
    auto rho = new int[n];
    auto varrho = new int[m];
    auto u = new double[n + 1];
    auto v = new double[m + 1];
    hungarianLSAPE(cost, n, m, rho, varrho, u, v);
    memset(b, 0, sizeof(int) * (n + 1) * (m + 1));
    for (int i = 0; i < n; ++i) {
        b[i * (m + 1) + rho[i]] = 1;
    }
    int basepos = n * (m + 1);
    for (int j = 0; j < m; ++j) {
        if (varrho[j] == n) {
            b[basepos + j] = 1;
        }
    }
    b[(n + 1) * (m + 1) - 1] = 1;
    delete[] v;
    delete[] u;
    delete[] varrho;
    delete[] rho;
}