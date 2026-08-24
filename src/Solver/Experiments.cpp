#define NOMINMAX

#include <iostream>
#include <cmath>
#include <map>
#include <cassert>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <omp.h>
#include "Matrix.hpp"
#include "Time.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "Experiments.hpp"

using namespace std;


//_____________________________________________________EXPERIMENTS_________________________________________________________
// Comparator for sorting vector of Solver Results
bool Experiments::SortBySigma(
    const pair<CalcType, SolverResults> &a, 
    const pair<CalcType, SolverResults> &b
) { 
    return (a.first < b.first); 
}

// Calculate first moment
SolverResults Experiments::CalculateFirstMoment(
    CalcType tMax, 
    ExtrapolationType type,
    CalcType step
) {
    PropsVector.clear();
    FileReader Reader(reader_file_path);

    Props = Reader.GetProperties(enable_debug_print = true);
    Equation equation(Props);
    EulerSolver solver;

    cout << "\n==========================CALCULATIONS START==========================\n";
    clock_t clockStart = clock();
    auto solverResults = solver.Solve(
        equation, 
        type, 
        tMax, 
        step, 
        equation.GenerateEquilibriumValuesForNAndC(200), 
        enable_debug_print = true
    );
    clock_t clockEnd = clock();
    cout << "\n===========================CALCULATIONS END===========================\n";
    
    Time calcTime(clockEnd - clockStart);
    cout << "TIME:  " << calcTime << '\n';
    return solverResults;
}

// Calculate first moment with varying sigma (sM or sW)
vector<SolverResults> Experiments::CalculateWithVaryingSigma(
    CalcType tMax, 
    char sigmaType, 
    Vector sigmaVec, 
    ExtrapolationType type,
    CalcType step
) {
    map<CalcType, SolverResults> sigmasAndResults;
    
    PropsVector.clear();
    for (int i = 0; i < sigmaVec.size(); i++)
    {
        FileReader Reader(reader_file_path);
        cout << "ENTRY " << i << ":\n";
        switch (sigmaType)
        {
            case 'W':
                PropsVector.push_back(Reader.GetWithoutSigmaW(sigmaVec[i], enable_debug_print = true));
                break;
            case 'M':
                PropsVector.push_back(Reader.GetWithoutSigmaM(sigmaVec[i], enable_debug_print = true));
                break;
            default:
                cout << "===============================ERROR!!================================\n" << endl;
                break;
        }
    }
    assert (PropsVector.size() == sigmaVec.size());

    int finishedIterations = 0;
    omp_lock_t printLock;
    omp_lock_t sigmaLock;
    omp_init_lock(&printLock);
    omp_init_lock(&sigmaLock);

    cout << "\n==========================CALCULATIONS START==========================\n";
    clock_t clockStart = clock();

    #pragma omp parallel for default(none) shared(type, tMax, step, sigmaType, sigmaVec, sigmasAndResults, printLock, sigmaLock, finishedIterations, cout)
    for (int i = 0; i < sigmaVec.size(); i++)
    {
        auto threadNum = omp_get_thread_num();

        omp_set_lock(&printLock);
        cout << (int) (finishedIterations * 100 / sigmaVec.size()) 
             << "%    THREAD " << threadNum << ":     ENTRY " << i << ": START\n";
        omp_unset_lock(&printLock);
        
        auto newProps = PropsVector.at(i);
        Equation equation(newProps);
        EulerSolver solver;

        auto newResult = solver.Solve(
            equation, 
            type, 
            tMax, 
            step, 
            equation.GenerateEquilibriumValuesForNAndC(200), 
            enable_debug_print = false
        );
        sigmasAndResults.insert({ sigmaVec[i], newResult });
        
        finishedIterations++;
        CalcType N = newResult.Values.at(newResult.Values.size() - 1).first();
        
        omp_set_lock(&printLock);
        cout << (int) (finishedIterations * 100 / sigmaVec.size()) 
             << "%    THREAD " << threadNum << ":     ENTRY " << i 
             << ": FINISH    sigma " << sigmaType << " = " << sigmaVec[i] << ";  N = " << N << '\n';
        omp_unset_lock(&printLock);
    }
    clock_t clockEnd = clock();
    cout << "\n===========================CALCULATIONS END===========================\n";
    
    omp_destroy_lock(&printLock);
    Time calcTime(clockEnd - clockStart);
    cout << "TIME:  " << calcTime << endl;

    assert (PropsVector.size() == sigmasAndResults.size());
    vector<SolverResults> results;
    for (auto result : sigmasAndResults)
    {
        results.push_back(result.second);
    }
    return results;
}

// Launch Visualiser.py     !! THIS FUNCTION WORKS ONLY ON WINDOWS !!
void Experiments::Visualise_Windows()
{ 
    WinExec("python ..\\Visualiser.py", 1);
}

Experiments::Experiments()
{
    file_path_prefix = "..\\Data\\";
    visdata_path = file_path_prefix + "VisData.csv";
}

Experiments::~Experiments()
{ 
    PropsVector.clear();
}

