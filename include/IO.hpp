// To load and store files

#pragma once

#include <string>
#include <vector>

namespace io
{
    using std::vector;
    using std::string;

    extern string file_name;
    extern vector<string> lines; // stores the lines of the input file
    string loadFile(const char* p_fileName);
}
