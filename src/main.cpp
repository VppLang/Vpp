#include <iostream>
#include <vector>

#include "IO.hpp"
#include "Lexer.hpp"
#include "Token.hpp"

#include "Parser.hpp"
#include "ParserExpressions.hpp"
#include "ExpressionPrinter.hpp"

#include "Logger.hpp"


int main()
{	
    // create the tokens
	lexer::Lexer lexer;
	lexer.loadSource(io::loadFile("examples/example.vpp"));
    std::vector<lexer::Token> tokens = lexer.getTokens();

    // parse the tokens
    parser::Parser parser;
    parser::Expression* e = parser.parse_tokens(tokens);

    parser::print_expression(e);

    // test logs
    {
        logger::Logger::get_instance().emplace_back
            (
                logger::LogType::error, // log type: [error / warning / note]
                "dummy error",          // log message
                1,                      // line number: optional; 1-based indexing
                1                       // character number: optional; 1-based indexing
            );
        logger::Logger::get_instance().emplace_back
            (
                logger::LogType::error,
                "dummy error without line number and character number"
            );
        logger::Logger::get_instance().emplace_back
            (
                logger::LogType::warning,
                "dummy warning",
                52,
                1
            );
        logger::Logger::get_instance().emplace_back
            (
                logger::LogType::note,
                "dummy note without character number",
                3
            );
    }

    // printing the logs
    std::cerr << logger::Logger::get_instance();

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
