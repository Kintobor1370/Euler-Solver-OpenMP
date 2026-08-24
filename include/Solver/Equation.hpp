#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include "MatrixOfMatrix.hpp"
#include "Properties.hpp"

enum ExtrapolationType 
{ 
    Zero, 
    SquaredN, 
    Alpha, 
    Exponential, 
};


//_______________________________EQUATIONS FOR THE DYNAMICS OF SINGLET AND PAIR DENSITIES__________________________________
class Equation
{
    Properties props;                                                   // Model properties
    Vector N;                                                           // Vector of current singlet densities
    MatrixOfMatrix C;                                                   // Current pair densities
    ExtrapolationType C_extrapolation_type;

private:
    // Make Vector of N (Vector) and C (Matrix of Matrix) values
    Vector MakeVector(Vector N, MatrixOfMatrix C);

    // Calculte integral w(x)C(x)dx
    Matrix CalculateIntegralWC(MatrixOfMatrix C, Vector N);

    // Calculte integral m(x)C(x - y)dx
    MatrixOfMatrix CalculateIntegralMCShift(MatrixOfMatrix C, Vector N);

    // Calculate integral w(x)C(x - y)dx
    MatrixOfMatrix CalculateIntegralWCShift(MatrixOfMatrix C, Vector N);

    // Calculate integral w(x)C(x)C(x - y)dx
    MatrixOfMatrix CalculateIntegralWCShiftDouble(MatrixOfMatrix C, Vector N);

    CalcType MakeIntegralWithPairDensity(
        int shiftByX, 
        int shiftByY, 
        int max_non_zero_num, 
        Matrix kernel, 
        Matrix C, 
        CalcType asymptoticValue
    );

    // w(x)C(x)C(x - y)dx
    CalcType MakeIntegralWithPairDensityShift(
        int shiftByX, 
        int shiftByY, 
        int max_non_zero_num, 
        Matrix kernel, 
        Matrix C, 
        CalcType asymptoticValue
    );

    CalcType BilinearInterpolation(
        Vector grid,
        Matrix values,
        CalcType x,
        CalcType y,
        CalcType max_distance,
        ExtrapolationType type,
        CalcType asymptotic_value = 0
    );

    CalcType Extrapolation(
        Vector grid, 
        Matrix values, 
        CalcType distance, 
        CalcType max_distance, 
        ExtrapolationType type, 
        CalcType asymptotic_value
    );

public:
    Equation(Properties p);

    // Make Vector of equilibrium values for N (Vector) and C (Matrix of Matrix). Here C=N*N
    Vector GenerateEquilibriumValuesForNAndC(CalcType value);

    // Start Calculations
    Vector operator () (CalcType times, Vector vals, ExtrapolationType chosen_type);
};