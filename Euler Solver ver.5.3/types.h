/**********************************************************************************************
**                                      TYPES HEADER FILE                                    **
**  This file contains classes for mathematical data structures used in Solver.cpp program.  **
**********************************************************************************************/

#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <cassert>

#define EPSILON 1e-08

template<typename T> int sgn(T val) 
{ 
    return (T(0) < val) - (val < T(0)); 
}

//___________________________________MAIN CALCULATION TYPE_____________________________________
using CalcType = double;


//_________________________________VECTOR OF CALCULATION TYPE__________________________________
class Vector
{
    std::vector<CalcType> vec;

public:
    Vector(std::vector<CalcType> stlVec)
    {
        vec.assign(stlVec.begin(), stlVec.end());
    }

    Vector(const int size = 0) 
    {
        vec.resize(size); 
    }

    Vector(const int size, CalcType val)
    {
        vec.reserve(size);
        for (int i=0; i<size; i++)
        {
            vec.push_back(val);
        }
    }

    //....................Returns the original vector (required for drawing plots)
    std::vector<CalcType> get_vector()
    { 
        return vec; 
    }

    //....................Vector indexing operator
    CalcType& operator [] (const int index) 
    { 
        return vec.at(index); 
    }

    //....................Returns true if vector is empty
    bool empty() 
    { 
        return vec.empty(); 
    }

    //....................Returns Vector's size
    int size() 
    { 
        return vec.size(); 
    }

    //....................Modifies Vector's size
    void resize(int newSize) 
    { 
        vec.resize(newSize); 
    }

    //....................Clears Vector
    void clear() 
    { 
        vec.clear(); 
    }
    
    //....................Sorts Vector
    void sort() 
    { 
        std::sort(vec.begin(), vec.end()); 
    }

    //....................Adds an item to the back of Vector
    void add(CalcType newItem)
    { 
        vec.push_back(newItem); 
    }

    //....................Adds a Vector to the back of Vector
    void add(Vector newVec)
    {
        std::vector<CalcType> newVecStl = newVec.get_vector();
        vec.insert(vec.end(), newVecStl.begin(), newVecStl.end());
    }

    //....................Adds a unique item to the back of Vector. Returns true if the item was added
    bool add_unique(CalcType newItem)
    {
        std::vector<CalcType>::iterator it = std::find(vec.begin(), vec.end(), newItem);
        if (it == vec.end())
        {
            vec.push_back(newItem);
            return true;
        }
        return false;
    }
    
    //....................Returns first element of Vector
    CalcType first() 
    { 
        return vec.at(0); 
    }

    //....................Returns last element of Vector
    CalcType last() 
    { 
        return vec.at(vec.size() - 1); 
    }

    //....................Returns first n elements of Vector
    Vector head(int n)                  
    {
        std::vector<CalcType> vecHead(vec.begin(), vec.begin() + n);
        return Vector(vecHead); 
    }

    //....................Returns last n elements of Vector
    Vector tail(int n)
    {
        std::vector<CalcType> vecTail(vec.end() - n, vec.end());
        return Vector(vecTail);
    }

    //....................Erases first n elements of Vector
    void erase_first(int n)
    {
        for (int i=0; i<n; i++)
        {
            vec.erase(vec.begin());
        }
    }

    //....................Returns vector element of the lowest value
    CalcType min_value()
    {
        return *min_element(vec.begin(), vec.end()); 
    }

    //....................Returns vector element of the highest value
    CalcType max_value() 
    { 
        return *max_element(vec.begin(), vec.end()); 
    }

    //....................Returns a sum of vector elements
    CalcType sum() 
    { 
        return std::accumulate(vec.begin(), vec.end(), 0.00000000); 
    }
    
    //....................Returns an average value of vector elements
    CalcType avg_value() 
    { 
        return vec.empty() ? 0 : std::accumulate(vec.begin(), vec.end(), 0.00000000) / vec.size(); 
    }

    //....................Sets a linearly spaced Vector
    static Vector setLinSpaced(CalcType size, CalcType minVal, CalcType maxVal)
    {
        Vector result(size);
        CalcType step = (maxVal - minVal) / (size - 1);
        for (int i=0; i<size-1; i++)
        {
            result[i] = minVal + i * step;
        }
        result[size - 1] = maxVal;
        return result;
    }

    //....................Natural logarithm of vector elements
    static Vector log(Vector arg)
    {
        std::vector<CalcType> argVec = arg.get_vector();
        std::vector<CalcType> logVec = argVec;
        std::transform(argVec.begin(), argVec.end(), logVec.begin(), [](CalcType a) {
            return std::log(a);
        });
        return Vector(logVec);
    }

