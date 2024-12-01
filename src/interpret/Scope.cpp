#include <interpret/parser/Scope.h>
#include <runtime/usings.h>
#include <runtime/object/Variable.h>
#include <runtime/object/Function.h>
Scope::Scope() { this->parentScope = standardScope; }
Scope::Scope(Scope* parentScope) { this->parentScope = parentScope; }
void Scope::defineVariable(const String& name, Variable* variable) {
	variables.insert(std::make_pair(name, variable));
}
bool Scope::hasVariable(const String& name) {
	if (variables.count(name) > 0) return true;
	return parentScope != nullptr && parentScope->hasVariable(name);
}
void Scope::defineFunction(const String& name, Function* function) {
	functions.insert(std::make_pair(name, function));
}
bool Scope::hasFunction(const String& name) {
	if (functions.count(name) > 0) return true;
	return parentScope != nullptr && parentScope->hasFunction(name);
}
Variable* Scope::getVariable(const String& name) { return variables[name]; }
Function* Scope::getFunction(const String& name) { return functions[name]; }
