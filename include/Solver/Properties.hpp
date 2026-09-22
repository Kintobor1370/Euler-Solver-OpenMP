#pragma once

#include <string>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "VectorOfMatrix.hpp"
#include "MatrixOfMatrix.hpp"

#define PI 3.1415927

enum KernelType 
{
    Normal, 
};


//___________________________________________________MODEL PROPERTIES______________________________________________________
struct Properties
{
    int SpeciesNumber;                                                  // Number of species                
        
    Vector b;                                                           // Birth rate oer unit time in species i  (b)
    Vector d;                                                           // Death rate per unit time in species i  (d)
    Matrix d_prime;                                                     // Linear dependence of death rate of species i on neighbours of species  (d')
        
    VectorOfMatrix M;                                                   // Rate of birth-movement of species i to distance (x,y)  (m(x))
    MatrixOfMatrix W;                                                   // Death-weighting for neighbours j of species i at distance (x,y)  (w(x))

    Matrix MaxNumForW;                                                  // Maximum number of non-zero bins for 'w' kernel
    Vector MaxNumForM;                                                  // Maximum number of non-zero bins for 'm' kernel

    Vector SigmaM;
    Matrix SigmaW;

    Vector MomentsGrid;                                                 // The non-uniform grid that corresponds to pair densities
    CalcType CutoffDistance;                                            // The largest distance between two individuals for which we compute the pair density
    Vector KernelsGrid;                                                 // The uniform grid that corresponds to kernels
    CalcType KernelsGridStep;                                           // The step of uniform grid for kernels

    //..............................GENERATE GRIDS FOR KERNELS AND PAIR DENSITIES
    void GenerateGrids(
        CalcType sigma_w, 
        CalcType sigma_m,
        CalcType cutoff_dist_multiplier =  5,
        int num_for_moments = 5
    );

    //..............................GENERATE KERNEL
    std::pair<Matrix, CalcType> GenerateKernel(
        CalcType s,                                                     // Sigma 
        CalcType R,                                                     // Max radius 
        KernelType type
    );

    //..............................GENERATE MODEL PROPERTIES
    static Properties Generate(
        int num,                                                        // Number of species
        Matrix sW,                                                      // Sigma W
        Vector sM,                                                      // Sigma M
        Vector b,                                                           
        Vector d,
        Matrix dd,
        KernelType w_type = Normal,                                     // W kernel type
        KernelType m_type = Normal                                      // M kernel type
    );
};