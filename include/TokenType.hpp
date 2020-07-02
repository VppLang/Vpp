#pragma once

#include <string>
#include <array>
#include <iostream>

namespace VPP
{
	enum class TokenType
	{
		INVALID = 0,

		// Single character tolkiens
		LEFT_PAREN, RIGHT_PAREN, 
		LEFT_BRACE, RIGHT_BRACE,
		LEFT_CURLYBRACE, RIGHT_CURLYBRACE,
		COMMA, DOT, SEMICOLON, FSLASH, STAR,
		PLUS, PLUS_PLUS,
		MINUS, MINUS_MINUS,

		// Equality J R.R Tolkiens
		EQUAL, EQUAL_EQUAL, BANG, BANG_EQUAL, 
		GREATER, GREATER_EQUAL,
		LESS, LESS_EQUAL,


		// Lit literals

		IDENTIFIER, STRING, NUMBER,

		// Keywords
		AND, IF, OR, ELSE, ELIF, FOR, 
		WHILE, BREAK, RETURN, TRUE, FALSE,  
		CLASS, THIS, FUNC, ZIL, PRINT, 
	    VAR, STAT, DYNAM, 
		EndOfFile 

	};

	std::string convertToString(TokenType type);

}
