//
// Created by 卢思睿 on 2018/6/30.
//

#ifndef GED_DATASET_HPP
#define GED_DATASET_HPP

#include "costMat.hpp"
#include <vector>

struct RunningCase {
    std::pair<std::string, std::string> namepair;
    std::pair<const chemgraph&, const chemgraph&> graphpair;
    RunningCase(std::string name1, std::string name2, const chemgraph& graph1, const chemgraph& graph2)
            : namepair(std::make_pair(std::move(name1), std::move(name2))), graphpair(std::pair<const chemgraph&, const chemgraph&>(graph1, graph2)) {
    }
};

class Dataset {
    int num;
    std::vector<chemgraph> graphs;
    std::vector<std::string> names;
protected:
    void readFromDir(const char* dirname, double sample_rate);
public:
    inline
    int size() const {return num;}
    std::vector<std::pair<const chemgraph&, const chemgraph&>> getAllPairs() const;
    std::vector<RunningCase> getAllRunningCases() const;
};

class Acyclic : public Dataset {
public:
    Acyclic(const char *basedir, double sample_rate);
};

class pah : public Dataset {
public:
    pah(const char *basedir, double sample_rate);
};

class SingleResult {
    const std::pair<std::string, std::string> names;
    std::vector<std::pair<int, double>> values;
public:
    SingleResult(std::string name1_, std::string name2_) : names(std::make_pair(std::move(name1_), std::move(name2_))) {}
    inline
    void add(int ged, double time) {
        values.emplace_back(ged, time);
    }
    inline
    const std::pair<std::string, std::string> &getNamePair() const {
        return names;
    }
    inline
    const std::vector<std::pair<int, double>> &getValues() const {
        return values;
    };
    inline
    void print() const {
        printf("%s, %s", names.first.c_str(), names.second.c_str());
        for (auto x : values) {
            printf("%d in %.4f seconds", x.first, x.second);
        }
    }
};

class Result {
    int cvs;
    int cvd;
    int ces;
    int ced;
    const Dataset &dataset;
    int num;
    std::vector<SingleResult> results;
    int test_times;
public:
    Result(const Dataset &dataset_, int cvs_, int cvd_, int ces_, int ced_);
    void run(int test_times);
    void writeCSV(const char *filename);
};

#endif //GED_DATASET_HPP