void Experiments::Experiment_14_4(int input_data)
{
    string plotTitle;
    switch(input_data)
    {
        case 0:
            reader_file_path = file_path_prefix + "14\\4\\a.csv";
            plotTitle = "(a)";
            break;

        case 1:
            reader_file_path = file_path_prefix + "14\\4\\b.csv";
            plotTitle = "(b)";
            break;
        
            case 2:
            reader_file_path = file_path_prefix + "14\\4\\c.csv";
            plotTitle = "(c)";
            break;
    }
    auto solverResults = CalculateFirstMoment(100);

    Vector N;
    Vector CSquareRoot;
    for (auto Values : solverResults.Values)
    {
        CalcType NVal = Values.first();
        N.add(NVal);
        
        CalcType CAtCutoffDistance = Values[Props.MomentsGrid.size()];
        CSquareRoot.add(std::sqrt(CAtCutoffDistance));
    }

    vector<Vector> plotPoints = { 
        solverResults.Times, 
        N, 
        CSquareRoot 
    };
    vector<string> plotLabels = { 
        "Time", 
        "N", 
        "Square root of C at cutoff distance" 
    };
    FileWriter VisData(visdata_path);
    VisData.WritePlotData("14.4", plotTitle, plotLabels, plotPoints);
    Visualise_Windows();
}

void Experiments::Experiment_14_6(char sigmaType, string radiusType)
{
    reader_file_path = file_path_prefix + "14\\6\\a.csv";
    string plotTitle = "(a)";
    if(sigmaType == 'M')
    {
        reader_file_path = file_path_prefix + "14\\6\\b.csv";
        plotTitle = "(b)";
    }
    auto sigmaVec = Vector::setLinSpaced(160, EPSILON, 0.2);
    auto solverResults = CalculateWithVaryingSigma(200, sigmaType, sigmaVec);
    
    Vector convergedN;
    Vector convergedCSquareRoot;
    for (int i = 0; i < PropsVector.size(); i++)
    {
        auto values = solverResults.at(i).Values;
        auto convergedNAndC = values.at(values.size() - 1);
        CalcType convergedNVal = convergedNAndC.first();
        convergedN.add(convergedNVal);

        CalcType convergedCAtCutoffDistance = convergedNAndC[PropsVector[i].MomentsGrid.size()];
        convergedCSquareRoot.add(std::sqrt(convergedCAtCutoffDistance));
    }

    vector<Vector> plotPoints = { 
        sigmaVec, 
        convergedN, 
        convergedCSquareRoot 
    };
    vector<string> plotLabels = { 
        radiusType, 
        "Equilibrium density", 
        "Square root of C at cutoff distance" 
    };
    FileWriter VisData(visdata_path);
    VisData.WritePlotData("14.6", plotTitle, plotLabels, plotPoints);
    Visualise_Windows();
}

void Experiments::Custom_Experiment()
{
    reader_file_path = file_path_prefix + "Custom\\experiment.csv";
    string plot_title = "My experiment";
    auto solver_results = CalculateFirstMoment(100, SquaredN, 0.1);

    Vector N;
    Vector CSquareRoot;
    for (auto Values : solver_results.Values)
    {
        CalcType N_value = Values.first();
        N.add(N_value);

        CalcType C_at_cutoff_distance = Values[Props.MomentsGrid.size()];
        CSquareRoot.add(std::sqrt(C_at_cutoff_distance));
    }
    
    vector<Vector> plot_points;
    plot_points.push_back(solver_results.Times);
    plot_points.push_back(N);
    plot_points.push_back(CSquareRoot);

    vector<string> plot_labels;
    plot_labels.push_back("Time");
    plot_labels.push_back("N");
    plot_labels.push_back("Square root of C at cutoff distance");

    FileWriter VisData(visdata_path);
    VisData.WritePlotData("1", plot_title, plot_labels, plot_points);
    Visualise_Windows();
}

void Experiments::KernelTest(char KernelSymbol, string case_str)
{
    FileReader Reader(file_path_prefix + "14\\4\\" + case_str + ".csv");
    auto Props = Reader.GetProperties(enable_debug_print = true);
    
    Matrix kernel;
    string title;
    switch(KernelSymbol)
    {
        case 'W':
            kernel = Props.W(0, 0);
            title = "w(r) kernel test for experiment " + case_str;
            break;
    
        case 'M':
            kernel = Props.M(0);
            title = "m(r) kernel test for experiment " + case_str;
            break;
        
        default:
            cout << "ERROR: No such kernel\n";
            break;
    }

    map<CalcType, CalcType> result;
    bool isUnique;

    for (int x = 0; x < Props.KernelsGrid.size(); x++)
    {
        for (int y = 0; y < Props.KernelsGrid.size(); y++)
        {
            isUnique = true;
            CalcType r = std::hypot(Props.KernelsGrid[x], Props.KernelsGrid[y]);
            for (auto item : result)
            {
                /*
                cout << "x = " << Props.KernelsGrid[x]
                     << "    y = " << Props.KernelsGrid[y] 
                     << "    r = " << r 
                     << "    kernel = " << kernel[x][y] 
                     << '\n';
                */
                if (r == item.first)
                {
                    isUnique = false;
                }
            }
            if (isUnique)
            {
                result.insert({ r, kernel[x][y] });
            }
        }
    }

    vector<CalcType> xVals;
    vector<CalcType> yVals;
    for (auto item : result)
    {
        xVals.push_back(item.first);
        yVals.push_back(item.second);
    }
    
    switch (KernelSymbol)
    {
        case 'W':
            cout << "MAX NON-ZERO NUMBERS: " << Props.MaxNumForW << '\n';
            break;
        
        case 'M':
            cout << "MAX NON-ZERO NUMBERS: " << Props.MaxNumForM << '\n';
            break;

        default:
            cout << "ERROR: No such kernel\n";
            break;
    }

    vector<Vector> plotPoints = { 
        xVals, 
        yVals 
    };
    vector<string> plotLabels = { 
        "r", 
        "distribution" 
    };
    FileWriter VisData(visdata_path);
    VisData.WritePlotData("1", title, plotLabels, plotPoints);
    Visualise_Windows();
}