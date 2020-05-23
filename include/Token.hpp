#pragma once

#include "TokenType.hpp"

namespace lexer
{
	
	class Token
	{
	public:
		Token();
		Token(TokenType p_type, const std::string& p_lexeme, const std::string& p_literal, int p_line);

		TokenType getType() const { return type; }

		const std::string& getLexeme() const { return lexeme; }

		const std::string& getLiteral() const { return literal; }

		int getLine() const { return line; }

	private:
		TokenType type;
		std::string lexeme;
		std::string literal;

		int line;
	};

}