    //....................Absolute values of vector elements
    static Vector abs(Vector arg)
    {
        std::vector<CalcType> argVec = arg.get_vector();
        std::vector<CalcType> absVec = argVec;
        std::transform(argVec.begin(), argVec.end(), absVec.begin(), [](CalcType a) {
            return std::abs(a);
        });
        return Vector(absVec);
    }

    //....................Vector + calculation type value
    Vector operator + (CalcType addVal)
    {
        std::vector<CalcType> sum = vec;
        std::transform(vec.begin(), vec.end(), sum.begin(), [addVal](CalcType a){
            return a + addVal;
        });
        return Vector(sum);
    }

    //....................Vector - calculation type value
    Vector operator - (CalcType subVal)
    {
        std::vector<CalcType> sub = vec;
        std::transform(vec.begin(), vec.end(), sub.begin(), [subVal](CalcType a){
            return a - subVal;
        });
        return Vector(sub);
    }
    
    //....................-Vector
    Vector operator - ()
    {
        std::vector<CalcType> negativeVec = vec;
        std::transform(vec.begin(), vec.end(), negativeVec.begin(), [](CalcType a){
            return a * -1;
        });
        return Vector(negativeVec);
    }

    //....................Vector * calculation type value
    Vector operator * (CalcType comVal)
    {
        std::vector<CalcType> product = vec;
        std::transform(vec.begin(), vec.end(), product.begin(), [comVal](CalcType a){
            return a * comVal;
        });
        return Vector(product);
    }

    //....................Vector / calculation type value
    Vector operator / (CalcType divVal)
    {
        std::vector<CalcType> quotient = vec;
        std::transform(vec.begin(), vec.end(), quotient.begin(), [divVal](CalcType a){
            return a / divVal;
        });
        return quotient;
    }

    //....................Vector + Vector
    Vector operator + (Vector addVec)
    {
        int maxSize = std::max((int) vec.size(), (int) addVec.size());
        Vector sum(vec);
        sum.resize(maxSize);
        addVec.resize(maxSize);
        for (int i=0; i<maxSize; i++)
        {
            sum[i] += addVec[i];
        }
        return sum;
    }

    //....................Vector - Vector
    Vector operator - (Vector subVec)
    {
        int maxSize = std::max((int) vec.size(), (int) subVec.size());
        Vector sub(vec);
        sub.resize(maxSize);
        subVec.resize(maxSize);
        for (int i=0; i<maxSize; i++)
        {
            sub[i] -= subVec[i];
        }
        return sub;
    }

    //....................Vector * Vector
    Vector operator * (Vector comVec)
    {
        int maxSize = std::max((int) vec.size(), (int) comVec.size());
        Vector product(vec);
        product.resize(maxSize);
        comVec.resize(maxSize);
        for (int i=0; i<maxSize; i++)
        {
            product[i] *= comVec[i];
        }
        return product;
    }

    //....................Vector / Vector
    Vector operator / (Vector divVec)
    {
        int maxSize = std::max((int) vec.size(), (int) divVec.size());
        Vector quotient(vec);
        quotient.resize(maxSize);
        divVec.resize(maxSize);
        for (int i=0; i<maxSize; i++)
        {
            quotient[i] /= divVec[i];
        }
        return quotient;
    }

    std::vector<CalcType>::iterator begin()
    { 
        return vec.begin(); 
    }

    std::vector<CalcType>::iterator end() 
    { 
        return vec.end(); 
    }

    friend std::ostream& operator << (std::ostream& out, const Vector &v)
	{
		out << v.vec.at(0);
		for(int i=1; i<v.vec.size(); i++)
        {
			out << ", " << v.vec.at(i);
        }
        out << '\n';
		return out;
	}

    std::pair<int, CalcType> MaxStep()
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
        return std::make_pair(maxStepIndex, maxStep);
    }
};


//______________________________SQUARE MATRIX OF CALCULATION TYPE_____________________________
class Matrix
{
    std::vector<Vector> mat;

public:
    Matrix(const int size = 0)
    { 
        resize(size); 
    }

    Matrix(const int size, CalcType val)
    {
        mat.reserve(size);
        for (int i=0; i<size; i++)
        {
            mat.push_back(Vector(size, val));
        }
    }

    Vector& operator [] (const int rowNum)
    { 
        return mat.at(rowNum); 
    }

    int size()
    { 
        return mat.size(); 
    }

    void resize(const int newSize)
    {
        mat.resize(newSize);
        for (auto &col : mat)
        {
            col.resize(newSize);
        }
    }

    void resize(const int r, const int c)
    {
        mat.resize(r);
        for (int i=0; i<r; i++)
        {
            mat[i].resize(c);
        }
    }

    Vector Row(const int rowNum) 
    { 
        return mat.at(rowNum); 
    }

    Vector Col(const int colNum)
    {
        Vector col(mat.size());
        for (int i=0; i<mat.size(); i++)
        {
            col[i] = mat.at(i)[colNum];
        }
        return col;
    }

