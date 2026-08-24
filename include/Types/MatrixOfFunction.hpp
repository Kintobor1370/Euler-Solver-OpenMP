#pragma once 

#include "Function.hpp"


//_____________SQUARE MATRIX OF FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE_____________
class MatrixOfFunction
{
    std::vector<std::vector<Function>> matOfFunc;

public:
    MatrixOfFunction(int size = 0);

    //....................Returns numbers of rows & columns in Matrix of Function
    int size();

    //....................Matrix of Function indexing operator
    Function& operator () (int rowIndex, int colIndex);
};
