#pragma once
#include "TokenType.h"
#include "usings.h"
class Token {
	private:
	TokenType type;
	String value;
	int lineNumber;
	int columnNumber;
	public:
	Token(TokenType type, String value, int lineNumber, int columnNumber) : type(type), value(value), lineNumber(lineNumber), columnNumber(columnNumber) { }
	TokenType getType() const { return type; }
	String getValue() { return value; }
	int getLineNumber() const { return lineNumber; }
	int getColumnNumber() const { return columnNumber; }
};
static inline std::ostream& operator<<(std::ostream& os, Token& token) {
	os << "Token[type=" << token.getType() << ", value='" << token.getValue() << "', line=" << token.getLineNumber() << ", column=" << token.getColumnNumber() << "]";
	return os; 
}