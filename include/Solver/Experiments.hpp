#pragma once

#include "Vector.hpp"
#include "Properties.hpp"
#include "Equation.hpp"
#include "Solver.hpp"


//_____________________________________________________EXPERIMENTS_________________________________________________________
class Experiments
{
    Properties Props;
    std::vector<Properties> PropsVector;
    std::string file_path_prefix;
    std::string file_path_separator;
    std::string reader_file_path;
    std::string visdata_path;
    bool enable_debug_print;

private:
    // Comparator for sorting vector of Solver Results
    static bool SortBySigma(
        const std::pair<CalcType, SolverResults> &a, 
        const std::pair<CalcType, SolverResults> &b
    );

    // Calculate first moment
    SolverResults CalculateFirstMoment(
        CalcType tMax, 
        ExtrapolationType type = SquaredN, 
        CalcType step = 0.1
    );

    // Calculate first moment with varying sigma (sM or sW)
    std::vector<SolverResults> CalculateWithVaryingSigma(
        CalcType tMax, 
        char sigmaType, 
        Vector sigmaVec, 
        ExtrapolationType type=SquaredN, 
        CalcType step = 0.1
    );

<<<<<<< HEAD
    // Run Visualiser.py
=======
    // Run visualisation script
>>>>>>> 076b2183d309fa3090126b9ba8e103745fcfa629
    void RunVisualiser();

public:
    Experiments();

    ~Experiments();

    void Experiment_14_4(int input_data);

    void Experiment_14_6(char sigmaType, std::string radiusType);

    void Custom_Experiment();

    void KernelTest(char KernelSymbol, std::string case_str);
};