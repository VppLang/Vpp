//Description: This is the header file that handles the contains the expressions for the syntax tree
//Author: RK-Codings

#pragma once

#include <string>
#include "Token.hpp"

namespace parser
{
    struct Expression {};

    struct Literal : public Expression
    {
    public:
        lexer::Token type;
        Literal(lexer::Token type) : type(type) {}
    };

    struct Grouping : public Expression
    {
    public:
    	lexer::Token symbol_beginning, symbol_end;
        std::string expression;
        Grouping(lexer::Token symbol_beginning, std::string expression, lexer::Token symbol_end) : symbol_beginning(symbol_beginning), expression(expression), symbol_end(symbol_end) {}
    };

    struct Unary : public Expression //Contains a prefix and expression. For example -a (negated).
    {
    public:
        token::Token prefix;
        std::string expression;

        Unary(token::Token prefix, std::string expression) : prefix(prefix), expression(expression) {}
    };

    struct Binary : public Expression //Two expressions and an operator. For example a+b.
    {
    public:
        std::string left, right;
        lexer::Token operator;

        Binary(std::string left, lexer::Token operator, std::string right) : left(left), operator(operator), right(right) {}
    };

    struct Operator : public Expression
    {
    public:
        lexer::Token symbol;
        Operator(lexer::Token symbol) : symbol(symbol) {}
    };
}