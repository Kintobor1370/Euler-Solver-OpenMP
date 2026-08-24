#pragma once 

#include "Vector.hpp"
#include "Matrix.hpp"
#include "MatrixOfMatrix.hpp"
#include "MatrixOfFunction.hpp"

//__________________________________________________CONVERTION FUNCTIONS__________________________________________________
Vector MatrixToVector(Matrix mat, bool symmetric = false);

Vector MatrixOfMatrixToVector(MatrixOfMatrix matOfMat, bool symmetric = false);

Matrix VectorToMatrix(Vector vec, int matSize, bool symmetric = false);

MatrixOfMatrix VectorToMatrixOfMatrix(
    Vector vec, 
    int matOfMatSize, 
    int matSize, 
    bool symmetric = false
);

MatrixOfFunction VectorToMatrixOfFunction(
    Vector xVec, 
    Vector yVec, 
    int matOfFuncSize
);