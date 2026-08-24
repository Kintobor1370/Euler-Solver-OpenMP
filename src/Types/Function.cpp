#include <iostream>
#include <cmath>
#include <map>
#include <algorithm>
#include <cassert>
#include "Function.hpp"

using namespace std;


//______________________FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE_____________________
Function::Function(const int size)
{
    x.resize(size);
    y.resize(size);
}

Function::Function(Vector xGrid, Vector yVals) : x(xGrid), y(yVals) {}

Function::Function(Vector xGrid, Matrix yVals)
{
    map<CalcType, CalcType> XY;
    for (int i=0; i<xGrid.size(); i++)
    {
        for (int j=i; j<xGrid.size(); j++)
        {
            assert (abs(yVals[i][j] - yVals[j][i]) < EPSILON);
            CalcType xHypot = hypot(xGrid[i], xGrid[j]);
            XY.insert({ xHypot, yVals[i][j] });
        }
    }
    for (auto coord : XY)
    {
        x.add(coord.first);
        y.add(coord.second);
    }
}

Function::Function(Vector xGrid, Matrix yVals, CalcType xMax)
{
    map<CalcType, CalcType> XY;
    for (int i=0; i<xGrid.size(); i++)
    {
        for (int j=i; j<xGrid.size(); j++)
        {
            assert (abs(yVals[i][j] - yVals[j][i]) < EPSILON);
            CalcType xHypot = hypot(xGrid[i], xGrid[j]);
            XY.insert({ xHypot, yVals[i][j] });
        }
    }
    
    map<CalcType, CalcType>::iterator it = XY.begin();
    while (it != XY.end() && it->first <= xMax)
    {
        x.add(it->first);
        y.add(it->second);
    }
}

int Function::size()
{ 
    return x.size(); 
}

Vector Function::X() 
{ 
    return x; 
}

Vector Function::Y() 
{ 
    return y; 
}

static Function trim(Function func, CalcType xFinal)
{
    auto xVals = func.X().get_vector();
    auto it = find(xVals.begin(), xVals.end(), xFinal);
    assert (it != xVals.end());
    int finalIndex = distance(xVals.begin(), it);
    
    Vector xValsTrimmed;
    Vector yValsTrimmed;
    for (int i=0; i<=finalIndex; i++)
    {
        xValsTrimmed.add(func.X()[i]);
        yValsTrimmed.add(func.Y()[i]);
    }
    return Function(xValsTrimmed, yValsTrimmed);
}

CalcType Function::findY(CalcType xVal)
{
    assert ((xVal >= x[0]) && (xVal <= x.last()));
    
    vector<CalcType> xStl = x.get_vector();
    vector<CalcType>::iterator it = find(xStl.begin(), xStl.end(), xVal);
    assert (it != xStl.end());
    
    int index = distance(xStl.begin(), it);
    return y[index];
}

pair<bool, CalcType> Function::ConstantSign()
{
    bool isConstant = true;
    int signInit = sgn(y[1] - y[0]);
    CalcType val = 0;
    for (int i=2; i<y.size(); i++)
    {
        int sign = sgn(y[i] - y[i-1]);
        if ((sign != signInit) && (sign != 0))
        {
            isConstant = false;
            val = x[i];
        }
    }
    return make_pair(isConstant, val);
}

CalcType Function::Interpolate(CalcType xVal)
{
    int i = 1;
    while (xVal > x[i])
    {
        i++;
    }
    /**
    cout << "X[i-1] = " << x[i - 1]
            << "   X[i] = " << x[i] 
            << "\nY[i-1] = " << y[i - 1] 
            << "   Y[i] = " << y[i] << "\n\n";
    */
    CalcType weight = (xVal - x[i - 1]) / (x[i] - x[i - 1]);
    CalcType yVal = y[i - 1] + weight * (y[i] - y[i - 1]);
    return yVal;
}

CalcType Function::Interpolate(CalcType xVal, CalcType asymptoticVal)
{
    if (xVal > x.last())
    {
        return asymptoticVal;
    }
    int i = 1;
    while (xVal > x[i])
    {
        i++;
    }
    CalcType weight = (xVal - x[i - 1]) / (x[i] - x[i - 1]);
    CalcType yVal = y[i - 1] + weight * (y[i] - y[i - 1]);
    return yVal;
}

CalcType Function::IntegralRectangles()
{
    assert (x.size() % 2 == 1);

    CalcType integral = 0;
    CalcType step = (2 * (x.last() - x[0])) / x.size();
    for (int i=1-x.size(); i<x.size()-1; i+=2)
        integral += y[abs(i + 1)];
    
    assert (integral != 0);
    integral *= step;
    return integral;
}

Function operator + (Function baseFunc, CalcType addVal)
{
    Vector Y = baseFunc.Y();
    Vector YNew;
    for (int i = 0; i < Y.size(); i++)
    {
        YNew.add(Y[i] + addVal);
    }
    Function funcNew(baseFunc.X(), YNew);
    return funcNew;
}

Function operator - (Function baseFunc, CalcType subVal)
{
    Vector Y = baseFunc.Y();
    Vector YNew;
    for (int i = 0; i < Y.size(); i++)
    {
        YNew.add(Y[i] - subVal);
    }
    Function funcNew(baseFunc.X(), YNew);
    return funcNew;
}

Function operator * (Function baseFunc, CalcType comVal)
{
    Vector Y = baseFunc.Y();
    Vector YNew;
    for (int i = 0; i < Y.size(); i++)
    {
        YNew.add(Y[i] * comVal);
    }
    Function funcNew(baseFunc.X(), YNew);
    return funcNew;
}

Function operator / (Function baseFunc, CalcType divVal)
{
    Vector Y = baseFunc.Y();
    Vector YNew;
    for (int i = 0; i < Y.size(); i++)
    {
        YNew.add(Y[i] / divVal);
    }
    Function funcNew(baseFunc.X(), YNew);
    return funcNew;
}

Function Function::operator - ()
{
    Vector YNew;
    for (int i = 0; i < y.size(); i++)
    {
        YNew.add(-1 * y[i]);
    }
    Function funcNew(x, YNew);
    return funcNew;
}

ostream& operator << (ostream& out, Function &f)
{
    for(int i = 0; i < f.size(); i++)
    {
        out << "X: " << f.x[i] << "   Y: " << f.y[i] << '\n';
    }
    return out;
}