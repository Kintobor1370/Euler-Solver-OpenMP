#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cassert>
#include "Vector.hpp"

using namespace std;


// Assert if Vector is equal to its vector<CalcType> counterpart
void AssertVectorEqual(
    Vector& actual,
    const vector<CalcType>& expected
) {
    assert(actual.size() == expected.size());
    for (int i = 0; i < expected.size(); i++)
    {
        assert(actual[i] == expected.at(i));
    }
}

// TEST CONSTRUCTORS
// Constructor from STL vector
void TestConstructorFromSTLVector()
{
    vector<CalcType> STLVec { 1, 2, 3, 4, 5 };
    Vector Vec(STLVec);
    AssertVectorEqual(Vec, STLVec);
}

// Constructor from size
void TestConstructorFromSize()
{
    int size = 5;
    vector<CalcType> STLVec(size, 0.0);
    Vector Vec(size);
    AssertVectorEqual(Vec, STLVec);
}

// Constructor from size and value
void TestConstructorFromSizeAndValue()
{
    int size = 5;
    int value = 3.14;
    vector<CalcType> STLVec(size, value);
    Vector Vec(size, value);
    AssertVectorEqual(Vec, STLVec);
}

// TEST BASIC OPERATORS
void TestIndexing()
{
    Vector vec({ 0, 1, 2 });
    for (int i = 0; i < vec.size(); i++)
    {
        assert(vec[i] == i);
    }
    vec[1] = 5;
    assert(vec[1] == 5);
}

void TestSize()
{
    Vector vec(3);
    assert(vec.size() == 3);
    
    vec.add(0);
    assert(vec.size() == 4);
    
    vec.clear();
    assert(vec.size() == 0);
}

void TestEmpty()
{
    Vector vec;
    
    // Assert that the Vector is empty
    assert(vec.empty());
    assert(vec.size() == 0);
    
    // Assert that the Vector is not empty
    vec.add(1);
    assert(!vec.empty());
    assert(vec.size() != 0);
}

void TestGetVector()
{
    vector<CalcType> STLVec { 1, 2, 3 };
    Vector vec(STLVec);
    assert(vec.get_vector() == STLVec);
}

void TestResize()
{
    Vector vec({ 0, 1, 2, 3, 4 });
    vec.resize(10);
    AssertVectorEqual(
        vec,
        { 0, 1, 2, 3, 4, 0, 0, 0, 0, 0 }
    );
    vec.resize(3);
    AssertVectorEqual(
        vec,
        { 0, 1, 2 }
    );
}

void TestClear()
{
    Vector vec(5, 1);
    AssertVectorEqual(
        vec,
        { 1, 1, 1, 1, 1 }
    );
    vec.clear();
    assert(vec.empty());
}

// TEST ADD OPERATIONS
void TestAddValue()
{
    Vector vec({ 1, 2, 3 });
    vec.add(4);
    AssertVectorEqual(
        vec,
        { 1, 2, 3, 4 }
    );
}

void TestAddVector()
{
    Vector vec({ 1, 2, 3 });
    Vector addVec({ 4, 5, 6 });
    vec.add(addVec);
    AssertVectorEqual(
        vec,
        { 1, 2, 3, 4, 5, 6 }
    );
}

void TestAddUnique()
{
    Vector vec({ 1, 2, 3 });
    
    // Add unique value
    bool addedUnique = vec.add_unique(4);

    // Add duplicate value
    bool addedDuplicate = vec.add_unique(2);

    assert(addedUnique);
    assert(!addedDuplicate);
    AssertVectorEqual(
        vec,
        { 1, 2, 3, 4 }
    );
}

// TEST SORTING
void TestSort()
{
    Vector vec({ 1, 4, 0, 3, 2 });
    vec.sort();
    AssertVectorEqual(
        vec, 
        { 0, 1, 2, 3, 4 }
    );
}

