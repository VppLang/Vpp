//Description: This file contains the parser which turns tokens into abstract syntax tree
//Author: RK-Coding

#pragma once

#include "ParserExpressions.hpp"
#include "ExpressionPrinter.hpp"
#include <iostream> //Debug
#include <vector>


namespace parser
{
    class Parser
    {
    public:
        Expression* parse_tokens(std::vector<lexer::Token> tokens)
        {
            for (size_t i = 0; i < tokens.size(); i++)
            {
                if (tokens[i].getType() == lexer::TokenType::MINUS)
                {
                    if (i == 0 || tokens[i+1].getType() != lexer::TokenType::NUMBER || tokens[i+1].getType() != lexer::TokenType::RIGHT_PAREN)
                    {
                        std::vector<lexer::Token> right_side_tokens = tokens;
                        right_side_tokens.erase(right_side_tokens.begin() + i);

                        Unary* tree = new Unary(tokens[i], parse_tokens(right_side_tokens));

                        return (Expression*)tree;
                    }
                }

                if (tokens[i].getType() == lexer::TokenType::NUMBER)
                {
                    Literal* tree = new Literal(tokens[i]);

                    return (Expression*) tree;
                }

                //if (tokens[i].getType() == lexer::TokenType::STAR)
                //{
                //
                //}
            }

            return nullptr;
        }


    };
}