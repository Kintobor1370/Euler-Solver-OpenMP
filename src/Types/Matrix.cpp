#include <iostream>
#include <algorithm>
#include "Matrix.hpp"

using namespace std;


//______________________________SQUARE MATRIX OF CALCULATION TYPE_____________________________
Matrix::Matrix(const int size)
{ 
    resize(size); 
}

Matrix::Matrix(const int size, CalcType val)
{
    mat.reserve(size);
    for (int i = 0; i < size; i++)
    {
        mat.push_back(Vector(size, val));
    }
}

Vector& Matrix::operator [] (const int rowNum)
{ 
    return mat.at(rowNum); 
}

int Matrix::size()
{ 
    return mat.size(); 
}

void Matrix::resize(const int newSize)
{
    mat.resize(newSize);
    for (auto &col : mat)
    {
        col.resize(newSize);
    }
}

void Matrix::resize(const int r, const int c)
{
    mat.resize(r);
    for (int i = 0; i < r; i++)
    {
        mat[i].resize(c);
    }
}

Vector Matrix::Row(const int rowNum) 
{ 
    return mat.at(rowNum); 
}

Vector Matrix::Col(const int colNum)
{
    Vector col(mat.size());
    for (int i = 0; i < mat.size(); i++)
    {
        col[i] = mat.at(i)[colNum];
    }
    return col;
}

CalcType Matrix::min_value()
{
    vector<CalcType> minVals;
    minVals.reserve(mat.size());
    for (int i = 0; i < mat.size(); i++)
    {
        minVals.push_back(mat.at(i).min_value());
    }
    return *min_element(minVals.begin(), minVals.end());
}

CalcType Matrix::max_value()
{
    vector<CalcType> maxVals;
    maxVals.reserve(mat.size());
    for (int i = 0; i < mat.size(); i++)
    {
        maxVals.push_back(mat.at(i).max_value());
    }
    return *max_element(maxVals.begin(), maxVals.end());
}

Matrix operator + (Matrix baseMat, CalcType addVal)
{
    Matrix sum(baseMat.size());
    for (int i = 0; i < sum.size(); i++)
    {
        for (int j = 0; j < sum.size(); j++)
        {
            sum[i][j] = baseMat[i][j] + addVal;
        }
    }
    return sum;
}

Matrix operator - (Matrix baseMat, CalcType subVal)
{
    Matrix sub(baseMat.size());
    for (int i = 0; i < sub.size(); i++)
    {
        for (int j = 0; j < sub.size(); j++)
        {
            sub[i][j] = baseMat[i][j] - subVal;
        }
    }
    return sub;
}

Matrix operator * (Matrix baseMat, CalcType comVal)
{
    Matrix product(baseMat.size());
    for (int i = 0; i < product.size(); i++)
    {
        for (int j = 0; j < product.size(); j++)
        {
            product[i][j] = baseMat[i][j] * comVal;
        }
    }
    return product;
}

Matrix operator / (Matrix baseMat, CalcType divVal)
{
    Matrix quotient(baseMat.size());
    for (int i = 0; i < quotient.size(); i++)
    {
        for (int j = 0; j < quotient.size(); j++)
        {
            quotient[i][j] = baseMat[i][j] / divVal;
        }
    }
    return quotient;
}

Matrix Matrix::operator - ()
{
    Matrix negativeMat(mat.size());
    for (int i = 0; i < negativeMat.size(); i++)
    {
        for (int j = 0; j < negativeMat.size(); j++)
        {
            negativeMat[i][j] = -1 * mat.at(i)[j];
        }
    }
    return negativeMat;
}

ostream& operator << (ostream& out, const Matrix &m)
{
    for (int i = 0; i < m.mat.size(); i++)
    {
        out << m.mat.at(i);
    }
    return out;
}