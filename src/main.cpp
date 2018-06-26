#include <iostream>
#include "input.hpp"
#include "genCost.hpp"
//#include <omp.h>
#include <cstring>
#define MAX_NODE 75
#define MAX_DSIZE 5600
int cvd=4, ced=2, cvs=2, ces=1;
char filename1[]="g1.gxl", filename2[]="g2.gxl";
//chemgraph g1, g2;
//costMat delta;

int main()
{
    //cin>>cvd>>ced>>cvs>>ces;
    chemgraph g1=chemgraph(filename1), g2=chemgraph(filename2);
    costMat delta=costMat(cvd, ced, cvs, ces, g1, g2);
    //g1.printchem(), g2.printchem();
    //delta.printCost();
    //delta.printDelta();
}
