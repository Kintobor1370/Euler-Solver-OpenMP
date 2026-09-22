#pragma once 

#include <iosfwd>
#include <vector>

#define EPSILON 1e-08


//___________________________________MAIN CALCULATION TYPE_____________________________________
using CalcType = double;


//_________________________________VECTOR OF CALCULATION TYPE__________________________________
class Vector
{
    std::vector<CalcType> vec;

public:
    Vector();

    Vector(const std::vector<CalcType>& stlVec);

    Vector(const int size);

    Vector(const int size, const CalcType val);

    //....................Copy constructor
    Vector(const Vector& other);

    //....................Move constructor
    Vector(Vector&& other) noexcept;

    //....................Returns the original vector (required for drawing plots)
    std::vector<CalcType> get_vector();

    //....................Vector indexing operator
    CalcType& operator [] (const int index);

    //....................Returns true if vector is empty
    bool empty() const;

    //....................Returns Vector's size
    int size() const;

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

    Vector& operator = (const Vector& v);

    Vector& operator = (Vector&& v) noexcept;

    //....................Vector + calculation type value
    friend Vector operator + (Vector baseVec, CalcType addVal);

    //....................Vector - calculation type value
    friend Vector operator - (Vector baseVec, CalcType subVal);

    //....................Vector * calculation type value
    friend Vector operator * (Vector baseVec, CalcType comVal);

    //....................Vector / calculation type value
    friend Vector operator / (Vector baseVec, CalcType divVal);

    //....................-Vector
    Vector operator - ();

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

    std::pair<int, CalcType> MaxStep();

    //....................Display vector of calculation type values
    //....................Format: 
    //....................   x1, x2, ..., xn
    friend std::ostream& operator << (std::ostream& out, const Vector &v);
};