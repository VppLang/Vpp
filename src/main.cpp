#include <iostream>
#include <vector>

#include "IO.hpp"
#include "Lexer.hpp"
#include "Token.hpp"

#include "Parser.hpp"
#include "ParserExpressions.hpp"
#include "ExpressionPrinter.hpp"



int main()
{	
    // create the tokens
	lexer::Lexer lexer;
	lexer.loadSource(loadFile("examples/example.vpp"));
    std::vector<lexer::Token> tokens = lexer.getTokens();

    // parse the tokens
    parser::Parser parser;
    parser::Expression* e = parser.parse_tokens(tokens);

    parser::print_expression(e);

    delete e;

    return 0;
}



/*
int main()
{
    parser::Expression* e = new parser::Expression();
    print_expression(e);
}
*/