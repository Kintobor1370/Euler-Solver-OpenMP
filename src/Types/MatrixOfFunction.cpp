#include "MatrixOfFunction.hpp"


//_____________SQUARE MATRIX OF FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE_____________
MatrixOfFunction::MatrixOfFunction(int size)
{
    matOfFunc.resize(size);
    for (int i = 0; i < size; i++)
    {
        matOfFunc.at(i).resize(size);
    }
}

int MatrixOfFunction::size() 
{ 
    return matOfFunc.size(); 
}

Function& MatrixOfFunction::operator () (int rowIndex, int colIndex) 
{ 
    return matOfFunc.at(rowIndex).at(colIndex); 
}