// TEST ERASE
void TestEraseFirst()
{
    Vector vec({ 0, 1, 2, 3, 4 });
    
    // Erase less than size of Vector
    vec.erase_first(2);
    AssertVectorEqual(vec, { 2, 3, 4 });

    // Erase more than size of Vector
    vec.erase_first(vec.size() + 1);
    assert(vec.empty());
}

// TEST FIRST / LAST / HEAD / TAIL
void TestFirst()
{
    Vector vec({ 0, 1, 2 });
    assert(vec.first() == 0);

    vec.erase_first(1);
    assert(vec.first() == 1);
}

void TestLast()
{
    Vector vec({ 0, 1, 2 });
    assert(vec.last() == 2);

    vec.add(3);
    assert(vec.last() == 3);
}

void TestHead()
{
    Vector vec({ 0, 1, 2, 3, 4 });

    // Head size is less than original Vector size
    Vector vecHead1 = vec.head(3);
    AssertVectorEqual(vecHead1, { 0, 1, 2 });

    // Head size is bigger than original Vector size
    Vector vecHead2 = vec.head(vec.size() + 1);
    AssertVectorEqual(vecHead2, vec.get_vector());
}

void TestTail()
{
    Vector vec({ 0, 1, 2, 3, 4 });

    // Tail size is less than original Vector size
    Vector vecTail1 = vec.tail(3);
    AssertVectorEqual(vecTail1, { 2, 3, 4 });

    // Tail size is bigger than original Vector size
    Vector vecTail2 = vec.tail(vec.size() + 1);
    AssertVectorEqual(vecTail2, vec.get_vector());
}

// TEST MIN / MAX
void TestMinValue()
{
    Vector vec({ 1, 4, -2, 0, 3, -1, 2 });
    assert(vec.min_value() == -2);
}

void TestMaxValue()
{
    Vector vec({ 1, 4, -2, 0, 3, -1, 2 });
    assert(vec.max_value() == 4);
}

// TEST SUM
void TestSum()
{
    Vector vec({ 1, 2, 3, 4 });
    assert(vec.sum() == 10);
}

// TEST AVERAGE VALUE
void TestAvgValue()
{
    Vector vec({ 1, 2, 3, 4 });
    cout << vec.sum() / vec.size() << "  " << vec.avg_value() << "\n";
    assert(vec.avg_value() == 2.5);
}

// TEST LINEARLY SPACED VECTOR
void TestSetLinSpaced()
{
    Vector vec = Vector::setLinSpaced(5, 0, 10);
    AssertVectorEqual(
        vec,
        { 0, 2.5, 5, 7.5, 10 }
    );
}

// TEST MATHEMATICAL FUNCTIONS
void TestLog()
{
    Vector vec({ 0, exp(1), exp(2), exp(3), exp(4) });
    Vector logVec = Vector::log(vec);
    AssertVectorEqual(
        logVec,
        { 0, 1, 2, 3, 4 }
    );
}

void TestAbs()
{
    Vector vec({ -4, -3, -2, -1, 0, 1, 2, 3, 4 });
    Vector absVec = Vector::abs(vec);
    AssertVectorEqual(
        absVec,
        { 4, 3, 2, 1, 0, 1, 2, 3, 4 }
    );
}

// TEST SCALAR ARITHMETIC
void TestArithmeticsScalar(
    vector<CalcType> &vec,
    CalcType val
) {
    
    Vector testMathVecObj(vec);

    // vec + val
    Vector testMathVecObjSum = testMathVecObj + val;
    for (int i = 0; i < testMathVecObjSum.size(); i++)
    {
        assert(testMathVecObjSum[i] == vec.at(i) + val);
    }

    // vec - val
    Vector testMathVecObjSub = testMathVecObj - val;
    for (int i = 0; i < testMathVecObjSub.size(); i++)
    {
        assert(testMathVecObjSub[i] == vec.at(i) - val);
    }

    // vec * val
    Vector testMathVecObjProd = testMathVecObj * val;
    for (int i = 0; i < testMathVecObjProd.size(); i++)
    {
        assert(testMathVecObjProd[i] == vec.at(i) * val);
    }

    // vec / val
    Vector testMathVecObjQuot = testMathVecObj / val;
    for (int i = 0; i < testMathVecObjQuot.size(); i++)
    {
        assert(testMathVecObjQuot[i] == vec.at(i) / val);
    }
}

