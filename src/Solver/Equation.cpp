#include <cmath>
#include <cassert>
#include "Conversion.hpp"
#include "Equation.hpp"

using namespace std;


//_______________________________EQUATIONS FOR THE DYNAMICS OF SINGLET AND PAIR DENSITIES__________________________________

// Make Vector of N (Vector) and C (Matrix of Matrix) values
Vector Equation::MakeVector(Vector N, MatrixOfMatrix C)
{
    Vector result = N;
    result.add(MatrixOfMatrixToVector(C));

    int expectedSize = props.SpeciesNumber + 
                       props.SpeciesNumber * 
                       props.SpeciesNumber * 
                       props.MomentsGrid.size() * 
                       props.MomentsGrid.size();
    assert (result.size() == expectedSize);
    return result;
}

// Calculte integral w(x)C(x)dx
Matrix Equation::CalculateIntegralWC(MatrixOfMatrix C, Vector N)
{
    Matrix result(props.SpeciesNumber);
    for (int i = 0; i < props.SpeciesNumber; i++)
    {
        for (int j = 0; j < props.SpeciesNumber; j++)
        {
            CalcType asymptoticVal = N[i] * N[j];
            result[i][j] = MakeIntegralWithPairDensity(
                0, 
                0, 
                props.MaxNumForW[i][j], 
                props.W(i, j), 
                C(i, j), 
                asymptoticVal
            );
        }
    }
    return result;
}

// Calculte integral m(x)C(x - y)dx
MatrixOfMatrix Equation::CalculateIntegralMCShift(MatrixOfMatrix C, Vector N)
{
    MatrixOfMatrix result(props.SpeciesNumber);
    for (int i = 0; i < props.SpeciesNumber; i++)
    {
        for (int j = 0; j < props.SpeciesNumber; j++)
        {
            Matrix resultElem(props.MomentsGrid.size());
            CalcType asymptoticVal = N[i] * N[j];
            for (int xNum = 0; xNum < props.MomentsGrid.size(); xNum++)
            {
                for (int yNum = 0; yNum < props.MomentsGrid.size(); yNum++)
                {
                    resultElem[xNum][yNum] = MakeIntegralWithPairDensity(
                        xNum, 
                        yNum, 
                        props.MaxNumForM[i], 
                        props.M(i), 
                        C(i, j), 
                        asymptoticVal
                    );
                }
            }
            result(i, j) = resultElem;
        }
    }
    return result;
}

// Calculate integral w(x)C(x - y)dx
MatrixOfMatrix Equation::CalculateIntegralWCShift(MatrixOfMatrix C, Vector N)
{
    MatrixOfMatrix result(props.SpeciesNumber);
    for (int i = 0; i < props.SpeciesNumber; i++) 
    {
        for (int j = 0; j < props.SpeciesNumber; j++)
        {
            Matrix resultElem(props.MomentsGrid.size());
            CalcType asymptoticVal = N[i] * N[j];
            for (int xNum = 0; xNum < props.MomentsGrid.size(); xNum++)
            {
                for (int yNum = 0; yNum < props.MomentsGrid.size(); yNum++)
                {
                    resultElem[xNum][yNum] = MakeIntegralWithPairDensity(
                        xNum, 
                        yNum, 
                        props.MaxNumForW[i][j],
                        props.W(i, j), 
                        C(i, j), 
                        asymptoticVal
                    );
                }
            }
            result(i, j) = resultElem;
        }
    }
    return result;
}

// Calculate integral w(x)C(x)C(x - y)dx
MatrixOfMatrix Equation::CalculateIntegralWCShiftDouble(MatrixOfMatrix C, Vector N)
{
    MatrixOfMatrix result(props.SpeciesNumber);
    for (int i = 0; i < props.SpeciesNumber; i++) 
    {
        for (int j = 0; j < props.SpeciesNumber; j++)
        {
            Matrix resultElem(props.MomentsGrid.size());
            CalcType asymptoticVal = N[i] * N[j];
            for (int xNum = 0; xNum < props.MomentsGrid.size(); xNum++)
            {
                for (int yNum = 0; yNum < props.MomentsGrid.size(); yNum++)
                {
                    resultElem[xNum][yNum] = MakeIntegralWithPairDensityShift(
                        xNum, 
                        yNum, 
                        props.MaxNumForW[i][j],
                        props.W(i, j), 
                        C(i, j), 
                        asymptoticVal
                    );
                }
            }
            result(i, j) = resultElem;
        }
    }
    return result;
}

