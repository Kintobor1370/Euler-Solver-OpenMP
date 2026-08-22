/**********************************************************************************************
**                                      TYPES HEADER FILE                                    **
**  This file contains classes for mathematical data structures used in Solver.cpp program.  **
**********************************************************************************************/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>

#define EPSILON 1e-08

using namespace std;


//_________________________________VECTOR OF CALCULATION TYPE__________________________________
Vector::Vector(vector<CalcType> stlVec)
{
    vec.assign(stlVec.begin(), stlVec.end());
}

Vector::Vector(const int size) 
{
    vec.resize(size); 
}

Vector::Vector(const int size, CalcType val)
{
    vec.reserve(size);
    for (int i=0; i<size; i++)
    {
        vec.push_back(val);
    }
}

vector<CalcType> Vector::get_vector()
{ 
    return vec; 
}

CalcType& Vector::operator [] (const int index) 
{ 
    return vec.at(index); 
}

bool Vector::empty() 
{ 
    return vec.empty(); 
}

int Vector::size() 
{ 
    return vec.size(); 
}

void Vector::resize(int newSize) 
{ 
    vec.resize(newSize); 
}

void Vector::clear() 
{ 
    vec.clear(); 
}

void Vector::sort() 
{ 
    sort(vec.begin(), vec.end()); 
}

void Vector::add(CalcType newItem)
{ 
    vec.push_back(newItem); 
}

void Vector::add(Vector newVec)
{
    vector<CalcType> newVecStl = newVec.get_vector();
    vec.insert(vec.end(), newVecStl.begin(), newVecStl.end());
}


bool Vector::add_unique(CalcType newItem)
{
    vector<CalcType>::iterator it = find(vec.begin(), vec.end(), newItem);
    if (it == vec.end())
    {
        vec.push_back(newItem);
        return true;
    }
    return false;
}

CalcType Vector::first() 
{ 
    return vec.at(0); 
}

CalcType Vector::last() 
{ 
    return vec.at(vec.size() - 1); 
}

Vector Vector::head(int n)                  
{
    vector<CalcType> vecHead(vec.begin(), vec.begin() + n);
    return Vector(vecHead); 
}

Vector Vector::tail(int n)
{
    vector<CalcType> vecTail(vec.end() - n, vec.end());
    return Vector(vecTail);
}

void Vector::erase_first(int n)
{
    for (int i=0; i<n; i++)
    {
        vec.erase(vec.begin());
    }
}

CalcType Vector::min_value()
{
    return *min_element(vec.begin(), vec.end()); 
}

CalcType Vector::max_value() 
{ 
    return *max_element(vec.begin(), vec.end()); 
}

CalcType Vector::sum() 
{ 
    return accumulate(vec.begin(), vec.end(), 0); 
}

CalcType Vector::avg_value() 
{ 
    return vec.empty() ? 0 : accumulate(vec.begin(), vec.end(), 0) / vec.size(); 
}

static Vector Vector::setLinSpaced(
    CalcType size, 
    CalcType minVal, 
    CalcType maxVal
) {
    Vector result(size);
    CalcType step = (maxVal - minVal) / (size - 1);
    for (int i=0; i<size-1; i++)
    {
        result[i] = minVal + i * step;
    }
    result[size - 1] = maxVal;
    return result;
}

static Vector Vector::log(Vector arg)
{
    vector<CalcType> argVec = arg.get_vector();
    vector<CalcType> logVec = argVec;
    transform(argVec.begin(), argVec.end(), logVec.begin(), [](CalcType a) {
        return log(a);
    });
    return Vector(logVec);
}

static Vector Vector::abs(Vector arg)
{
    vector<CalcType> argVec = arg.get_vector();
    vector<CalcType> absVec = argVec;
    transform(argVec.begin(), argVec.end(), absVec.begin(), [](CalcType a) {
        return abs(a);
    });
    return Vector(absVec);
}

Vector Vector::operator + (CalcType addVal)
{
    vector<CalcType> sum = vec;
    transform(vec.begin(), vec.end(), sum.begin(), [addVal](CalcType a){
        return a + addVal;
    });
    return Vector(sum);
}

Vector Vector::operator - (CalcType subVal)
{
    vector<CalcType> sub = vec;
    transform(vec.begin(), vec.end(), sub.begin(), [subVal](CalcType a){
        return a - subVal;
    });
    return Vector(sub);
}

