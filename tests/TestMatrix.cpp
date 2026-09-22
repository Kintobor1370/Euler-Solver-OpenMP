#include <iostream>
#include <cassert>
#include "Matrix.hpp"
#include "Conversion.hpp"

using namespace std;


// Assert if Vector object is equal to its vector<CalcType> counterpart
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

// Assert if Matrix object is equal to its vector<vector<CalcType>> counterpart
void AssertMatrixEqual(
    Matrix& actual,
    const vector<vector<CalcType>>& expected
) {
    assert(actual.size() == expected.size());
    for (int row = 0; row < expected.size(); row++)
    {
        assert(actual[row].size() == expected[row].size());
        for (int col = 0; col < expected[0].size(); col++)
        {
            assert(actual[row][col] == expected[row][col]);
        }
    }
}

// TEST CONSTRUCTOR
void TestConstructor()
{
    vector<vector<CalcType>> STLMat {
        { 5, 5, 5 },
        { 5, 5, 5 },
        { 5, 5, 5 }
    };
    Matrix Mat(3, 5);
    AssertMatrixEqual(Mat, STLMat);
}

// TEST BASIC OPERATORS
void TestIndexing()
{
    Matrix mat(3, 5);
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat.size(); j++)
        {
            assert(mat[i][j] == 5);
        }
    }
    mat[1][2] = 10;
    assert(mat[1][2] == 10);
}

void TestSize()
{
    Matrix mat(5);
    assert(mat.size() == 5);
}

void TestResize()
{
    Matrix mat(3, 5);
    mat.resize(6);
    AssertMatrixEqual(
        mat,
        { 
            { 5, 5, 5, 0, 0, 0 },
            { 5, 5, 5, 0, 0, 0 },
            { 5, 5, 5, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0 }
        }
    );
    mat.resize(2);
    AssertMatrixEqual(
        mat,
        { 
            { 5, 5 },
            { 5, 5 }
        }
    );
}

void TestResizeRowsAndCols()
{
    Matrix mat(3, 5);
    mat.resize(6, 3);
    AssertMatrixEqual(
        mat,
        { 
            { 5, 5, 5 },
            { 5, 5, 5 },
            { 5, 5, 5 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        }
    );
    mat.resize(6, 5);
    AssertMatrixEqual(
        mat,
        { 
            { 5, 5, 5, 0, 0 },
            { 5, 5, 5, 0, 0 },
            { 5, 5, 5, 0, 0 },
            { 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0 }
        }
    );
    mat.resize(3, 2);
    AssertMatrixEqual(
        mat,
        { 
            { 5, 5 },
            { 5, 5 },
            { 5, 5 }
        }
    );
}

// TEST ROWS AND COLUMNS OUTPUT
void TestRow()
{
    Vector matBase({
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20,
        21, 22, 23, 24, 25
    });
    Matrix mat = VectorToMatrix(matBase, 5);
    Vector row = mat.Row(2);
    AssertVectorEqual(
        row,
        { 11, 12, 13, 14, 15 }
    );
}

void TestCol()
{
    Vector matBase({
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20,
        21, 22, 23, 24, 25
    });
    Matrix mat = VectorToMatrix(matBase, 5);
    Vector column = mat.Col(3);
    AssertVectorEqual(
        column,
        { 4, 9, 14, 19, 24 }
    );
}

// TEST MIN / MAX VALUES
void TestMinValue()
{
    Vector matBase({
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20,
        21, 22, 23, 24, 25
    });
    Matrix mat = VectorToMatrix(matBase, 5);
    assert(mat.min_value() == 1);
}

void TestMaxValue()
{
    Vector matBase({
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20,
        21, 22, 23, 24, 25
    });
    Matrix mat = VectorToMatrix(matBase, 5);
    assert(mat.max_value() == 25);
}

// TEST SCALAR ARITHMETIC
void TestArithmeticsScalar() 
{
    Vector matBase({
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20,
        21, 22, 23, 24, 25
    });
    Matrix mat = VectorToMatrix(matBase, 5);
    CalcType arg = 2.54;

    // Add a CalcType value
    Matrix TestAddition = mat + arg;
    for (int i = 0; i < TestAddition.size(); i++)
    {
        for (int j = 0; j < TestAddition.size(); j++)
        {
            assert(TestAddition[i][j] == matBase[i * 5 + j] + arg);
        }
    }

    // Subtract a CalcType value
    Matrix TestSubtraction = mat - arg;
    for (int i = 0; i < TestSubtraction.size(); i++)
    {
        for (int j = 0; j < TestSubtraction.size(); j++)
        {
            assert(TestSubtraction[i][j] == matBase[i * 5 + j] - arg);
        }
    }

    // Turn Matrix values to negative
    Matrix TestNegative = -mat;
    for (int i = 0; i < TestNegative.size(); i++)
    {
        for (int j = 0; j < TestNegative.size(); j++)
        {
            assert(TestNegative[i][j] == -1 * matBase[i * 5 + j]);
        }
    }

    // Multiply by a CalcType value
    Matrix TestProduct = mat * arg;
    for (int i = 0; i < TestProduct.size(); i++)
    {
        for (int j = 0; j < TestProduct.size(); j++)
        {
            assert(TestProduct[i][j] == matBase[i * 5 + j] * arg);
        }
    }

    // Divide by a CalcType value
    Matrix TestQuotient = mat / arg;
    for (int i = 0; i < TestQuotient.size(); i++)
    {
        for (int j = 0; j < TestQuotient.size(); j++)
        {
            assert(TestQuotient[i][j] == matBase[i * 5 + j] / arg);
        }
    }
}


int main()
{
    cout << "Constructor test..........";
    TestConstructor();
    cout << "passed!\n";

    cout << "Basic operators tests.....";
    TestIndexing();
    TestSize();
    TestResize();
    TestResizeRowsAndCols();
    cout << "passed!\n";

    cout << "Row output test...........";
    TestRow();
    cout << "passed!\n";

    cout << "Column output test........";
    TestCol();
    cout << "passed!\n";

    cout << "Minimum value test........";
    TestMinValue();
    cout << "passed!\n";

    cout << "Maximum value test........";
    TestMaxValue();
    cout << "passed!\n";

    cout << "Scalar arithmetics test...";
    TestArithmeticsScalar();
    cout << "passed!\n";



    cout << "\n=========================ALL TESTS COMPLETE!=========================\n\n";
    return 0;
}