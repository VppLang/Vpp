#include <string>

struct Token
{
  public:
    std::string type;
    Token(std::string type) : type(type) {}
};