void TestArithmeticsVector(
    vector<CalcType> &a,
    vector<CalcType> &b
) {
    int diff = abs((int) (a.size() - b.size()));
    if (diff != 0)
    {
        vector<CalcType> zeros(diff, 0);
        if (a.size() > b.size())
        {
            b.insert(b.end(), zeros.begin(), zeros.end());
        }
        else
        {
            a.insert(a.end(), zeros.begin(), zeros.end());
        }
    }

    Vector testMathVecObjA(a);
    Vector testMathVecObjB(b);

    // a + b
    Vector testMathVecObjSum = testMathVecObjA + testMathVecObjB;
    for (int i = 0; i < testMathVecObjSum.size(); i++)
    {
        assert(testMathVecObjSum[i] == a.at(i) + b.at(i));
    }

    // a - b
    Vector testMathVecObjSub = testMathVecObjA - testMathVecObjB;
    for (int i = 0; i < testMathVecObjSub.size(); i++)
    {
        assert(testMathVecObjSub[i] == a.at(i) - b.at(i));
    }

    // -a
    Vector testMathVecObjNeg = -testMathVecObjA;
    for (int i = 0; i < testMathVecObjNeg.size(); i++)
    {
        assert(testMathVecObjNeg[i] == -1 * a.at(i));
    }

    // a * b
    Vector testMathVecObjProd = testMathVecObjA * testMathVecObjB;
    for (int i = 0; i < testMathVecObjProd.size(); i++)
    {
        assert(testMathVecObjProd[i] == a.at(i) * b.at(i));
    }

    // a / b
    Vector testMathVecObjQuot = testMathVecObjA / testMathVecObjB;
    for (int i = 0; i < testMathVecObjQuot.size(); i++)
    {
        assert(testMathVecObjQuot[i] == a.at(i) / b.at(i));
    }
}


int main()
{
    TestConstructorFromSTLVector();
    TestConstructorFromSize();
    TestConstructorFromSizeAndValue();

    TestIndexing();
    TestSize();
    TestEmpty();
    TestGetVector();
    TestResize();
    TestClear();

    TestAddValue();
    TestAddVector();
    TestAddUnique();

    TestSort();

    TestEraseFirst();

    TestFirst();
    TestLast();
    TestHead();
    TestTail();

    TestMinValue();
    TestMaxValue();

    TestSum();
    
    TestAvgValue();
    
    TestSetLinSpaced();
    
    TestLog();
    
    TestAbs();

    // Test Vector arithmetics:
    // Scalar operations
    vector<CalcType> testMathVecA {
        12, 5, -1, 4, -6, 1, 59, -25, 72, 8
    };
    CalcType val = 5;
    TestArithmeticsScalar(testMathVecA, val);

    // Vector operations
    vector<CalcType> testMathVecB {
        -6, 1, 82, 5, -74, -6, 85, 0, -1, -47
    };
    TestArithmeticsVector(testMathVecA, testMathVecB);

    // Test for Vectors with different sizes
    vector<CalcType> testMathVecDiffSize {
        -6, 1, 82, 5, -74, -6
    };

    // First Vector is longer than second Vector
    TestArithmeticsVector(testMathVecA, testMathVecDiffSize);

    // First Vector is shorter than second Vector
    //TestMath(testMathVecDiffSize, testMathVecB);
    

    cout << "\n=========================ALL TESTS COMPLETE!=========================\n\n";
    return 0;
}