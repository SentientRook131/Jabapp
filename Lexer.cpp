#include "Lexer.h"
char Lexer::currentChar() { return sourceCode[index]; }
bool Lexer::isEnd() { return index >= sourceCode.length(); }
void Lexer::advance() {
	if (currentChar() == '\n') {
		line++;
		column = 0;
	} else {
		column++;
	}
	index++;
}
Token Lexer::readNumber() {
	String number;
	int startColumn = column;
	while (!isEnd() && isExists(DIGITS, currentChar())) {
		number += currentChar();
		advance();
	}
	return Token(TokenType::NUMBER, number, line, startColumn);
}
bool Lexer::isKeyword(String value) { return isExists<String>(keywords, value); }
Token Lexer::readIdentitifierOrKeyword() {
	String identifier;
	int startColumn = column;
	while (!isEnd() && isExists(IDENTIFIER_PART, currentChar())) {
		identifier += currentChar();
		advance();
	}
	TokenType type = isKeyword(identifier) ? TokenType::KEYWORD : TokenType::IDENTIFIER;
	return Token(type, identifier, line, startColumn);
}
Token Lexer::readString() {
	String string;
	int startColumn = column;
	advance();
	while (!isEnd() && currentChar() != '"') {
		if (currentChar() == '\\') {
			advance();
			if (!isEnd()) {
				string += currentChar();
			}
		} else {
			string += currentChar();
		}
		advance();
	}
	if (!isEnd()) {
		advance();
	} else {
		std::cerr << "Unexpected Error: Unterminated string literal at line " << line << ", column " << startColumn << "\n";
	}
	return Token(TokenType::STRING, string, line, startColumn);
}
Token Lexer::readOperator() {
	String operator__;
	int startColumn = column;

	while (!isEnd() && isExists(OPERATORS, currentChar())) {
		operator__ += currentChar();
		advance();
	}

	return Token(TokenType::OPERATOR, operator__, line, startColumn);
}
List<Token> Lexer::tokenize() {
	List<Token> tokens;
	while (!isEnd()) {
		char c = currentChar();
		if (isExists(WHITESPACE, c)) {
			advance();
		} else if (isExists(DIGITS, c)) {
			tokens.push_back(readNumber());
		} else if (isExists(IDENTIFIER_START, c)) {
			//std::cout << "action riok\n";
			tokens.push_back(readIdentitifierOrKeyword());
		} else if (c == '"') {
			tokens.push_back(readString());
		} else if (isExists(OPERATORS, c)) {
			tokens.push_back(readOperator());
		} else if (isExists(SEPARATORS, c)) {
			tokens.push_back(Token(TokenType::SEPARATOR, &c, line, column));
			advance();
		}
	}
	tokens.push_back(Token(TokenType::EOF__, "", line, column));
	return tokens;
}