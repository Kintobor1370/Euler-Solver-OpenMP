#pragma once 

#include "Function.hpp"


//_________________VECTOR OF FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE________________
class VectorOfFunction
{
    std::vector<Function> vecOfFunc;

public:
    VectorOfFunction(int size = 0);

    //....................Returns the size of Vector of Function
    int size();

    //....................Vector of Function indexing operator
    Function& operator () (const int index);
};