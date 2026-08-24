#include <iostream>
#include <vector>
#include <cassert>
#include "Vector.hpp"

using namespace std;


int main()
{
    vector<CalcType> testVec {1, 2, 3, 4, 5};
    Vector testVecObj(testVec);
    assert (testVecObj.get_vector() == testVec);
    
    // Indexing operator
    for (int i = 0; i < testVecObj.size(); i++)
    {
        assert (testVecObj[i] == i + 1);
    }

    // Vector is not empty
    assert (!testVecObj.empty());

    // Vector's size
    assert (testVecObj.size() == 5);

    // Resize to bigger size
    testVecObj.resize(8);
    for (int i = 0; i < 5; i++)
    {
        assert (testVecObj[i] == i + 1);
    }
    for (int i = 5; i < testVecObj.size(); i++)
    {
        assert (testVecObj[i] == 0);
    }

    // Resize to smaller size
    testVecObj.resize(3);
    for (int i = 0; i < testVecObj.size(); i++)
    {
        assert (testVecObj[i] == i + 1);
    }

    // Clear Vector
    testVecObj.clear();
    assert (testVecObj.empty());
    assert (testVecObj.size() == 0);

    cout << "\n=========================ALL TESTS COMPLETE!=========================\n\n";
    return 0;
}