CalcType Equation::MakeIntegralWithPairDensity(
    int shiftByX, 
    int shiftByY, 
    int max_non_zero_num, 
    Matrix kernel, 
    Matrix C, 
    CalcType asymptoticValue
) {
    CalcType integral = 0;
    for (int i = 1 - max_non_zero_num; i < max_non_zero_num - 1; i += 2)
    {
        for (int j = 1 - max_non_zero_num; j < max_non_zero_num - 1; j += 2)
        {
            assert (i + 1 < max_non_zero_num);
            assert (j + 1 < max_non_zero_num);

            const CalcType sum_x = abs(
                props.MomentsGrid[shiftByX] + (i >= 0 ? props.KernelsGrid[i+1] : -props.KernelsGrid[-i-1])
            );
            const CalcType sum_y = abs(
                props.MomentsGrid[shiftByY] + (j >= 0 ? props.KernelsGrid[j+1] : -props.KernelsGrid[-j-1])
            );

            auto pair_density = BilinearInterpolation(
                props.MomentsGrid, 
                C, 
                sum_x, 
                sum_y, 
                props.CutoffDistance, 
                C_extrapolation_type, 
                asymptoticValue
            );
            integral += kernel[abs(i + 1)][abs(j + 1)] * pair_density;
        }
    }
    integral *= pow(props.KernelsGridStep, 2);
    return integral;
}

// w(x)C(x)C(x - y)dx
CalcType Equation::MakeIntegralWithPairDensityShift(
    int shiftByX, 
    int shiftByY, 
    int max_non_zero_num, 
    Matrix kernel, 
    Matrix C, 
    CalcType asymptoticValue
) {
    CalcType integral = 0;
    for (int i = 1 - max_non_zero_num; i < max_non_zero_num - 1; i += 2)
    {
        for (int j = 1 - max_non_zero_num; j < max_non_zero_num - 1; j += 2)
        {
            assert (i + 1 < max_non_zero_num);
            assert (j + 1 < max_non_zero_num);

            const CalcType _x = abs(
                props.MomentsGrid[0] + (i >= 0 ? props.KernelsGrid[i+1] : -props.KernelsGrid[-i-1])
            );
            const CalcType _y = abs(
                props.MomentsGrid[0] + (j >= 0 ? props.KernelsGrid[j+1] : -props.KernelsGrid[-j-1])
            );
            const CalcType sum_x = abs(
                props.MomentsGrid[shiftByX] + (i >= 0 ? props.KernelsGrid[i+1] : -props.KernelsGrid[-i-1])
            );
            const CalcType sum_y = abs(
                props.MomentsGrid[shiftByY] + (j >= 0 ? props.KernelsGrid[j+1] : -props.KernelsGrid[-j-1])
            );

            auto pair_density = BilinearInterpolation(
                props.MomentsGrid, 
                C, 
                _x, 
                _y, 
                props.CutoffDistance, 
                C_extrapolation_type, 
                asymptoticValue
            );
            auto pair_density_shift = BilinearInterpolation(
                props.MomentsGrid, 
                C, 
                sum_x, 
                sum_y, 
                props.CutoffDistance, 
                C_extrapolation_type, 
                asymptoticValue
            );
            integral += kernel[abs(i + 1)][abs(j + 1)] * pair_density * pair_density_shift;
        }
    }
    integral *= pow(props.KernelsGridStep, 2);
    return integral;
}

