#pragma once
#include <../include/runtime/usings.h>
#include <interpret/parser/Scope.h>
#include <interpret/parser/ASTNode.h>
class Interpreter {
	private:
	Scope* scope;
	public:
	Interpreter();
	void interpret(ASTNode*);
	Object evaluate(ASTNode*);
	Object evaluateForType(const String&, ASTNode*);
	Object evaluateBinaryExpression(BinaryExpressionNode*);
	[[nodiscard]] Scope* getScope();
};