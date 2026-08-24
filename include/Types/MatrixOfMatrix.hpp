#pragma once 

#include "Matrix.hpp"


//____________________________MATRIX OF MATRIX OF CALCULATION TYPE_____________________________
class MatrixOfMatrix
{
    std::vector<std::vector<Matrix>> matOfMat;

public:
    MatrixOfMatrix(const int size = 0);

    //....................Returns numbers of rows & columns in Matrix of Matrix
    int size();

    //....................Matrix of Matrix indexing operator
    Matrix& operator () (const int rowIndex, const int colIndex);
};