//
// Created by 卢思睿 on 2018/6/29.
//


#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>

void randomInit(double *x, int c_n, int c_m, int max_row_sample_times, int max_col_sample_times, int max_assign_times) {
    srand(time(NULL));
    memset(x, 0, sizeof(double) * c_n * c_m);
    int assigned_times = 0;
    bool *row_assigned = new bool[c_n - 1];
    bool *col_assigned = new bool[c_m - 1];
    memset(row_assigned, 0, sizeof(bool) * (c_n - 1));
    memset(col_assigned, 0, sizeof(bool) * (c_m - 1));
    for (int i = 0; i < max_row_sample_times; ++i) {
        int row = rand() % (c_n - 1);
        if (row_assigned[row]) {
            continue;
        } else {
            for (int j = 0; j < max_col_sample_times; ++j) {
                int col = rand() % (c_m - 1);
                if (col_assigned[col])
                    continue;
                x[row * c_m + col] = 1;
                col_assigned[col] = true;
                row_assigned[row] = true;
                ++assigned_times;
                break;
            }
        }
        if (assigned_times == max_assign_times)
            break;
    }
    for (int i = 0; i < c_m; ++i) {
        if (col_assigned[i])
            continue;
        x[(c_n - 1) * c_m + i] = true;
    }
    for (int i = 0; i < c_n; ++i) {
        if (row_assigned[i])
            continue;
        x[(i + 1) * c_m - 1] = true;
    }
    x[c_n * c_m - 1] = true;
}

void diagonalInit(double *x, int c_n, int c_m) {
    for (int i=0; i<std::min(c_n, c_m); i++)
        x[i*c_m+c_m - 1 - i]=1;
    if (c_n>c_m){
        for (int i=c_m; i<c_n; i++)
            x[(i+1)*c_m-1]=1;
    }
    else{
        for(int i=c_n; i<c_m; i++)
            x[(c_n-1)*c_m+i]=1;
    }
    x[c_n*c_m-1]=1;
}