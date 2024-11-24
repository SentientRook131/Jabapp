#include <iostream>
#include "Lexer.h"
#include "Toolkit.hpp"
int main() {
	Lexer lexer("int x = 10;");
	List<Token> tokens = lexer.tokenize();
	for (Token token : tokens) {
		std::cout << token << "\n";
	}
	return 0;
}