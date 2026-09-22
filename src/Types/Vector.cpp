#include <iostream>
#include <cmath>
#include <numeric>
#include <utility>
#include <algorithm>
#include "Vector.hpp"

using namespace std;


//_________________________________VECTOR OF CALCULATION TYPE__________________________________
Vector::Vector() {}

Vector::Vector(const vector<CalcType>& stlVec)
{
    vec.assign(stlVec.begin(), stlVec.end());
}

Vector::Vector(const int size) 
{
    vec.reserve(size); 
}

Vector::Vector(const int size, const CalcType val)
{
    vec.reserve(size);
    for (int i = 0; i < size; i++)
    {
        vec.push_back(val);
    }
}

Vector::Vector(const Vector& other) : vec(other.vec) {}

Vector::Vector(Vector&& other) noexcept : vec(move(other.vec)) {}

vector<CalcType> Vector::get_vector()
{ 
    return vec; 
}

CalcType& Vector::operator [] (const int index) 
{ 
    return vec.at(index); 
}

bool Vector::empty() const
{ 
    return vec.empty(); 
}

int Vector::size() const
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
    std::sort(vec.begin(), vec.end()); 
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
    return vec.front(); 
}

CalcType Vector::last() 
{ 
    return vec.back(); 
}

Vector Vector::head(int n)                  
{
    vector<CalcType> vecHead(vec.begin(), vec.begin() + min(n, (int) vec.size()));
    return Vector(vecHead); 
}

Vector Vector::tail(int n)
{
    vector<CalcType> vecTail(vec.end() - min(n, (int) vec.size()), vec.end());
    return Vector(vecTail);
}

void Vector::erase_first(int n)
{
    vec.erase(vec.begin(), vec.begin() + min(n, (int) vec.size()));
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
    return vec.empty() ? 0 : (accumulate(vec.begin(), vec.end(), 0) / (CalcType) vec.size()); 
}

Vector Vector::setLinSpaced(
    CalcType size, 
    CalcType minVal, 
    CalcType maxVal
) {
    Vector result(size, 0);
    CalcType step = (maxVal - minVal) / (size - 1);
    result[0] = minVal;
    result[size - 1] = maxVal;
    for (int i = 1; i < size - 1; i++)
    {
        result[i] = minVal + i * step;
    }
    return result;
}

Vector Vector::log(Vector arg)
{
    vector<CalcType> argVec = arg.get_vector();
    vector<CalcType> logVec = argVec;
    transform(argVec.begin(), argVec.end(), logVec.begin(), [](CalcType a) {
        return std::log(a);
    });
    return Vector(logVec);
}

Vector Vector::abs(Vector arg)
{
    vector<CalcType> argVec = arg.get_vector();
    vector<CalcType> absVec = argVec;
    transform(argVec.begin(), argVec.end(), absVec.begin(), [](CalcType a) {
        return std::abs(a);
    });
    return Vector(absVec);
}

Vector& Vector::operator = (const Vector& v)
{
    vec = v.vec;
    return *this;
}

Vector& Vector::operator = (Vector&& v) noexcept
{
    vec = move(v.vec);
    return *this;
}

Vector operator + (Vector baseVec, CalcType addVal)
{
    vector<CalcType> sum = baseVec.get_vector();
    transform(baseVec.begin(), baseVec.end(), sum.begin(), [addVal](CalcType a){
        return a + addVal;
    });
    return Vector(sum);
}

Vector operator - (Vector baseVec, CalcType subVal)
{
    vector<CalcType> sub = baseVec.get_vector();
    transform(baseVec.begin(), baseVec.end(), sub.begin(), [subVal](CalcType a){
        return a - subVal;
    });
    return Vector(sub);
}

Vector operator * (Vector baseVec, CalcType comVal)
{
    vector<CalcType> product = baseVec.get_vector();
    transform(baseVec.begin(), baseVec.end(), product.begin(), [comVal](CalcType a){
        return a * comVal;
    });
    return Vector(product);
}

Vector operator / (Vector baseVec, CalcType divVal)
{
    vector<CalcType> quotient = baseVec.get_vector();
    transform(baseVec.begin(), baseVec.end(), quotient.begin(), [divVal](CalcType a){
        return a / divVal;
    });
    return Vector(quotient);
}

Vector Vector::operator - ()
{
    vector<CalcType> negativeVec = vec;
    transform(vec.begin(), vec.end(), negativeVec.begin(), [](CalcType a){
        return a * -1;
    });
    return Vector(negativeVec);
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

ostream& operator << (ostream& out, const Vector &v)
{
    out << v.vec.at(0);
    for(int i = 1; i < v.vec.size(); i++)
    {
        out << ", " << v.vec.at(i);
    }
    out << '\n';
    return out;
}