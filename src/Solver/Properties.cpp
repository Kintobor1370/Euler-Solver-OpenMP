#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include "Properties.hpp"

using namespace std;


//..............................GENERATE GRIDS FOR KERNELS AND PAIR DENSITIES
void Properties::GenerateGrids(
    CalcType sigma_w, 
    CalcType sigma_m
) {
    CalcType cutoff_distance = (sigma_w + sigma_m) * 5;
    CalcType max_radius = std::max(sigma_w, sigma_m) * 5;

    int num_for_moments = 5;
    auto moments_grid = Vector::abs(
        -Vector::log(
            -Vector::setLinSpaced(num_for_moments, 0, num_for_moments - 1) / num_for_moments + 1
        ) * 0.01 * num_for_moments
    );
    while (moments_grid.last() < cutoff_distance - 0.01)
    {
        num_for_moments++;
        moments_grid = Vector::abs(
            -Vector::log(
                -Vector::setLinSpaced(num_for_moments, 0, num_for_moments - 1) / num_for_moments + 1
            ) * 0.01 * num_for_moments
        );
    }
    CalcType parameter = cutoff_distance / moments_grid.last();
    moments_grid = moments_grid * parameter;
    assert (std::abs(moments_grid.last() - cutoff_distance) < EPSILON);

    int num_for_kernels = (num_for_moments - 1) * 2 - 1;
    if (std::min(sigma_w, sigma_m) < 0.015)
    {
        num_for_kernels = (num_for_kernels - 2) * 4 - 1;
        num_for_kernels = (num_for_kernels - 1) * 2 - 1;
    }
    cout << "number of mid-points for pair density grid: " << num_for_moments
         << "\nnumber of mid-points for kernels grid:      " << num_for_kernels << "\n\n";

    assert ((num_for_kernels % 2 == 1) && (num_for_kernels >= 5));
    auto kernels_grid = Vector::setLinSpaced(num_for_kernels, 0, max_radius);

    CutoffDistance  = moments_grid.last();
    MomentsGrid = moments_grid;
    KernelsGrid = kernels_grid;
    KernelsGridStep = kernels_grid[2] - kernels_grid[0];
}

//..............................GENERATE KERNEL
pair<Matrix, CalcType> Properties::GenerateKernel(
    CalcType s,                                                     // Sigma 
    CalcType R,                                                     // Max radius 
    KernelType type
) {
    Vector grid = KernelsGrid;
    CalcType step = KernelsGridStep;

    Matrix kernel_values(grid.size());
    int max_non_zero_num = 0; 

    // Calculate
    for (int x = 0; x < grid.size(); x++)
    {
        for (int y = 0; y < grid.size(); y++)
        {
            const auto r = hypot(grid[x], grid[y]);
            if(r <= R)
            {
                switch (type)
                {
                    case Normal:
                        auto norm = s * sqrt(2 * PI) * (1 - exp((-R * R) / (2 * s * s)));
                        auto weight = exp((-r * r) / (2 * s * s));
                        kernel_values[x][y] = weight / norm;
                        break;
                }
                if (kernel_values[x][y] != 0)
                {
                    max_non_zero_num = max({ max_non_zero_num, x + 1, y + 1 });
                }
            }
            else kernel_values[x][y] = 0;
        }
    }
    if (grid.size() % 2 == 1 && max_non_zero_num % 2 == 0 && max_non_zero_num != 2)
    {
        max_non_zero_num++;
    }
    if (max_non_zero_num == 1)
    {
        max_non_zero_num = 2;
    }

    // Renormalize
    CalcType integral = 0;
    for (int x = 1 - max_non_zero_num; x < max_non_zero_num - 1; x += 2)
    {
        for (int y = 1 - max_non_zero_num; y < max_non_zero_num - 1; y += 2)
        {
            integral += kernel_values[abs(x + 1)][abs(y + 1)];
        }
    }
    assert (integral != 0);
    integral *= step * step;
    kernel_values = kernel_values / integral;

    return make_pair(kernel_values, max_non_zero_num);
}

//..............................GENERATE MODEL PROPERTIES
Properties Properties::Generate(
    int num,                                                            // Number of species
    Matrix sW,                                                          // Sigma W
    Vector sM,                                                          // Sigma M
    Vector b,                                                           
    Vector d,
    Matrix dd,
    KernelType w_type,                                                  // W kernel type
    KernelType m_type                                                   // M kernel type
) {
    Properties props;
    props.SpeciesNumber = num;
    props.SigmaM = sM;
    props.SigmaW = sW;
    props.b = b;
    props.d = d;
    props.d_prime = dd;
    props.GenerateGrids(sW.max_value(), sM.max_value());

    MatrixOfMatrix w(num);
    Matrix max_num_w(num);
    
    Matrix max_radius_W;
    if (w_type == Normal)
    {
        max_radius_W = sW * 3;
    }
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            auto kernel_W = props.GenerateKernel(sW[i][j], max_radius_W[i][j], w_type);
            w(i, j) = kernel_W.first;
            max_num_w[i][j] = kernel_W.second;
        }
    }    

    VectorOfMatrix m(num);
    Vector max_num_m(num);
    
    Vector max_radius_M;
    if (m_type == Normal)
    {
        max_radius_M = sM * 3;
    }
    for (int i = 0; i < num; i++)
    {
        auto kernel_M = props.GenerateKernel(sM[i], max_radius_M[i], m_type);
        m(i) = kernel_M.first;
        max_num_m[i] = kernel_M.second;
    }

    props.M = m;
    props.W = w;
    props.MaxNumForW = max_num_w;
    props.MaxNumForM = max_num_m;
    return props;
}