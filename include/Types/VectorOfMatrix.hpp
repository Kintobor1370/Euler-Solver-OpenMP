#pragma once 

#include "Matrix.hpp"


//____________________________VECTOR OF MATRIX OF CALCULATION TYPE_____________________________
class VectorOfMatrix
{
    std::vector<Matrix> vecOfMat;

public:
    VectorOfMatrix(const int size = 0);

    //....................Returns the size of Vector of Matrix
    int size();

    //....................Vector of Matrix indexing operator
    Matrix& operator () (const int index);
};