//....................-Vector
Vector Vector::operator - ()
{
    vector<CalcType> negativeVec = vec;
    transform(vec.begin(), vec.end(), negativeVec.begin(), [](CalcType a){
        return a * -1;
    });
    return Vector(negativeVec);
}

Vector Vector::operator * (CalcType comVal)
{
    vector<CalcType> product = vec;
    transform(vec.begin(), vec.end(), product.begin(), [comVal](CalcType a){
        return a * comVal;
    });
    return Vector(product);
}

Vector Vector::operator / (CalcType divVal)
{
    vector<CalcType> quotient = vec;
    transform(vec.begin(), vec.end(), quotient.begin(), [divVal](CalcType a){
        return a / divVal;
    });
    return quotient;
}

Vector Vector::operator + (Vector addVec)
{
    int maxSize = max((int) vec.size(), (int) addVec.size());
    Vector sum(vec);
    sum.resize(maxSize);
    addVec.resize(maxSize);
    for (int i=0; i<maxSize; i++)
    {
        sum[i] += addVec[i];
    }
    return sum;
}

Vector Vector::operator - (Vector subVec)
{
    int maxSize = max((int) vec.size(), (int) subVec.size());
    Vector sub(vec);
    sub.resize(maxSize);
    subVec.resize(maxSize);
    for (int i=0; i<maxSize; i++)
    {
        sub[i] -= subVec[i];
    }
    return sub;
}

Vector Vector::operator * (Vector comVec)
{
    int maxSize = max((int) vec.size(), (int) comVec.size());
    Vector product(vec);
    product.resize(maxSize);
    comVec.resize(maxSize);
    for (int i=0; i<maxSize; i++)
    {
        product[i] *= comVec[i];
    }
    return product;
}

Vector Vector::operator / (Vector divVec)
{
    int maxSize = max((int) vec.size(), (int) divVec.size());
    Vector quotient(vec);
    quotient.resize(maxSize);
    divVec.resize(maxSize);
    for (int i=0; i<maxSize; i++)
    {
        quotient[i] /= divVec[i];
    }
    return quotient;
}

vector<CalcType>::iterator Vector::begin()
{ 
    return vec.begin(); 
}

vector<CalcType>::iterator Vector::end() 
{ 
    return vec.end(); 
}

friend ostream& Vector::operator << (ostream& out, const Vector &v)
{
    out << v.vec.at(0);
    for(int i=1; i<v.vec.size(); i++)
    {
        out << ", " << v.vec.at(i);
    }
    out << '\n';
    return out;
}

pair<int, CalcType> Vector::MaxStep()
{
    CalcType maxStep = vec.at(1) - vec.at(0);
    int maxStepIndex = 1;
    for (int i=2; i<vec.size(); i++)
    {
        CalcType currStep = vec.at(i) - vec.at(i - 1);
        if (currStep > maxStep)
        {
            maxStep = currStep;
            maxStepIndex = i;
        }
    }
    return make_pair(maxStepIndex, maxStep);
}


//______________________________SQUARE MATRIX OF CALCULATION TYPE_____________________________
Matrix::Matrix(const int size)
{ 
    resize(size); 
}

Matrix::Matrix(const int size, CalcType val)
{
    mat.reserve(size);
    for (int i=0; i<size; i++)
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
    for (int i=0; i<r; i++)
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
    for (int i=0; i<mat.size(); i++)
    {
        col[i] = mat.at(i)[colNum];
    }
    return col;
}

CalcType Matrix::min_value()
{
    vector<CalcType> minVals;
    minVals.reserve(mat.size());
    for (int i=0; i<mat.size(); i++)
    {
        minVals.push_back(mat.at(i).min_value());
    }
    return *min_element(minVals.begin(), minVals.end());
}

CalcType Matrix::max_value()
{
    vector<CalcType> maxVals;
    maxVals.reserve(mat.size());
    for (int i=0; i<mat.size(); i++)
    {
        maxVals.push_back(mat.at(i).max_value());
    }
    return *max_element(maxVals.begin(), maxVals.end());
}

Matrix Matrix::operator + (CalcType addVal)
{
    Matrix sum(mat.size());
    for (int i=0; i<sum.size(); i++)
    {
        for (int j=0; j<sum.size(); j++)
        {
            sum[i][j] = mat.at(i)[j] + addVal;
        }
    }
    return sum;
}

