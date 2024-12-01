#pragma once
#include "TokenType.h"
#include <usings.h>

#include <utility>
class Token {
	private:
	TokenType type;
	String value;
	int lineNumber;
	int columnNumber;
	public:
	Token(const TokenType type, String value, const int lineNumber, const int columnNumber) : type(type), value(std::move(value)), lineNumber(lineNumber), columnNumber(columnNumber) { }
	[[nodiscard]] TokenType getType() const { return type; }
	String getValue() { return value; }
	[[nodiscard]] int getLineNumber() const { return lineNumber; }
	[[nodiscard]] int getColumnNumber() const { return columnNumber; }
};
static std::ostream& operator<<(std::ostream& os, Token& token) {
	os << "Token[type=" << token.getType() << ", value='" << token.getValue() << "', line=" << token.getLineNumber() << ", column=" << token.getColumnNumber() << "]";
	return os; 
}