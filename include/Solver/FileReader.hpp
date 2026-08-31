#pragma once

#include <string>
#include <fstream>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Properties.hpp"


//_____________________________________________________FILE READER_________________________________________________________
class FileReader
{
    std::fstream file;
    std::string filename;
    std::string new_line;
    std::string new_word;

private:
    int GetInt();

    CalcType GetCalcType();

    Vector GetVector(int vec_size);

    Matrix GetMatrix(int mat_size);

    void DebugPrint(Properties props);

    void CheckKernels(Properties props);

public:
    FileReader(std::string str);

    Properties GetProperties(bool debug_print_enabled = false);

    Properties GetWithoutSigmaW(
        CalcType sigmaW, 
        bool debug_print_enabled = false
    );

    Properties GetWithoutSigmaM(
        CalcType sigmaM, 
        bool debug_print_enabled = false
    );
};