Matrix Matrix::operator - (CalcType subVal)
{
    Matrix sub(mat.size());
    for (int i=0; i<sub.size(); i++)
    {
        for (int j=0; j<sub.size(); j++)
        {
            sub[i][j] = mat.at(i)[j] - subVal;
        }
    }
    return sub;
}

Matrix Matrix::operator - ()
{
    Matrix negativeMat(mat.size());
    for (int i=0; i<negativeMat.size(); i++)
    {
        for (int j=0; j<negativeMat.size(); j++)
        {
            negativeMat[i][j] = -1 * mat.at(i)[j];
        }
    }
    return negativeMat;
}

Matrix Matrix::operator * (CalcType comVal)
{
    Matrix product(mat.size());
    for (int i=0; i<product.size(); i++)
    {
        for (int j=0; j<product.size(); j++)
        {
            product[i][j] = mat.at(i)[j] * comVal;
        }
    }
    return product;
}

Matrix Matrix::operator / (CalcType divVal)
{
    Matrix quotient(mat.size());
    for (int i=0; i<quotient.size(); i++)
    {
        for (int j=0; j<quotient.size(); j++)
        {
            quotient[i][j] = mat.at(i)[j] / divVal;
        }
    }
    return quotient;
}

friend ostream& Matrix::operator << (ostream& out, const Matrix &m)
{
    for (int i=0; i<m.mat.size(); i++)
    {
        out << m.mat.at(i);
    }
    return out;
}


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


