#include <interpret/Interpreter.h>
#include <runtime/object/Function.h>
#include <runtime/object/Variable.h>

Interpreter::Interpreter() { this->scope = new Scope(); }
void Interpreter::interpret(ASTNode* node) {
	evaluate(node);
}
Object Interpreter::evaluate(ASTNode* node) {
	if (instanceof<NumberNode, ASTNode>(node)) {
		return dynamic_cast<NumberNode *>(node)->getValue();
	} else if (instanceof<StringNode, ASTNode>(node)) {
		return dynamic_cast<StringNode *>(node)->getValue();
	} else if (instanceof<IdentifierNode, ASTNode>(node)) {
		String name = dynamic_cast<IdentifierNode *>(node)->getName();
		return scope->hasVariable(name) ? scope->getVariable(name)->getValue() : nullptr;
	} else if (instanceof<FunctionNode, ASTNode>(node)) {
		auto* n = dynamic_cast<FunctionNode *>(node);
		Function* function = scope->getFunction(n->getFunctionName());
		if (function == nullptr) return nullptr;
		List<Object> evaluatedArgs;
		for (ASTNode& arg : n->getArguments()) {
			Object evaluatedArg = evaluate(&arg);
			evaluatedArgs.push_back(evaluatedArg);
		}
		Interpreter* er = this;
		return function->call(evaluatedArgs, er);
	} else if (instanceof<BinaryExpressionNode, ASTNode>(node)) {
		return evaluateBinaryExpression(dynamic_cast<BinaryExpressionNode *>(node));
	} else if (instanceof<AssignmentNode, ASTNode>(node)) {
		auto* assignmentNode = dynamic_cast<AssignmentNode *>(node);
		Object value = evaluate(assignmentNode->getValue());
		scope->defineVariable(assignmentNode->getVariableName(), new Variable(assignmentNode->getVariableName(), "unknown", value));
		return value;
	} else if (instanceof<BlockNode, ASTNode>(node)) {
		for (ASTNode& statement : dynamic_cast<BlockNode *>(node)->getStatements()) {
			evaluate(&statement);
		}
		return nullptr;
	} else if (instanceof<VariableNode, ASTNode>(node)) {
		auto* v = dynamic_cast<VariableNode *>(node);
		if (!scope->hasVariable(v->getName())) {
			scope->defineVariable(v->getName(), new Variable(v->getName(), v->getType(), evaluateForType(v->getType(), std::any_cast<ASTNode>(v->getValue()))));
		}
	} else if (instanceof<IfNode, ASTNode>(node)) {
		auto* v = dynamic_cast<IfNode *>(node);
		bool condition = std::any_cast<bool>(v->getCondition());
		if (condition) {
			interpret(v->getBody());
		} else {
			for (ASTNode& v2 : v->getBranches()) {
				if (instanceof<IfNode, ASTNode>(&v2)) {
					auto* v3 = dynamic_cast<IfNode *>(&v2);
					interpret(v3);
				} else if (instanceof<ElseNode, ASTNode>(&v2)) {
					auto* v3 = dynamic_cast<ElseNode *>(&v2);
					interpret(v3);
					break;
				}
			}
		}
		return condition;
	} else if (instanceof<ElseNode, ASTNode>(node)) {
		auto* v = dynamic_cast<ElseNode *>(node);
		return evaluate(v->getBody());
	}
	return false;
}
Object Interpreter::evaluateForType(const String& type, ASTNode* value) {
	Object o = evaluate(value);
	if (type == "int") return std::any_cast<int>(o);
	else if (type == "float") return std::any_cast<float>(o);
	else if (type == "double") return std::any_cast<double>(o);
	else if (type == "short") return std::any_cast<short>(o);
	else if (type == "long") return std::any_cast<long long>(o);
	else if (type == "string") return std::any_cast<String>(o);
	return false;
}
Object Interpreter::evaluateBinaryExpression(BinaryExpressionNode* node) {
	Object leftValue = evaluate(node->getLeft());
	Object rightValue = evaluate(node->getRight());
	if (instanceof<BinaryExpressionNode, ASTNode>(std::any_cast<ASTNode*>(leftValue))) leftValue = (BinaryExpressionNode*) std::any_cast<ASTNode*>(leftValue);
	if (instanceof<BinaryExpressionNode, ASTNode>(std::any_cast<ASTNode*>(rightValue))) rightValue = (BinaryExpressionNode*) std::any_cast<ASTNode*>(rightValue);
	if (instanceof<NumberNode, ASTNode>(std::any_cast<ASTNode*>(leftValue))) leftValue = ((NumberNode*) std::any_cast<ASTNode*>(leftValue))->getValue();
	if (instanceof<NumberNode, ASTNode>(std::any_cast<ASTNode*>(rightValue))) rightValue = ((NumberNode*) std::any_cast<ASTNode*>(rightValue))->getValue();
	if (node->getOperator() == "+") {
		if (leftValue.type() == typeid(String) || rightValue.type() == typeid(String)) {
			return std::any_cast<String>(leftValue) + std::any_cast<String>(rightValue);
		} else {
			return (std::any_cast<long double>(leftValue) + std::any_cast<long double>(rightValue));
		}
	} else if (node->getOperator() == "-") {
		return (std::any_cast<long double>(leftValue) - std::any_cast<long double>(rightValue));
	} else if (node->getOperator() == "*") {
		return (std::any_cast<long double>(leftValue) * std::any_cast<long double>(rightValue));
	} else if (node->getOperator() == "/") {
		return (std::any_cast<long double>(leftValue) / std::any_cast<long double>(rightValue));
	} else if (node->getOperator() == ">=") {
		return (std::any_cast<long double>(leftValue) >= std::any_cast<long double>(rightValue));
	} else if (node->getOperator() == ">") {
		return (std::any_cast<long double>(leftValue) > std::any_cast<long double>(rightValue));
	} else if (node->getOperator() == "==") {
		return (std::any_cast<long double>(leftValue) == std::any_cast<long double>(rightValue));
	} else if (node->getOperator() == "<") {
		return (std::any_cast<long double>(leftValue) < std::any_cast<long double>(rightValue));
	} else if (node->getOperator() == "<=") {
		return (std::any_cast<long double>(leftValue) <= std::any_cast<long double>(rightValue));
	}
	return false;
}
Scope* Interpreter::getScope() {
	return scope;
}
