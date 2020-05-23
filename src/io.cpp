#include "IO.hpp"

std::string loadFile(std::string& p_fileName)
{
    std::ifstream inFile (p_fileName);
    std::ostringstream source;

    source << inFile.rdbuf();

    return source.str();  
}
