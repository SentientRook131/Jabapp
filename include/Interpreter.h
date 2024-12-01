#pragma once
#include <usings.h>
#include <Scope.h>
#include <ASTNode.h>
class Interpreter {
	Scope* scope;
	public:
	Interpreter();
	void interpret(ASTNode*);
	Object evaluate(ASTNode*);
	Object evaluateForType(const String&, ASTNode*);
	Object evaluateBinaryExpression(BinaryExpressionNode*);
	[[nodiscard]] Scope* getScope();
};