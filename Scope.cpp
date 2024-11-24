#include "Scope.h"
Scope::Scope() { this->parentScope = standardScope; }
Scope::Scope(Scope* parentScope) { this->parentScope = parentScope; }
void Scope::defineVariable(String name, Variable* variable) {
	variables.insert(std::make_pair(name, variable));
}
bool Scope::hasVariable(String name) {
	if (variables.count(name) > 0) return true;
	return parentScope != nullptr && parentScope->hasVariable(name);
}
void Scope::defineFunction(String name, Function* function) {
	functions.insert(std::make_pair(name, function));
}
bool Scope::hasFunction(String name) {
	if (functions.count(name) > 0) return true;
	return parentScope != nullptr && parentScope->hasFunction(name);
}
Variable* Scope::getVariable(String name) { return variables[name]; }
Function* Scope::getFunction(String name) { return functions[name]; }
