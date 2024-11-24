#pragma once
#include "usings.h"
#include "Variable.h"
#include "Function.h"

class Scope {
	private:
	Map<String, Variable*> variables;
	Map<String, Function*> functions;
	Scope* parentScope;
	public:
	static Scope* standardScope;
	Scope();
	Scope(Scope* parentScope);
	void defineVariable(String name, Variable* var);
	bool hasVariable(String name);
	void defineFunction(String name, Function* func);
	bool hasFunction(String name);
	Variable* getVariable(String name);
	Function* getFunction(String name);
};