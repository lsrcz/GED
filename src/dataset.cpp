//
// Created by 卢思睿 on 2018/6/30.
//

#include "dataset.hpp"
#include <dirent.h>
#include <init.hpp>
#include <IPFP.hpp>

void Dataset::readFromDir(const char *dirname, double sample_rate) {
    DIR *dir = opendir(dirname);
    struct dirent *ptr;
    char buffer[1024];
    if (dir == nullptr) {
        fprintf(stderr, "Directory %s doen't exist", dirname);
        exit(-1);
    }
    int cnt = 0;
    while ((ptr = readdir(dir))) {
        if ((double)rand() / RAND_MAX > sample_rate)
            continue;
        strcpy(buffer, dirname);
        strcat(buffer, "/");
        strcat(buffer, ptr->d_name);
        if (strlen(buffer) < 3)
            continue;
        if (strcmp(buffer + (strlen(buffer) - 3), "gxl") == 0) {
            graphs.emplace_back(buffer);
            names.emplace_back(ptr->d_name);
        }
    }
    printf("sample size: %ld\n", graphs.size());
    closedir(dir);
    num = graphs.size();
}

std::vector<std::pair<const chemgraph&, const chemgraph&>> Dataset::getAllPairs() const {
    std::vector<std::pair<const chemgraph&, const chemgraph&>> ret;
    for (int i = 0; i < graphs.size(); ++i) {
        for (int j = i + 1; j < graphs.size(); ++i) {
            ret.emplace_back(graphs[i], graphs[j]);
        }
    }
    return ret;
};

std::vector<RunningCase> Dataset::getAllRunningCases() const {
    std::vector<RunningCase> ret;
    for (int i = 0; i < graphs.size(); ++i) {
        for (int j = i + 1; j < graphs.size(); ++j) {
            ret.emplace_back(names[i], names[j], graphs[i], graphs[j]);
        }
    }
    return ret;
}

Acyclic::Acyclic(const char *basedir, double sample_rate) {
    readFromDir(basedir, sample_rate);
};

pah::pah(const char *basedir, double sample_rate) {
    readFromDir(basedir, sample_rate);
}

Result::Result(const Dataset &dataset_, int cvs_, int cvd_, int ces_, int ced_)
        : dataset(dataset_), num(dataset_.size()), cvs(cvs_), cvd(cvd_), ces(ces_), ced(ced_) {
}

void Result::run(int test_times) {
    this->test_times = test_times;
    int pcnt = 0;
    for (auto p : dataset.getAllRunningCases()) {
        printf("%d\n", pcnt++);
        SingleResult singleResult(p.namepair.first, p.namepair.second);
        auto start = clock();

        costMat delta(cvd, ced, cvs, ces, p.graphpair.first, p.graphpair.second);
        auto x = (double *) calloc(delta.d_n, sizeof(double));
        for (int i = 0; i < test_times; ++i) {
            // diagonalInit(x, delta.c_n, delta.c_m);
            randomInit(x, delta.c_n, delta.c_m, delta.c_n, delta.c_m, 10000);
            IPFPmin(x, delta);

            double running_time = (double) (clock() - start) / CLOCKS_PER_SEC;

            auto ged = (int) delta.computeCost(x);
            singleResult.add(ged, running_time);
        }
        results.push_back(singleResult);
        free(x);
    }
}

void Result::writeCSV(const char *filename) {
    FILE * f = fopen(filename, "w");
    fprintf(f, "file1,file2");
    for (int i = 1; i <= test_times; ++i) {
        fprintf(f, ",test case %d", i);
    }
    fprintf(f, ",min ged,avg time\n");
    for (const auto &result : results) {
        fprintf(f, "\"%s\",\"%s\"", result.getNamePair().first.c_str(), result.getNamePair().second.c_str());
        int ged = INT32_MAX;
        double tot_time = 0;
        for (const auto &x : result.getValues()) {
            fprintf(f, ",%d", x.first);
            ged = std::min(ged, x.first);
            tot_time += x.second;
        }
        fprintf(f, ",%d", ged);
        fprintf(f, ",%f\n", tot_time / test_times);
    }
}