    //....................Returns an element of Matrix which has the lowest value
    CalcType min_value()
    {
        std::vector<CalcType> minVals;
        minVals.reserve(mat.size());
        for (int i=0; i<mat.size(); i++)
        {
            minVals.push_back(mat.at(i).min_value());
        }
        return *min_element(minVals.begin(), minVals.end());
    }

    //....................Returns an element of Matrix which has the highest value
    CalcType max_value()
    {
        std::vector<CalcType> maxVals;
        maxVals.reserve(mat.size());
        for (int i=0; i<mat.size(); i++)
        {
            maxVals.push_back(mat.at(i).max_value());
        }
        return *max_element(maxVals.begin(), maxVals.end());
    }

    //....................Matrix + calculation type value
    Matrix operator + (CalcType addVal)
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

    //....................Matrix - calculation type value
    Matrix operator - (CalcType subVal)
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
    
    //....................-Matrix
    Matrix operator - ()
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

    //....................Matrix * calculation type value
    Matrix operator * (CalcType comVal)
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

    //....................Matrix / calculation type value
    Matrix operator / (CalcType divVal)
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

    friend std::ostream& operator << (std::ostream& out, const Matrix &m)
	{
        for (int i=0; i<m.mat.size(); i++)
        {
            out << m.mat.at(i);
        }
        return out;
	}
};


//____________________________VECTOR OF MATRIX OF CALCULATION TYPE_____________________________
class VectorOfMatrix
{
    std::vector<Matrix> vecOfMat;

public:
    VectorOfMatrix(const int size = 0)
    { 
        vecOfMat.resize(size);
    }

    //....................Returns the size of Vector of Matrix
    int size()
    { 
        return vecOfMat.size(); 
    }

    //....................Vector of Matrix indexing operator
    Matrix& operator () (const int index)
    { 
        return vecOfMat.at(index); 
    }
};


//____________________________MATRIX OF MATRIX OF CALCULATION TYPE_____________________________
class MatrixOfMatrix
{
    std::vector<std::vector<Matrix>> matOfMat;

public:
    MatrixOfMatrix(const int size = 0)
    {
        matOfMat.resize(size);
        for (int i=0; i<size; i++)
        {
            matOfMat.at(i).resize(size);
        }
    }

    //....................Returns numbers of rows & columns in Matrix of Matrix
    int size() 
    { 
        return matOfMat.size(); 
    }

    //....................Matrix of Matrix indexing operator
    Matrix& operator () (const int rowIndex, const int colIndex) 
    { 
        return matOfMat.at(rowIndex).at(colIndex); 
    }
};


//______________________FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE_____________________
class Function
{
    Vector x;
    Vector y;

public:
    Function(const int size = 0)
    {
        x.resize(size);
        y.resize(size);
    }

    Function(Vector xGrid, Vector yVals) : x(xGrid), y(yVals) {}

    Function(Vector xGrid, Matrix yVals)
    {
        std::map<CalcType, CalcType> XY;
        for (int i=0; i<xGrid.size(); i++)
        {
            for (int j=i; j<xGrid.size(); j++)
            {
                assert (std::abs(yVals[i][j] - yVals[j][i]) < EPSILON);
                CalcType xHypot = std::hypot(xGrid[i], xGrid[j]);
                XY.insert({ xHypot, yVals[i][j] });
            }
        }
        for (auto coord : XY)
        {
            x.add(coord.first);
            y.add(coord.second);
        }
    }

    Function(Vector xGrid, Matrix yVals, CalcType xMax)
    {
        std::map<CalcType, CalcType> XY;
        for (int i=0; i<xGrid.size(); i++)
        {
            for (int j=i; j<xGrid.size(); j++)
            {
                assert (std::abs(yVals[i][j] - yVals[j][i]) < EPSILON);
                CalcType xHypot = std::hypot(xGrid[i], xGrid[j]);
                XY.insert({ xHypot, yVals[i][j] });
            }
        }
        
        std::map<CalcType, CalcType>::iterator it = XY.begin();
        while (it != XY.end() && it->first <= xMax)
        {
            x.add(it->first);
            y.add(it->second);
        }
    }

    int size()
    { 
        return x.size(); 
    }

    Vector X() 
    { 
        return x; 
    }

    Vector Y() 
    { 
        return y; 
    }

    static Function trim(Function func, CalcType xFinal)
    {
        auto xVals = func.X().get_vector();
        auto it = std::find(xVals.begin(), xVals.end(), xFinal);
        assert (it != xVals.end());
        int finalIndex = std::distance(xVals.begin(), it);
        
        Vector xValsTrimmed;
        Vector yValsTrimmed;
        for (int i=0; i<=finalIndex; i++)
        {
            xValsTrimmed.add(func.X()[i]);
            yValsTrimmed.add(func.Y()[i]);
        }
        return Function(xValsTrimmed, yValsTrimmed);
    }

