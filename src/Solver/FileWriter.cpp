#include <iostream>
#include <cassert>
#include "FileWriter.hpp"

using namespace std;


//_____________________________________________________FILE WRITER_________________________________________________________
FileWriter::FileWriter(string str) : filename(str) {}

void FileWriter::WritePlotData(
    string number, 
    string title, 
    vector<string> labels, 
    vector<Vector> points
) {
    assert (points.size() >= 2);
    assert (points.size() == labels.size());

    int number_of_plots = points.size() - 1;
    int number_of_points = points.at(0).size();
    for (int i = 1; i < points.size(); i++)
    {
        assert (points.at(i).size() == number_of_points);
    }
    file.open(filename, ios::out);
    file.clear();
    file << "Experiment" << ',' << number << '\n'
            << "Plot title" << ',' << title << '\n'
            << '\n'
            << "Number of" << ',' << number_of_plots << '\n'
            << "plots" << '\n'
            << '\n'
            << "Number of" << ',' << number_of_points << '\n'
            << "points" << '\n'
            << '\n'
            << labels.at(0);
    
    for (int i = 1; i < labels.size(); i++)
    {
        file << ',' << labels.at(i);
    }
    file << '\n';

    for (int point_num = 0; point_num < number_of_points; point_num++)
    {
        file << points.at(0)[point_num];
        for (int plot_num=1; plot_num<=number_of_plots; plot_num++)
        {
            file << ',' << points.at(plot_num)[point_num];
        }
        file << '\n';
    }
    file.close();
}