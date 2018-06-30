//
// Created by 卢思睿 on 2018/6/30.
//

#include "dataset.hpp"

int main() {
    srand(time(NULL));
    pah d("../gdc-c1/pah", 0.4);
    Result result(d, 2, 4, 1, 2);
    auto x = d.getAllRunningCases();
    result.run(3);
    result.writeCSV("./pah.csv");
}