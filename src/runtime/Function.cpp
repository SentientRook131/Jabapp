#include <runtime/object/Function.h>
#include <runtime/usings.h>
#include <interpret/parser/ASTNode.h>
#include "../interpret/Scope.cpp"
#include "../interpret/Variable.cpp"
#include "../interpret/Interpreter.cpp"
class Scope;

Function::Function(const Function& f) : name(f.name), parameters(f.parameters) {
	this->body = f.body;
	this->callback = f.callback;
	this->native = f.native;
}
Function::Function(const String &name, const List<String> &parameters, ASTNode* body) {
	this->name = name;
	this->parameters = parameters;
	this->body = body;
	this->callback = nullptr;
	native = false;
}
Function::Function(const String &name, const List<String> &parameters, FunctionCallBack* callback) {
	this->name = name;
	this->parameters = parameters;
	this->callback = callback;
	this->body = nullptr;
	native = true;
}
String Function::getName() {
	return name;
}
List<String> Function::getParameters() {
	return parameters;
}
ASTNode* Function::getBody() const {
	return body;
}
Object Function::call(const List<Object> &arguments, Interpreter* interpreter) {
	auto* functionScope = new Scope(interpreter->getScope());
	for (int i = 0; i < parameters.size();i++) {
		Object obj = parameters[i];
		functionScope->defineVariable(std::any_cast<String>(obj), new Variable(std::any_cast<String>(obj), "unknown", arguments[i]));
	}
	if (native) return callback->execute(arguments);
	return interpreter->evaluate(body);
}
Object Function::execute(const List<Object> &arguments) const {
	return callback->execute(arguments);
}
