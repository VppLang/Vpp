// Author Martin Mast(codergopher)
// The Lexer turns a string of v++ into tokens
//
// To do: finish keywords list, add a debugger logger

#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "Token.hpp"

namespace lexer
{
	class Lexer
	{
	public:
		Lexer();

		void loadSource(const std::string& p_source);

		std::vector<Token>& getTokens();

	private:
		void addToken(TokenType p_type);
		void addToken(TokenType p_type, const std::string& p_literal);

		void scanAllTokens();
		void scanToken();

		char advance();
		bool isAtEnd() const;
		bool match(char p_char);
		char peek() const;
		char peekNext() const;

		void handleString();

		bool isDigit(char p_char) const;
		bool isAlpha(char p_char) const;
		bool isAlphaNumeric(char p_char) const { return isDigit(p_char) || isAlpha(p_char); }

		void handleNumber();
		void handleIdentifier();

		size_t getNumParsedChars() const { return current - start; }


		std::string source;
		std::vector<Token> tokens;

		unsigned start;
		size_t current;
		unsigned line;
        unsigned character_number;

		// eventually insert a Logger object here

		bool hasError;

	};
}
