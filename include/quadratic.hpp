//
//  quadratic.hpp
//  
//
//  Created by 吴怡凡 on 26/06/2018.
//
//

#ifndef QUADRATIC_HPP
#define QUADRATIC_HPP

#include <stdio.h>
#include "costMat.hpp"

void solveQuadratic(const costMat &c, double *x, int *b, double &s_k, double &l, double *mult_x_d);

#endif //QUADRATIC_HPP
