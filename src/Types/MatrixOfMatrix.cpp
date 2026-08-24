#include "MatrixOfMatrix.hpp"


//____________________________MATRIX OF MATRIX OF CALCULATION TYPE_____________________________
MatrixOfMatrix::MatrixOfMatrix(const int size)
{
    matOfMat.resize(size);
    for (int i = 0; i < size; i++)
    {
        matOfMat.at(i).resize(size);
    }
}

int MatrixOfMatrix::size() 
{ 
    return matOfMat.size(); 
}

Matrix& MatrixOfMatrix::operator () (const int rowIndex, const int colIndex) 
{ 
    return matOfMat.at(rowIndex).at(colIndex); 
}