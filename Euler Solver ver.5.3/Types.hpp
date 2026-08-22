/**********************************************************************************************
**                                      TYPES HEADER FILE                                    **
**  This file contains classes for mathematical data structures used in Solver.cpp program.  **
**********************************************************************************************/

#include <iosfwd>
#include <string>
#include <vector>

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
    Vector(std::vector<CalcType> stlVec);

    Vector(const int size = 0);

    Vector(const int size, CalcType val);

    //....................Returns the original vector (required for drawing plots)
    std::vector<CalcType> get_vector();

    //....................Vector indexing operator
    CalcType& operator [] (const int index);

    //....................Returns true if vector is empty
    bool empty();

    //....................Returns Vector's size
    int size();

    //....................Modifies Vector's size
    void resize(int newSize);

    //....................Clears Vector
    void clear();
    
    //....................Sorts Vector
    void sort();

    //....................Adds an item to the back of Vector
    void add(CalcType newItem);

    //....................Adds a Vector to the back of Vector
    void add(Vector newVec);

    //....................Adds a unique item to the back of Vector. Returns true if the item was added
    bool add_unique(CalcType newItem);
    
    //....................Returns first element of Vector
    CalcType first();

    //....................Returns last element of Vector
    CalcType last();

    //....................Returns first n elements of Vector
    Vector head(int n);

    //....................Returns last n elements of Vector
    Vector tail(int n);
    
    //....................Erases first n elements of Vector
    void erase_first(int n);

    //....................Returns vector element of the lowest value
    CalcType min_value();

    //....................Returns vector element of the highest value
    CalcType max_value();

    //....................Returns a sum of vector elements
    CalcType sum();
    
    //....................Returns an average value of vector elements
    CalcType avg_value();

    //....................Sets a linearly spaced Vector
    static Vector setLinSpaced(
        CalcType size, 
        CalcType minVal, 
        CalcType maxVal
    );

    //....................Natural logarithm of vector elements
    static Vector log(Vector arg);

    //....................Absolute values of vector elements
    static Vector abs(Vector arg);

    //....................Vector + calculation type value
    Vector operator + (CalcType addVal);

    //....................Vector - calculation type value
    Vector operator - (CalcType subVal);
    
    //....................-Vector
    Vector operator - ();

    //....................Vector * calculation type value
    Vector operator * (CalcType comVal);

    //....................Vector / calculation type value
    Vector operator / (CalcType divVal);

    //....................Vector + Vector
    Vector operator + (Vector addVec);

    //....................Vector - Vector
    Vector operator - (Vector subVec);

    //....................Vector * Vector
    Vector operator * (Vector comVec);

    //....................Vector / Vector
    Vector operator / (Vector divVec);

    std::vector<CalcType>::iterator begin();

    std::vector<CalcType>::iterator end();

    friend std::ostream& operator << (std::ostream& out, const Vector &v);

    std::pair<int, CalcType> MaxStep();
};


//______________________________SQUARE MATRIX OF CALCULATION TYPE_____________________________
class Matrix
{
    std::vector<Vector> mat;

public:
    Matrix(const int size = 0);

    Matrix(const int size, CalcType val);

    Vector& operator [] (const int rowNum);

    int size();

    void resize(const int newSize);

    void resize(const int r, const int c);

    Vector Row(const int rowNum);

    Vector Col(const int colNum);

    //....................Returns an element of Matrix which has the lowest value
    CalcType min_value();

    //....................Returns an element of Matrix which has the highest value
    CalcType max_value();

    //....................Matrix + calculation type value
    Matrix operator + (CalcType addVal);

    //....................Matrix - calculation type value
    Matrix operator - (CalcType subVal);
    
    //....................-Matrix
    Matrix operator - ();

    //....................Matrix * calculation type value
    Matrix operator * (CalcType comVal);

    //....................Matrix / calculation type value
    Matrix operator / (CalcType divVal);

    friend std::ostream& operator << (std::ostream& out, const Matrix &m);
};


//____________________________VECTOR OF MATRIX OF CALCULATION TYPE_____________________________
class VectorOfMatrix
{
    std::vector<Matrix> vecOfMat;

public:
    VectorOfMatrix(const int size = 0);

    //....................Returns the size of Vector of Matrix
    int size();

    //....................Vector of Matrix indexing operator
    Matrix& operator () (const int index);
};


//____________________________MATRIX OF MATRIX OF CALCULATION TYPE_____________________________
class MatrixOfMatrix
{
    std::vector<std::vector<Matrix>> matOfMat;

public:
    MatrixOfMatrix(const int size = 0);

    //....................Returns numbers of rows & columns in Matrix of Matrix
    int size();

    //....................Matrix of Matrix indexing operator
    Matrix& operator () (const int rowIndex, const int colIndex);
};


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
    Function operator + (CalcType add_val);

    //....................Vector - calculation type value
    Function operator - (CalcType sub_val);
    
    //....................-Vector
    Function operator - ();

    //....................Vector * calculation type value
    Function operator * (CalcType com_val);

    //....................Vector / calculation type value
    Function operator / (CalcType div_val);

    friend std::ostream& operator << (std::ostream& out, Function &f);
};


//_________________VECTOR OF FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE________________
class VectorOfFunction
{
    std::vector<Function> vecoffunc;

public:
    VectorOfFunction(int size = 0);

    //....................Returns the size of Vector of Function
    int size();

    //....................Vector of Matrix indexing operator
    Function& operator ();
};


//_____________SQUARE MATRIX OF FUNCTION OF CALCULATION TYPE ON 1D, 2D OR 3D SPACE_____________
class MatrixOfFunction
{
    std::vector<std::vector<Function>> matOfFunc;

public:
    MatrixOfFunction(int size = 0);

    //....................Returns numbers of rows & columns in Matrix of Function
    int size();

    //....................Matrix of Matrix indexing operator
    Function& operator () (int rowIndex, int colIndex);
};


//__________________________________________________CONVERTION FUNCTIONS__________________________________________________
Vector MatrixToVector(Matrix mat, bool symmetric = false);

Vector MatrixOfMatrixToVector(MatrixOfMatrix matOfMat, bool symmetric = false);

Matrix VectorToMatrix(Vector vec, int matSize, bool symmetric = false);

MatrixOfMatrix VectorToMatrixOfMatrix(
    Vector vec, 
    int matOfMatSize, 
    int matSize, 
    bool symmetric = false
);

MatrixOfFunction VectorToMatrixOfFunction(
    Vector xVec, 
    Vector yVec, 
    int matOfFuncSize
)


//________________________________________________TIME FROM CLOCK_T_________________________________________________
class Time
{
    std::string strSeconds;
    std::string strMinutes;
    std::string strHours;

public:
    Time(clock_t time);

    friend std::ostream& operator << (std::ostream& out, const Time &t);
};