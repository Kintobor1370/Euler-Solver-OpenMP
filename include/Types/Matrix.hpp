#pragma once 

#include <iosfwd>
#include "Vector.hpp"


//______________________________SQUARE MATRIX OF CALCULATION TYPE_____________________________
class Matrix
{
    std::vector<Vector> mat;

public:
    Matrix(const int size = 0, const CalcType val = 0);

    Vector& operator [] (const int rowNum);

    int size() const;

    void resize(const int newSize);

    void resize(const int r, const int c);

    Vector Row(const int rowNum) const;

    Vector Col(const int colNum);

    //....................Returns an element of Matrix which has the lowest value
    CalcType min_value();

    //....................Returns an element of Matrix which has the highest value
    CalcType max_value();

    //....................Matrix + calculation type value
    friend Matrix operator + (Matrix baseMat, CalcType addVal);

    //....................Matrix - calculation type value
    friend Matrix operator - (Matrix baseMat, CalcType subVal);

    //....................Matrix * calculation type value
    friend Matrix operator * (Matrix baseMat, CalcType comVal);

    //....................Matrix / calculation type value
    friend Matrix operator / (Matrix baseMat, CalcType divVal);

    //....................-Matrix
    Matrix operator - ();

    //....................Display matrix of calculation type values
    //....................Format:
    //....................   x11, x12, ..., x1n
    //....................   x21, x22, ..., x2n
    //....................          ...
    //....................   xn1, xn2, ..., xnn
    friend std::ostream& operator << (std::ostream& out, const Matrix &m);
};