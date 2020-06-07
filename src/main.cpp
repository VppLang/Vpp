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
    // create the logger
    VPP::Logger logger;

    // create the tokens
	VPP::Lexer lexer(logger);
	lexer.loadSource(VPP::loadFile("examples/example.vpp"));
    std::vector<VPP::Token> tokens = lexer.getTokens();

    // parse the tokens
    VPP::Parser parser;
    VPP::Expression* e = parser.parse_tokens(tokens);

    VPP::print_expression(e);

    // test logs
    {
        logger.emplace_back
            (
                VPP::LogType::error,    // log type: [error / warning / note]
                "dummy error",          // log message
                1,                      // line number: optional; 1-based indexing
                1                       // character number: optional; 1-based indexing
            );
        logger << VPP::Log
            { /* {/( */
                VPP::LogType::error,
                "dummy error logged using '<<'",
                1,
                5
            } /* }/) */ ;
        logger << VPP::Log
            (
                VPP::LogType::error,
                "dummy error without line number and character number"
            );
        logger.emplace_back
            (
                VPP::LogType::warning,
                "dummy warning",
                52,
                1
            );
        logger.emplace_back
            (
                VPP::LogType::note,
                "dummy note without character number",
                3
            );
    }

    // printing the logs
    std::cerr << logger;

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
