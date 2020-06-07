//Description: This file contains the parser which turns tokens into abstract syntax tree
//Author: RK-Coding

#pragma once

#include "ParserExpressions.hpp"
#include "ExpressionPrinter.hpp"
#include <iostream> //Debug
#include <vector>


namespace VPP
{
    class Parser
    {
    public:
        Expression* parse_tokens(std::vector<Token> tokens)
        {
            for (size_t i = 0; i < tokens.size(); i++)
            {
                if (tokens[i].getType() == TokenType::MINUS)
                {
                    if (i == 0 || tokens[i+1].getType() != TokenType::NUMBER || tokens[i+1].getType() != TokenType::RIGHT_PAREN)
                    {
                        std::vector<Token> right_side_tokens = tokens;
                        right_side_tokens.erase(right_side_tokens.begin() + i);

                        Unary* tree = new Unary(tokens[i], parse_tokens(right_side_tokens));

                        return (Expression*)tree;
                    }
                }

                if (tokens[i].getType() == TokenType::NUMBER)
                {
                    Literal* tree = new Literal(tokens[i]);

                    return (Expression*) tree;
                }

                //if (tokens[i].getType() == TokenType::STAR)
                //{
                //
                //}
            }

            return nullptr;
        }


    };
}
