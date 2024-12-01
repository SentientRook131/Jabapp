#pragma once
#include "FunctionCallBack.h"
#include <interpret/parser/ASTNode.h>
#include <optional>
#include <interpret/Interpreter.h>

class Function {
	private:
	String name;
	List<String> parameters;
	ASTNode* body{};
	FunctionCallBack* callback{};
	bool native{};
	public:
	Function() = default;
	Function(const Function&);
	Function(const String &, const List<String> &, ASTNode*);
	Function(const String &, const List<String> &, FunctionCallBack*);
	String getName();
	List<String> getParameters();
	[[nodiscard]] ASTNode* getBody() const;
	Object call(const List<Object> &, Interpreter*);
	[[nodiscard]] Object execute(const List<Object> &) const;
};