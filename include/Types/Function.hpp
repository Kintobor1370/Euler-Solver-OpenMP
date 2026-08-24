#pragma once 

#include <iosfwd>
#include "Vector.hpp"
#include "Matrix.hpp"

template<typename T> int sgn(T val) 
{ 
    return (T(0) < val) - (val < T(0)); 
}


//______________________FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE_____________________
class Function
{
    Vector x;
    Vector y;

public:
    Function(const int size = 0);

    Function(Vector xGrid, Vector yVals);

    Function(Vector xGrid, Matrix yVals);

    Function(Vector xGrid, Matrix yVals, CalcType xMax);

    int size();

    Vector X();

    Vector Y();

    static Function trim(Function func, CalcType xFinal);

    CalcType findY(CalcType xVal);

    std::pair<bool, CalcType> ConstantSign();

    CalcType Interpolate(CalcType xVal);

    CalcType Interpolate(CalcType xVal, CalcType asymptoticVal);

    CalcType IntegralRectangles();

    //....................All Y values + calculation type value
    friend Function operator + (Function baseFunc, CalcType addVal);

    //....................All Y values - calculation type value
    friend Function operator - (Function baseFunc, CalcType subVal);

    //....................All Y values * calculation type value
    friend Function operator * (Function baseFunc, CalcType comVal);

    //....................All Y values / calculation type value
    friend Function operator / (Function baseFunc, CalcType divVal);

    //....................Turn all Y values negative
    Function operator - ();

    //....................Display function values
    //....................Format:
    //....................   X: x1   Y: y1
    //....................   X: x2   Y: y2
    //....................   ...
    //....................   X: xn   Y: yn
    friend std::ostream& operator << (std::ostream& out, Function &f);
};