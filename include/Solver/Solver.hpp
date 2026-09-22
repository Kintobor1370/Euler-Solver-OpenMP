/**************************************************************************************************************************
**                                                         SOLVERS                                                       **
***************************************************************************************************************************
**         The code below realizes solvers for the logistic equation using vairous numerical methods, as well as         **
**                 a structure of all calculations' final results that will be used for creating plots.                  **
**************************************************************************************************************************/
#pragma once

#include "Vector.hpp"
#include "Equation.hpp"

//_____________________________________________________SOLVER RESULTS______________________________________________________
struct SolverResults
{
    Vector Times;                                                       // Time points
    std::vector<Vector> Values;                                         // Values of the solution at time
    std::vector<Vector> Derivatives;                                    // Derivatives

    // Clear solver results
    void clear();
};


//___________________________________________________EULER METHOD SOLVER___________________________________________________
class EulerSolver
{
    SolverResults results;

private:
    void add(Vector value, CalcType time);

    void addDerivative(Vector derivative);

public:
    EulerSolver();

    // Solve given equation numericaly for fixed amount of iterations
    SolverResults Solve(
        Equation currEquation,
        ExtrapolationType type,
        CalcType timeMax,
        CalcType step,
        Vector valInit,
        bool debug_print_enabled = false
    );
};


//________________________________________________RUNGE-KUTTA 4 METHOD SOLVER_______________________________________________
class RungeKutta4thSolver
{
    SolverResults results;

private:
    void add(Vector value, CalcType time);

    void addDerivative(Vector derivative);

public:
    // Solve given equation numericaly for fixed amount of iterations
    SolverResults Solve(
        Equation currEquation,
        ExtrapolationType type,
        CalcType timeMax,
        CalcType step,
        Vector valInit,
        bool debug_print_enabled = false
    );
};