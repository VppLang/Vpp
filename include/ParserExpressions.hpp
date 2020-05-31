//Description: This is the header file that handles the contains the expressions for the syntax tree
//Author: RK-Coding

#pragma once

#include <string>
#include "Token.hpp"

namespace parser
{
    struct Expression 
    {
    public:
        virtual ~Expression() {}
        virtual std::string get_string_form() { return "Empty Expression"; }
    };

    struct Literal : public Expression
    {
    public:
        lexer::Token type;
        
        Literal(lexer::Token type) : type(type) {}
        

        std::string get_string_form() override { return "Literal(" + type.getLiteral() + ")"; }
    };

    struct Grouping : public Expression
    {
    public:
        lexer::Token symbol_beginning, symbol_end;
        Expression* expression;
        ~Grouping();
        Grouping(lexer::Token symbol_beginning, Expression* expression, lexer::Token symbol_end) : symbol_beginning(symbol_beginning),  symbol_end(symbol_end), expression(expression) {}
    };

    struct Unary : public Expression //Contains a prefix and expression. For example -a (negated).
    {
    public:
        lexer::Token prefix;
        Expression* expression;

        Unary(lexer::Token prefix, Expression* expression) : prefix(prefix), expression(expression) {}
        ~Unary() {}

        std::string get_string_form() override { return "Unary(" + prefix.getLexeme() + ", " + expression->get_string_form() + ")"; }
    };

    struct Binary : public Expression //Two expressions and an operator. For example a+b.
    {
    public:
        Expression* left;
        Expression* right;
        lexer::Token operator_;
        ~Binary();
        Binary(Expression* left, lexer::Token operator_, Expression* right) : left(left), right(right), operator_(operator_) {}
    };

    struct Operator_ : public Expression
    {
    public:
        lexer::Token symbol;
        ~Operator_();
        Operator_(lexer::Token symbol) : symbol(symbol) {}
    };
}