CalcType Equation::BilinearInterpolation(
    Vector grid,
    Matrix values,
    CalcType x,
    CalcType y,
    CalcType max_distance,
    ExtrapolationType type,
    CalcType asymptotic_value
) {
    assert (grid.size() == values.size());

    CalcType distance = hypot(x, y);
    if (distance > max_distance)
    {
        return Extrapolation(grid, values, distance, max_distance, type, asymptotic_value);
    }

    // Find segments [a, b] and [c, d] so that x will be in [a, b] and y will be in [c, d]
    int i = 1, j = 1;
    while (x > grid[i]) i++;
    while (y > grid[j]) j++;
    
    CalcType a = grid[i-1];
    CalcType b = grid[i];
    CalcType c = grid[j-1];
    CalcType d = grid[j];

    // Compute weights
    CalcType wx = (x - a) / (b - a);
    CalcType wy = (y - c) / (d - c);

    // Compute weighted value
    CalcType value = values[i-1][j-1] * (1 - wx) * (1 - wy) + 
                     values[i][j-1] * wx * (1 - wy) +
                     values[i-1][j] * (1 - wx) * wy +
                     values[i][j] * wx * wy;
    return value;
}

CalcType Equation::Extrapolation(
    Vector grid, 
    Matrix values, 
    CalcType distance, 
    CalcType max_distance, 
    ExtrapolationType type, 
    CalcType asymptotic_value
) {
    if (abs(values[0].last() - asymptotic_value) < EPSILON)
    {
        return asymptotic_value;
    }

    CalcType extrapolated_value;
    switch (type)
    {
        case Zero:
        {
            extrapolated_value = 0;
            break;
        }
        case SquaredN:
        {
            extrapolated_value = asymptotic_value;
            break;
        }
        case Alpha:
        {
            CalcType alpha = 2 / (grid.size() + 1);
            Vector predicted_values;
            
            predicted_values.add(values[0][0]);
            for (int k = 1; k < grid.size(); k++)
            {
                CalcType new_predicted_value = alpha * values[0][k] + (1 - alpha) * predicted_values[k-1];
                predicted_values.add(new_predicted_value);
            }
            extrapolated_value = alpha * asymptotic_value + (1 - alpha) * predicted_values.last();
            break;
        }
        case Exponential:
        {
            const int accuracy = 5;
            CalcType decay_avg = 0;
            for (int k = 1; k < accuracy; k++)
            {
                CalcType pair_distance = max_distance - grid[grid.size() - 1 - k];
                CalcType new_decay_value = abs(
                    (values[0][grid.size() - 1 - k] - asymptotic_value) / (values[0].last() - asymptotic_value)
                );
                assert (pair_distance > 0);
                assert (new_decay_value >= 0);

                new_decay_value = log(new_decay_value) / pair_distance;
                decay_avg += new_decay_value;
            }
            decay_avg = decay_avg / (accuracy - 1);
            extrapolated_value = asymptotic_value + 
                                 (values[0].last() - asymptotic_value) * 
                                 exp(-1 * decay_avg * (distance - max_distance));
            break;
        }
    }
    return extrapolated_value;
}

Equation::Equation(Properties p) : props(p) {}

// Make Vector of equilibrium values for N (Vector) and C (Matrix of Matrix). Here C=N*N
Vector Equation::GenerateEquilibriumValuesForNAndC(CalcType value)
{
    int N_size = props.SpeciesNumber;
    int C_size = props.SpeciesNumber * 
                 props.SpeciesNumber * 
                 props.MomentsGrid.size() * 
                 props.MomentsGrid.size();
    
    Vector result;  
    for (int i = 0; i < N_size; i++)
    {
        result.add(value);
    }
    for (int i = 0; i < C_size; i++)
    {
        result.add(value * value);
    }
    return result;
}

