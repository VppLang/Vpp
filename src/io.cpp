#include "IO.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace VPP
{
    using std::vector;
    using std::string;
    using std::ifstream;
    using std::stringstream;
    using std::getline;

    string file_name;

    vector<string> lines;

    string loadFile(const char* p_fileName)
    {
        file_name = p_fileName;

        ifstream inFile (p_fileName);
        stringstream source;
        source << inFile.rdbuf();

        const auto source_string{source.str()};

        // fills up the lines vector
        string line;
        while(getline(source, line))
        {
            lines.emplace_back(line);
        }

        return source_string;
    }
}
