#pragma once
#include <string>
#include <array>
#include "usings.h"
#include "Token.h"
#include "Toolkit.hpp"
#include "TokenType.h"

class Lexer {
	private:
	String sourceCode;
	int index = 0;
	int line = 1;
	int column = 0;
	String WHITESPACE = " \t\r\n";
	String DIGITS = "0123456789.";
	String IDENTIFIER_START = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	String IDENTIFIER_PART = IDENTIFIER_START + DIGITS;
	String OPERATORS = "+-*/=<>!&|";
	String SEPARATORS = "();,{}";
	Array<String, 12> keywords = { "if", "else", "for", "while", "int", "double", "float", "byte", "short", "bool", "char", "return" };
	char currentChar();
	bool isEnd();
	void advance();
	Token readNumber();
	bool isKeyword(String value);
	Token readIdentitifierOrKeyword();
	Token readString();
	Token readOperator();
	public:
	Lexer(String sourceCode) : sourceCode(sourceCode) { }
	List<Token> tokenize();
};