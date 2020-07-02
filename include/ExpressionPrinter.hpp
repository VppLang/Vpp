//Description: This file prints Parser Expressions
//Author: RK-Coding

#pragma once

#include <iostream>
#include "ParserExpressions.hpp"

namespace VPP
{
    void print_expression(Expression* expression) 
    {
        std::cout << expression->get_string_form() << std::endl;
    }
}
