#pragma once
#include "usings.h"
#include "ASTNode.h"
#include "FunctionCallBack.h"
#include "Interpreter.h"

class Function {
	private:
	String name;
	List<String> parameters;
	ASTNode* body;
	FunctionCallBack* callback;
	public:
	Function() = default;
	Function(const Function&);
	Function(String, List<String>, ASTNode*, FunctionCallBack*);
	String getName();
	List<String> getParameters();
	ASTNode* getBody();
	Object call(List<Object>, Interpreter*);
	Object execute(List<Object>);
};