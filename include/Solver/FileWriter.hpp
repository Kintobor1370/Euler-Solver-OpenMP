#pragma once

#include <string>
#include <fstream>
#include "Vector.hpp"


//_____________________________________________________FILE WRITER_________________________________________________________
class FileWriter
{
    std::fstream file;
    std::string filename;

public:
    FileWriter(std::string str);

    void WritePlotData(
        std::string number, 
        std::string title, 
        std::vector<std::string> labels, 
        std::vector<Vector> points
    );
};