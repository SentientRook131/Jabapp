#include <Interpreter.h>
#include <iostream>
#include "Lexer.h"
#include "Parser.h"

int main() {
	Lexer lexer("int x = 10;");
	List<Token> tokens = lexer.tokenize();
	Parser parser(tokens);
	for (Token token : tokens) {
		std::cout << token << "\n";
	}
	Interpreter interpreter;
	ASTNode n = parser.parse();
	interpreter.interpret(&n);
	return 0;
}