// Start Calculations
Vector Equation::operator () (CalcType times, Vector vals, ExtrapolationType chosen_type)
{
    CalcType alpha = 1;
    CalcType beta = 0;
    CalcType gamma = 0;
    C_extrapolation_type = chosen_type;

    N = vals.head(props.SpeciesNumber);
    vals.erase_first(props.SpeciesNumber);
    C = VectorToMatrixOfMatrix(vals, props.SpeciesNumber, props.MomentsGrid.size());

    Vector dN(props.SpeciesNumber);                                 // Vector of derivatives of current first moments
    MatrixOfMatrix dC(props.SpeciesNumber);                         // Derivatives of current second moments

    Matrix WC = CalculateIntegralWC(C, N);                          // Integral w(x)C(x)dx
    MatrixOfMatrix MCShift = CalculateIntegralMCShift(C, N);        // Integral m(x)C(x-y)dx

    //FOR PARAMETRIC CLOSURE
    MatrixOfMatrix WCShift = CalculateIntegralWCShift(C, N);        // Integral w(x)C(x-y)dx
    MatrixOfMatrix WCDouble = CalculateIntegralWCShiftDouble(C, N); // Integral w(x)C(x)C(x-y)dx

    //.......................................CALCULATE FIRST MOMENT
    dN = N * (props.b - props.d);                                   // Contribution of birth and death, density independent
    Vector d_prime_sum(props.SpeciesNumber, 0);                     // Death contribution, density dependent
    for (int i = 0; i < props.SpeciesNumber; i++)
    {
        for (int j = 0; j < props.SpeciesNumber; j++)
        {
            d_prime_sum[i] = d_prime_sum[i] + props.d_prime[i][j] * WC[i][j];
        }
    }
    dN = dN - d_prime_sum;

    //.......................................CALCULATE SECOND MOMENT
    for (int i = 0; i < props.SpeciesNumber; i++)
    {
        for (int j = 0; j < props.SpeciesNumber; j++)
        {
            Matrix dC_elem(props.MomentsGrid.size());

            for (int xNum = 0; xNum < props.MomentsGrid.size(); xNum++)
            {
                for (int yNum = 0; yNum < props.MomentsGrid.size(); yNum++)
                {
                    // Birth contribution, density independent
                    CalcType result = props.b[i] * MCShift(i, j)[xNum][yNum] + props.b[j] * MCShift(j, i)[xNum][yNum]; 

                    // Birth contribution, Kronecker symbols
                    if (i == j)
                    {
                        result += 2 * props.b[i] * N[i] * BilinearInterpolation(
                            props.KernelsGrid,
                            props.M(i),
                            props.MomentsGrid[xNum],
                            props.MomentsGrid[yNum],
                            props.SigmaM[i] * 3,
                            Zero
                        );
                    }

                    // Death contribution, density independent
                    result -= props.d[i] * C(i, j)[xNum][yNum];
                    result -= props.d[j] * C(j, i)[xNum][yNum];

                    // Simple closure
                    for (int k = 0; k < props.SpeciesNumber; k++)
                    {
                        //result -= props.d_prime[i][k] * WC[i][k] * C(i, j)[xNum][yNum] / N[i];
                        //result -= props.d_prime[j][k] * WC[j][k] * C(j, i)[xNum][yNum] / N[j];

                        result -= props.d_prime[i][k] * (
                            alpha * WC[i][k] * C(i, j)[xNum][yNum] / N[i] +
                            beta * WCShift(i, k)[xNum][yNum] * C(i, j)[xNum][yNum] / N[i] +
                            gamma * WCDouble(i, k)[xNum][yNum] / N[i] -
                            beta * N[i] * N[i] * N[i]
                        ) / (alpha + beta);

                        result -= props.d_prime[j][k] * (
                            alpha * WC[j][k] * C(j, i)[xNum][yNum] / N[j] +
                            beta * WCShift(j, k)[xNum][yNum] * C(j, i)[xNum][yNum] / N[j] +
                            gamma * WCDouble(j, k)[xNum][yNum] / N[j] -
                            beta * N[j] * N[j] * N[j]
                        ) / (alpha + beta);
                    }
                    result -= props.d_prime[i][j] * C(i, j)[xNum][yNum] * BilinearInterpolation(
                        props.KernelsGrid,
                        props.W(i, j),
                        props.MomentsGrid[xNum],
                        props.MomentsGrid[yNum],
                        props.SigmaW[i][j] * 3,
                        Zero
                    );
                    result -= props.d_prime[j][i] * C(j, i)[xNum][yNum] * BilinearInterpolation(
                        props.KernelsGrid,
                        props.W(j, i),
                        props.MomentsGrid[xNum],
                        props.MomentsGrid[yNum],
                        props.SigmaW[j][i] * 3,
                        Zero
                    );
                    dC_elem[xNum][yNum] = result;
                }
            }
            dC(i, j) = dC_elem;
        }
    }
    return MakeVector(dN, dC);
}