// Author Martin Mast(codergopher)
// The Lexer turns a string of v++ into tokens
//
// To do: finish keywords list, add a debugger logger


#include <iostream>
#include <map>
#include <string>

#include "Lexer.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include "Logger.hpp"

namespace lexer
{

	static std::map<std::string, TokenType> sKeyWords = 
	{
		{"and", TokenType::AND},
		{"if", TokenType::IF},
		{"or", TokenType::OR},
		{"else", TokenType::ELSE},
		{"elif", TokenType::ELIF},
		{"for", TokenType::FOR},
		{"while", TokenType::WHILE},
		{"break", TokenType::BREAK},
		{"return", TokenType::RETURN},
		{"true", TokenType::TRUE},
		{"false", TokenType::FALSE},
		{"class", TokenType::CLASS},
		{"this", TokenType::THIS},
		{"func", TokenType::FUNC},
		{"zil", TokenType::ZIL},
		{"print", TokenType::PRINT},
		{"var", TokenType::VAR},
		{"stat", TokenType::STAT},
		{"dynam", TokenType::DYNAM}
	};

	Lexer::Lexer()
	:start(0),
	current(0),
	line(0),
    character_number(0),
	hasError(false)
	{
	}

	void Lexer::loadSource(const std::string& p_source)
	{
		source = p_source;
	}

	std::vector<Token>& Lexer::getTokens()
	{	
		scanAllTokens();
		return tokens;
	}

	char Lexer::advance()
	{
		auto curr = source.at(current);
		current++;

        if(curr == '\n')
        {
            character_number = 0;
        }
        else
        {
            ++character_number;
        }

		return curr;
	}

	void Lexer::addToken(TokenType p_type, const std::string& p_literal)
	{
		auto part = source.substr(start, getNumParsedChars());

		tokens.emplace_back(p_type, part, p_literal, line);
	}

	void Lexer::addToken(TokenType p_type)
	{
		addToken(p_type, "");
	}

	bool Lexer::isAtEnd() const
	{
		bool result = current >= source.size();
		return result;
	}

	bool Lexer::match(char p_char)
	{
		if (isAtEnd()) return false;

		if (source.at(current) != p_char)
			return false;

		current++;

		return true;
	}

	char Lexer::peek() const
	{
		if (isAtEnd()) return 0;

		return source.at(current);
	}

	char Lexer::peekNext() const
	{
		if (current + 1 >= source.size())
		{
			return '\0';
		}

		return source.at(current + 1);
	}

	void Lexer::handleString()
	{
		// if no " is found, carry on
		while (peek() != '"' && !isAtEnd())
		{
			if (peek() == '\n')
            {
                line++;
            }
			advance();
		}

		// we've got an open ", report error
		if (isAtEnd())
		{
			hasError = true;
			return;
		}

		advance();

		std::string value = source.substr(start + 1, getNumParsedChars() - 2);
		addToken(TokenType::STRING, value);

	}

	void Lexer::handleNumber()
	{
		while (isDigit(peek()))
		{
			advance();
		}

		if (peek() == '.' && isDigit(peekNext()))
		{
			advance();

			while (isDigit(peek()))
			{
				advance();
			}
		}

		std::string value = source.substr(start, getNumParsedChars());

		addToken(TokenType::NUMBER, value);
	}

	void Lexer::handleIdentifier()
	{
		while (isAlphaNumeric(peek()))
		{
			advance();
		}

		std::string text = source.substr(start, getNumParsedChars());

		auto result = sKeyWords.find(text);

		TokenType type = TokenType::IDENTIFIER;

		if (result != sKeyWords.end())
		{
			type = result->second;
		}

		addToken(type);
	}

	void Lexer::scanToken()
	{
		char c = advance();

		switch (c)
		{
            // single char lexemes
            case '(': addToken(TokenType::LEFT_PAREN); break;
            case ')': addToken(TokenType::RIGHT_PAREN); break;
            case '[': addToken(TokenType::LEFT_BRACE); break;
            case ']': addToken(TokenType::RIGHT_BRACE); break;
            case '{': addToken(TokenType::LEFT_CURLYBRACE); break;
            case '}': addToken(TokenType::RIGHT_CURLYBRACE); break;
            case ',': addToken(TokenType::COMMA); break;
            case '.': addToken(TokenType::DOT); break;
            case ';': addToken(TokenType::SEMICOLON); break;
            case '*': addToken(TokenType::STAR); break;

            // two char lexemes (could be 1 char too)
            case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
            case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
            case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
            case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
            case '+': addToken(match('+') ? TokenType::PLUS_PLUS : TokenType::PLUS); break;
            case '-': addToken(match('-') ? TokenType::MINUS_MINUS : TokenType::MINUS); break;

        	//comments
        	case '$':
        	{
        	    int nesting = 1;
                const auto line_start{line};
                const auto character_number_start{character_number};
        		while (nesting != 0 && !isAtEnd())
        		{
        			char last = advance();
        			// we've hit the end of the comment
        			if (last == '$')
        			{
        				nesting--;
        			}

        			else if (last == '\n')
        			{
        				line++;
        			}
        		}

				// it there was no closing $
    			if (nesting > 0)
    			{	
                    logger::Logger::get_instance()
                        .emplace_back
                        (
                            logger::LogType::error,
                            "Expected closing $ for comment",
                            line_start,
                            character_number_start
                        );
    				hasError = true;
    			}
	
        	}

    			break;

    		case ' ': 
    			break;
            case '\r': 
            	break;
            case '\t': 
                // Nobody wants whitespace as syntax. Looking at you, python!
            	break;

            case '\n':
                line++;
            	break;

            case '"':
                handleString();
            	break;

            default:
            	if (isDigit(c))
            	{
            		handleNumber();
            	}
            	else if (isAlpha(c))
            	{
            		handleIdentifier();
            	}
            	else
            	{
            		hasError = true;
                    logger::Logger::get_instance()
                        .emplace_back
                        (
                            logger::LogType::error,
                            "Unexpected character " + c,
                            line
                        );
            	}
            	break;
        }
	}


	bool Lexer::isDigit(char p_char) const
	{
		return p_char >= '0' && p_char <= '9';
	}

	bool Lexer::isAlpha(char p_char) const
	{
		return (p_char >= 'a' && p_char <= 'z') ||
		       (p_char >= 'A' && p_char <= 'Z') ||
		       (p_char == '_');
	}


	void Lexer::scanAllTokens()
	{
		line = 1;
        character_number = 0;
		current = 0;
		tokens.clear();

		while(! isAtEnd())
		{
			start = current;
			scanToken();
		}

		tokens.emplace_back(TokenType::EndOfFile, "", "", line);

	}
}