    CalcType findY(CalcType xVal)
    {
        assert ((xVal >= x[0]) && (xVal <= x.last()));
        
        std::vector<CalcType> xStl = x.get_vector();
        std::vector<CalcType>::iterator it = std::find(xStl.begin(), xStl.end(), xVal);
        assert (it != xStl.end());
        
        int index = std::distance(xStl.begin(), it);
        return y[index];
    }

    std::pair<bool, CalcType> ConstantSign()
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
        return std::make_pair(isConstant, val);
    }

    CalcType Interpolate(CalcType xVal)
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

    CalcType Interpolate(CalcType xVal, CalcType asymptoticVal)
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

    CalcType IntegralRectangles()
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

    //....................All Y values + calculation type value
    Function operator + (CalcType add_val)
    {
        Vector new_y;

        for (int i=0; i<y.size(); i++)
            new_y.add(y[i] + add_val);

        Function new_func(x, new_y);
        return new_func;
    }

    //....................Vector - calculation type value
    Function operator - (CalcType sub_val)
    {
        Vector new_y;

        for (int i=0; i<y.size(); i++)
            new_y.add(y[i] - sub_val);

        Function new_func(x, new_y);
        return new_func;
    }
    
    //....................-Vector
    Function operator - ()
    {
        Vector new_y;

        for (int i=0; i<y.size(); i++)
            new_y.add(-1 * y[i]);

        Function new_func(x, new_y);
        return new_func;
    }

    //....................Vector * calculation type value
    Function operator * (CalcType com_val)
    {
        Vector new_y;

        for (int i=0; i<y.size(); i++)
            new_y.add(y[i] * com_val);

        Function new_func(x, new_y);
        return new_func;
    }

    //....................Vector / calculation type value
    Function operator / (CalcType div_val)
    {
        Vector new_y;

        for (int i=0; i<y.size(); i++)
            new_y.add(y[i] / div_val);

        Function new_func(x, new_y);
        return new_func;
    }

    friend std::ostream& operator << (std::ostream& out, Function &f)
	{
		for(int i=0; i<f.size(); i++)
			out << "X: " << f.x[i] << "   Y: " << f.y[i] << '\n';
		return out;
	}
};


//_________________VECTOR OF FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE________________
class VectorOfFunction
{
    std::vector<Function> vecoffunc;

public:
    VectorOfFunction(int size=0) { vecoffunc.resize(size); }

    //....................Returns the size of Vector of Function
    int size() { return vecoffunc.size(); }

    //....................Vector of Matrix indexing operator
    Function& operator () (const int index) { return vecoffunc.at(index); }
};


//_____________SQUARE MATRIX OF FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE_____________
class MatrixOfFunction
{
    std::vector<std::vector<Function>> matOfFunc;

public:
    MatrixOfFunction(int size = 0)
    {
        matOfFunc.resize(size);
        for (int i=0; i<size; i++)
        {
            matOfFunc.at(i).resize(size);
        }
    }

    //....................Returns numbers of rows & columns in Matrix of Function
    int size() 
    { 
        return matOfFunc.size(); 
    }

    //....................Matrix of Matrix indexing operator
    Function& operator () (int rowIndex, int colIndex) 
    { 
        return matOfFunc.at(rowIndex).at(colIndex); 
    }
};


//__________________________________________________CONVERTION FUNCTIONS__________________________________________________
Vector MatrixToVector(Matrix mat, bool symmetric=false)
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

Vector MatrixOfMatrixToVector(MatrixOfMatrix matOfMat, bool symmetric=false)
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

Matrix VectorToMatrix(Vector vec, int matSize, bool symmetric=false)
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

MatrixOfMatrix VectorToMatrixOfMatrix(Vector vec, int matOfMatSize, int matSize, bool symmetric=false)
{
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

MatrixOfFunction VectorToMatrixOfFunction(Vector xVec, Vector yVec, int matOfFuncSize)
{
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
class Time
{
    std::string strSeconds;
    std::string strMinutes;
    std::string strHours;

public:
    Time(clock_t time)
    {
        int seconds = (int) time / CLOCKS_PER_SEC;
        int hours = seconds / 3600;
        int minutes = (seconds % 3600) / 60;
        seconds = seconds % 60;

        strSeconds = seconds / 10 == 0 ? "0" + std::to_string(std::abs(seconds)) : std::to_string(std::abs(seconds));
        strMinutes = minutes / 10 == 0 ? "0" + std::to_string(std::abs(minutes)) : std::to_string(std::abs(minutes));
        strHours = std::to_string(std::abs(hours));
    }

    friend std::ostream& operator << (std::ostream& out, const Time &t)
	{
        out << t.strHours << ':' << t.strMinutes << ':' << t.strSeconds;
		return out;
	}
};