//____________________________MATRIX OF MATRIX OF CALCULATION TYPE_____________________________
MatrixOfMatrix::MatrixOfMatrix(const int size)
{
    matOfMat.resize(size);
    for (int i=0; i<size; i++)
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

static Function Function::trim(Function func, CalcType xFinal)
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

Function Function::operator + (CalcType add_val)
{
    Vector new_y;

    for (int i=0; i<y.size(); i++)
        new_y.add(y[i] + add_val);

    Function new_func(x, new_y);
    return new_func;
}

Function Function::operator - (CalcType sub_val)
{
    Vector new_y;

    for (int i=0; i<y.size(); i++)
        new_y.add(y[i] - sub_val);

    Function new_func(x, new_y);
    return new_func;
}

Function Function::operator - ()
{
    Vector new_y;

    for (int i=0; i<y.size(); i++)
        new_y.add(-1 * y[i]);

    Function new_func(x, new_y);
    return new_func;
}

Function Function::operator * (CalcType com_val)
{
    Vector new_y;

    for (int i=0; i<y.size(); i++)
        new_y.add(y[i] * com_val);

    Function new_func(x, new_y);
    return new_func;
}

Function Function::operator / (CalcType div_val)
{
    Vector new_y;

    for (int i=0; i<y.size(); i++)
        new_y.add(y[i] / div_val);

    Function new_func(x, new_y);
    return new_func;
}

friend ostream& Function::operator << (ostream& out, Function &f)
{
    for(int i=0; i<f.size(); i++)
        out << "X: " << f.x[i] << "   Y: " << f.y[i] << '\n';
    return out;
}


//_________________VECTOR OF FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE________________
VectorOfFunction::VectorOfFunction(int size)
{
    vecoffunc.resize(size);
}

int VectorOfFunction::size()
{
    return vecoffunc.size();
}

Function& VectorOfFunction::operator () (const int index)
{
    return vecoffunc.at(index);
}


//_____________SQUARE MATRIX OF FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE_____________
MatrixOfFunction::MatrixOfFunction(int size)
{
    matOfFunc.resize(size);
    for (int i=0; i<size; i++)
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


//__________________________________________________CONVERTION FUNCTIONS__________________________________________________
Vector MatrixToVector(Matrix mat, bool symmetric)
{
    Vector result;
    if (symmetric)
    {
        for (int i=0; i<mat.size(); i++)
        {
            for (int j=i; j<mat.size(); j++)
            {
                result.add(mat[i][j]);
            }
        }
    }
    else
    {
        for (int i=0; i<mat.size(); i++)
        {
            for (int j=0; j<mat.size(); j++)
            {
                result.add(mat[i][j]);
            }
        }
    }
return result;
}

Vector MatrixOfMatrixToVector(MatrixOfMatrix matOfMat, bool symmetric)
{
    Vector result;
    if (symmetric)
    {
        for (int i=0; i<matOfMat.size(); i++)
        {
            for (int j=0; j<matOfMat.size(); j++)
            {
                for (int k=0; k<matOfMat(i, j).size(); k++)
                {
                    for (int l=k; l<matOfMat(i, j).size(); l++)
                    {
                        result.add(matOfMat(i, j)[k][l]);
                    }
                }
            }
        }
    }
    else
    {
        for (int i=0; i<matOfMat.size(); i++)
        {
            for (int j=0; j<matOfMat.size(); j++)
            {
                for (int k=0; k<matOfMat(i, j).size(); k++)
                {
                    for (int l=0; l<matOfMat(i, j).size(); l++)
                    {
                        result.add(matOfMat(i, j)[k][l]);
                    }
                }
            }
        }
    }
    return result;
}

Matrix VectorToMatrix(Vector vec, int matSize, bool symmetric)
{
    int totalSize = matSize * matSize;
    if (symmetric)
    {
        for (int i=1; i<matSize; i++)
        {
            totalSize -= i;
        }
    }
    assert (vec.size() == totalSize);

    Matrix result(matSize);
    int index = 0;
    if (symmetric)
    {
        for (int i=0; i<result.size(); i++)
        {
            for (int j=i; j<result.size(); j++)
            {
                result[i][j] = vec[index];
                result[j][i] = vec[index];
                index++;
            }
        }
    }
    else
    {
        for (int i=0; i<result.size(); i++)
        {
            for (int j=0; j<result.size(); j++)
            {
                result[i][j] = vec[index];
                index++;
            }
        }
    }
    return result;
}

MatrixOfMatrix VectorToMatrixOfMatrix(
    Vector vec, 
    int matOfMatSize, 
    int matSize, 
    bool IsSymmetric
) {
    int totalSize = matSize * matSize;
    if (symmetric)
    {
        for (int i=1; i<matSize; i++)
        {
            totalSize -= i;
        }
    }
    totalSize *= matOfMatSize * matOfMatSize;
    assert (vec.size() == totalSize);

    MatrixOfMatrix result(matOfMatSize);
    Matrix mat(matSize);
    int index = 0;
    if (symmetric)
    {
        for (int i=0; i<result.size(); i++)
        {
            for (int j=0; j<result.size(); j++)
            {
                for (int k=0; k<mat.size(); k++)
                {
                    for (int l=k; l<mat.size(); l++)
                    {
                        mat[k][l] = vec[index];
                        mat[l][k] = vec[index];
                        index++;
                    }
                }
                result(i, j) = mat;
            }
        }
    }
    else
    {
        for (int i=0; i<result.size(); i++)
        {
            for (int j=0; j<result.size(); j++)
            {
                for (int k=0; k<mat.size(); k++)
                {
                    for (int l=0; l<mat.size(); l++)
                    {
                        mat[k][l] = vec[index];
                        index++;
                    }
                }
                result(i, j) = mat;
            }
        }
    }
    return result;
}

MatrixOfFunction VectorToMatrixOfFunction(
    Vector xVec, 
    Vector yVec, 
    int matOfFuncSize
) {
    assert (yVec.size() == matOfFuncSize * matOfFuncSize * xVec.size());
    MatrixOfFunction result(matOfFuncSize);
    int index = 0;

    for (int i=0; i<result.size(); i++)
    {
        for (int j=0; j<result.size(); j++)
        {
            Vector yVals;

            for (int k=0; k<xVec.size(); k++)
            {
                yVals.add(yVec[index]);
                index++;
            }
            Function new_func(xVec, yVals);
            result(i, j) = new_func;
        }
    }
    return result;
    }

    bool IsSymmetric(Matrix mat)
    {
    for (int i=0; i<mat.size(); i++)
    {
        for (int j=i; j<mat.size(); j++)
        {
            if (mat[i][j] != mat[j][i])
            {
                return false;
            }
        }
    }
    return true;
}


//________________________________________________TIME FROM CLOCK_T_________________________________________________
Time::Time(clock_t time)
{
    int seconds = (int) time / CLOCKS_PER_SEC;
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;

    strSeconds = seconds / 10 == 0 ? "0" + to_string(abs(seconds)) : to_string(abs(seconds));
    strMinutes = minutes / 10 == 0 ? "0" + to_string(abs(minutes)) : to_string(abs(minutes));
    strHours = to_string(abs(hours));
}

friend ostream& Time::operator << (ostream& out, const Time &t)
{
    out << t.strHours << ':' << t.strMinutes << ':' << t.strSeconds;
    return out;
}