#include <iostream>
#include <cassert>
#include "Matrix.hpp"
#include "Conversion.hpp"

using namespace std;


int main()
{
    Vector testMat(vector<CalcType> { 
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20,
        21, 22, 23, 24, 25
    });

    // Conversion test
    Matrix testMatObj = VectorToMatrix(testMat, 5);
    CalcType arg = 2.54;

    // Add a CalcType value
    Matrix TestOperation = testMatObj + arg;
    for (int i = 0; i < TestOperation.size(); i++)
    {
        for (int j = 0; j < TestOperation.size(); j++)
        {
            assert (TestOperation[i][j] == testMatObj[i][j] + arg);
        }
    }

    // Subtract a CalcType value
    TestOperation = testMatObj - arg;
    for (int i = 0; i < TestOperation.size(); i++)
    {
        for (int j = 0; j < TestOperation.size(); j++)
        {
            assert (TestOperation[i][j] == testMatObj[i][j] - arg);
        }
    }

    // Turn Matrix values to negative
    TestOperation = -testMatObj;
    for (int i = 0; i < TestOperation.size(); i++)
    {
        for (int j = 0; j < TestOperation.size(); j++)
        {
            assert (TestOperation[i][j] == testMatObj[i][j] * -1);
        }
    }

    // Multiply by a CalcType value
    TestOperation = testMatObj * arg;
    for (int i = 0; i < TestOperation.size(); i++)
    {
        for (int j = 0; j < TestOperation.size(); j++)
        {
            assert (TestOperation[i][j] == testMatObj[i][j] * arg);
        }
    }

    // Divide by a CalcType value
    TestOperation = testMatObj / arg;
    for (int i = 0; i < TestOperation.size(); i++)
    {
        for (int j = 0; j < TestOperation.size(); j++)
        {
            assert (TestOperation[i][j] == testMatObj[i][j] / arg);
        }
    }
    cout << "\n=========================ALL TESTS COMPLETE!=========================\n\n";
    return 0;
}