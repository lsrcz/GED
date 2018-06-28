//
//  quadratic.hpp
//  
//
//  Created by 吴怡凡 on 26/06/2018.
//
//

#ifndef quadratic_hpp
#define quadratic_hpp

#include <stdio.h>
#include "genCost.hpp"

void solveQuadratic(const costMat& c, double* x, int* b, double& s_k, double& l, double* mult_x_d);

#endif /* quadratic_hpp */
