#include "VectorOfFunction.hpp"


//_________________VECTOR OF FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE________________
VectorOfFunction::VectorOfFunction(int size)
{
    vecOfFunc.resize(size);
}

int VectorOfFunction::size()
{
    return vecOfFunc.size();
}

Function& VectorOfFunction::operator () (const int index)
{
    return vecOfFunc.at(index);
}