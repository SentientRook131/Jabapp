#pragma once
#include <../include/runtime/usings.h>
#include <runtime/object/Variable.h>

class Function;

class Scope {
	Map<String, Variable*> variables;
	Map<String, Function*> functions;
	Scope* parentScope;
	public:
	static inline Scope* standardScope;
	Scope();
	explicit Scope(Scope* parentScope);
	void defineVariable(const String& name, Variable* var);
	bool hasVariable(const String& name) const;
	void defineFunction(const String& name, Function* func);
	bool hasFunction(const String& name) const;
	Variable* getVariable(const String& name);
	Function* getFunction(const String& name);
};