#include "Token.hpp"

#include <iostream>
#include <sstream>

namespace VPP
{

	Token::Token()
	:type(TokenType::INVALID),
	lexeme("empty lexeme"),
	literal("empty literal"),
	line(-1)
	{
	}

	Token::Token(TokenType p_type, const std::string& p_lexeme, const std::string& p_literal, int p_line)
	:type(p_type),
	lexeme(p_lexeme),
	literal(p_literal),
	line(p_line)
	{
	}
}
