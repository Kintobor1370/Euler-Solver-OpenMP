/**************************************************************************************************************************
**                                                         SOLVERS                                                       **
***************************************************************************************************************************
**         The code below realizes solvers for the logistic equation using vairous numerical methods, as well as         **
**                 a structure of all calculations' final results that will be used for creating plots.                  **
**************************************************************************************************************************/
#include <iostream>
#include "Solver.hpp"

using namespace std;


//_____________________________________________________SOLVER RESULTS______________________________________________________
void SolverResults::clear()
{
    Times.clear();
    Values.clear();
    Derivatives.clear();
}

//___________________________________________________EULER METHOD SOLVER___________________________________________________

void EulerSolver::add(Vector value, CalcType time)
{
    results.Values.emplace_back(std::move(value));
    results.Times.add(time);
}

void EulerSolver::addDerivative(Vector derivative)
{ 
    results.Derivatives.emplace_back(std::move(derivative)); 
}

// Solve given equation numericaly for fixed amount of iterations
SolverResults EulerSolver::Solve(
    Equation currEquation,
    ExtrapolationType type,
    CalcType timeMax,
    CalcType step,
    Vector valInit,
    bool debug_print_enabled
) {
    CalcType time = 0;
    Vector value = valInit;
    Vector derivative = currEquation(time, value, type);

    add(value, time);
    addDerivative(derivative);
    if (debug_print_enabled)
    {
        cout << "   t = " << time << ";   N = " << value.first() << '\n';
    }
    time += step;
    while (time < timeMax)
    {
        value = value + derivative * step;
        for (auto& val : value)
        {
            if (val < 0)
            {
                val = 0;
            }
        }
        add(value, time);
        derivative = currEquation(time, value, type);
        addDerivative(derivative);
        
        if (debug_print_enabled)
        {
            cout << "   t = " << time << ";   N = " << value.first() << '\n';
        }
        time += step;
    }
    return results;
}

//________________________________________________RUNGE-KUTTA 4 METHOD SOLVER_______________________________________________
void RungeKutta4thSolver::add(Vector value, CalcType time)
{
    results.Values.emplace_back(std::move(value));
    results.Times.add(time);
}

void RungeKutta4thSolver::addDerivative(Vector derivative)
{ 
    results.Derivatives.emplace_back(std::move(derivative)); 
}

// Solve given equation numericaly for fixed amount of iterations
SolverResults RungeKutta4thSolver::Solve(
    Equation currEquation,
    ExtrapolationType type,
    CalcType timeMax,
    CalcType step,
    Vector valInit,
    bool debug_print_enabled
) {
    CalcType time = 0;
    Vector value = valInit;
    
    results.clear();
    add(value, time);
    while (time < timeMax)
    {
        addDerivative(currEquation(time, value, type));
        
        Vector c0 = currEquation(time, value, type);
        time += step / 2;
        Vector c1 = currEquation(time, value + (c0 * step / 2), type);
        Vector c2 = currEquation(time, value + (c1 * step / 2), type);
        time += step / 2;
        Vector c3 = currEquation(time, value + (c2 * step), type);
        Vector c = c0;
        c = c + (c1 * 2);
        c = c + (c2 * 2);
        c = c + c3;
        value = value + (c * step / 6);

        for (auto& val : value)
        {
            if (val < 0)
            {
                val = 0;
            }
        }
        add(value, time);

        if (debug_print_enabled)
        {
            cout << "   t = " << time << ";   N = " << value.first() << '\n';
        }
    }
    addDerivative(currEquation(time, value, type));
    return results;
}