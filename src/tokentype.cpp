#include "TokenType.hpp"

#include <array>
#include <string>

namespace token
{

	std::array<std::string, 47> tokenNames =
	{
		"INVALID",
		"left parenthesis",
		"right parenthesis",
		"left brace",
		"right brace",
		"left curlybrace",
		"right curlybrace",
		"comma",
		"dot",
		"semicolon",
		"forward slash",
		"star",
		"plus",
		"plus plus",
		"minus",
		"minus minus",
		"equal",
		"equal equal",
		"bang",
		"bang equal",
		"greater",
		"greater equal",
		"less",
		"less equal",
		"identifier",
		"string",
		"number",
		"and",
		"if",
		"or",
		"else",
		"elseif",
		"for",
		"while",
		"break",
		"return",
		"true",
		"false",
		"class",
		"this",
		"func",
		"zil",
		"print",
		"var",
		"stat",
		"dynam",
		"eof"
	};

	std::string convertToString(TokenType type)
	{
		return tokenNames.at(static_cast<int>(type));
	}

}