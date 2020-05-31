#include "IO.hpp"

std::string loadFile(const char* p_fileName)
{
    std::ifstream inFile (p_fileName);
    std::ostringstream source;

    source << inFile.rdbuf();

    return source.str();  
}
