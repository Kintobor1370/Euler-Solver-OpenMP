#include "VectorOfMatrix.hpp"


//____________________________VECTOR OF MATRIX OF CALCULATION TYPE_____________________________
VectorOfMatrix::VectorOfMatrix(const int size)
{ 
    vecOfMat.resize(size);
}

int VectorOfMatrix::size()
{ 
    return vecOfMat.size(); 
}

Matrix& VectorOfMatrix::operator () (const int index)
{ 
    return vecOfMat.at(index); 
}