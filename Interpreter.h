#pragma once
#include "Scope.h"
#include "usings.h"
#include "ASTNode.h"

class Interpreter {
	private:
	Scope* scope;
	public:
	Interpreter();
	void interpret(ASTNode*);
	Object evaluate(ASTNode*);
	Object evaluateForType(String, ASTNode*);
	Object evaluateBinaryExpression(BinaryExpressionNode*);
	Scope* getScope();
};