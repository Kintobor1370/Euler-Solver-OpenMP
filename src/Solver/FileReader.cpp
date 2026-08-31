#include <iostream>
#include <sstream>
#include <cmath>
#include <cassert>
#include "FileReader.hpp"

using namespace std;


//_____________________________________________________FILE READER_________________________________________________________
int FileReader::GetInt()
{
    getline(file, new_line);
    stringstream stream(new_line);

    getline(stream, new_word, ',');
    getline(stream, new_word, ',');
    getline(file, new_line);
    return stoi(new_word);
}

CalcType FileReader::GetCalcType()
{
    getline(file, new_line);
    stringstream stream(new_line);

    getline(stream, new_word, ',');
    getline(stream, new_word, ',');
    return stod(new_word);
}

Vector FileReader::GetVector(int vec_size)
{
    Vector vector_from_file;
    getline(file, new_line);
    stringstream stream(new_line);

    getline(stream, new_word, ',');
    while (getline(stream, new_word, ','))
    {
        vector_from_file.add(stod(new_word));
    }
    assert (vector_from_file.size() == vec_size);
    return vector_from_file;
}

Matrix FileReader::GetMatrix(int mat_size)
{
    Matrix matrix_from_file(mat_size);
    for (int row_num=0; row_num<mat_size; row_num++)
    {
        getline(file, new_line);
        stringstream stream(new_line);

        int col_num = 0;
        getline(stream, new_word, ',');
        while (getline(stream, new_word, ','))
        {
            matrix_from_file[row_num][col_num] = stod(new_word);
            col_num++;
        }
    }
    for (int i = mat_size; i < 3; i++)
    {
        getline(file, new_line);
    }
    return matrix_from_file;
}

void FileReader::DebugPrint(Properties props)
{
    cout << "MODEL PROPERTIES:\n"
            << "   Species number: " << props.SpeciesNumber << '\n'
            << "   Cutoff distance : " << props.CutoffDistance << '\n'
            << "   Sigma W:  " << props.SigmaW
            << "   Sigma M:  " << props.SigmaM
            << "         b:  " << props.b
            << "         d:  " << props.d
            << "         d': " << props.d_prime
            << "\n\n";
}

void FileReader::CheckKernels(Properties props)
{
    cout << "    Kernels test...\n";
    for (int i = 0; i < props.SpeciesNumber; i++)
    {
        for (int j = 0; j < props.SpeciesNumber; j++)
        {
            cout << "      W_" << i + 1 << "_" << j + 1 << ": integral = ";
            
            CalcType integral = 0;
            for (int x = 1 - props.MaxNumForW[i][j]; x < props.MaxNumForW[i][j] - 1; x += 2)
            {
                for (int y = 1 - props.MaxNumForW[i][j]; y < props.MaxNumForW[i][j] - 1; y += 2)
                {
                    integral += props.W(i, j)[abs(x + 1)][abs(y + 1)];
                }
            }
            integral *= pow(props.KernelsGridStep, 2);
            cout << integral;
            assert (abs(integral - 1) < EPSILON);
            cout << ".  Pass!\n";
        }
    }

    for (int i = 0; i < props.SpeciesNumber; i++)
    {
        cout << "      M_" << i + 1 << ":   integral = ";
            
        CalcType integral = 0;
        for (int x = 1 - props.MaxNumForM[i]; x < props.MaxNumForM[i] - 1; x += 2)
        {
            for (int y = 1 - props.MaxNumForM[i]; y < props.MaxNumForM[i] - 1; y += 2)
            {
                integral += props.M(i)[abs(x + 1)][abs(y + 1)];
            }
        }
        integral *= pow(props.KernelsGridStep, 2);
        cout << integral;
        assert (abs(integral - 1) < EPSILON);
        cout << ".  Pass!\n";
    }
    cout << "    Test complete!\n\n";
}

FileReader::FileReader(string str) : filename(str) {}

Properties FileReader::GetProperties(bool debug_print_enabled)
{
    file.open(filename);

    int species = GetInt();
    
    getline(file, new_line);
    auto sW = GetMatrix(species);
    auto sM = GetVector(species);
    
    getline(file, new_line);
    auto b = GetVector(species);
    auto d = GetVector(species);
    auto dd = GetMatrix(species);
    file.close();

    auto properties = Properties::Generate(species, sW, sM, b, d, dd);
    if (debug_print_enabled)
    {
        DebugPrint(properties);
    }
    CheckKernels(properties);
    return properties;
}

Properties FileReader::GetWithoutSigmaW(
    CalcType sigmaW, 
    bool debug_print_enabled
) {
    file.open(filename);

    int species = GetInt();
    
    getline(file, new_line);
    Matrix sW(species, sigmaW);
    auto sM = GetVector(species);
    
    getline(file, new_line);
    getline(file, new_line);
    getline(file, new_line);
    auto b = GetVector(species);
    auto d = GetVector(species);
    auto dd = GetMatrix(species);
    file.close();

    auto properties = Properties::Generate(species, sW, sM, b, d, dd);
    if (debug_print_enabled)
    {
        DebugPrint(properties);
    }
    return properties;
}

Properties FileReader::GetWithoutSigmaM(
    CalcType sigmaM, 
    bool debug_print_enabled
) {
    file.open(filename);

    int species = GetInt();
    
    getline(file, new_line);
    auto sW = GetMatrix(species);
    Vector sM(species, sigmaM);
    
    getline(file, new_line);
    auto b = GetVector(species);
    auto d = GetVector(species);
    auto dd = GetMatrix(species);
    file.close();

    auto properties = Properties::Generate(species, sW, sM, b, d, dd);
    if (debug_print_enabled)
    {
        DebugPrint(properties);
    }
    return properties;
}