#include "ASTNode.h"
#include <memory>

NumberNode::NumberNode(long double obj) {
	if (isNumberType(obj)) {
		this->value = obj;
	}
}
long double* NumberNode::getValue() { return &value; }
Object* NumberNode::evaluate() { return new Object(value); }
static inline std::ostream& operator<<(std::ostream& os, NumberNode& n) {
	os << "NumberNode{value='" << n.evaluate() << "'}";
	return os;
}
IdentifierNode::IdentifierNode(String name) {
	this->name = name;
}
String IdentifierNode::getName() { return name; }
Object* IdentifierNode::evaluate() { return nullptr; }
static inline std::ostream& operator<<(std::ostream& os, IdentifierNode& n) {
	os << "IdentifierNode{name='" << n.getName() << "'}";
	return os;
}
StringNode::StringNode(String value) { this->value = value; }
String* StringNode::getValue() { return &value; }
Object* StringNode::evaluate() { return new Object(value); }
static inline std::ostream& operator<<(std::ostream& os, StringNode& n) {
	os << "StringNode{value='" << n.getValue() << "'}";
	return os;
}
IfNode::IfNode(ASTNode* condition, ASTNode* body, List<ASTNode> branches) {
	this->condition = condition;
	this->body = body;
	this->branches = branches;
}
ASTNode* IfNode::getCondition() { return condition; }
ASTNode* IfNode::getBody() { return body; }
List<ASTNode> IfNode::getBranches() { return branches; }
static inline std::ostream& operator<<(std::ostream& os, IfNode& n) {
	os << "IfNode{condition=" << n.getCondition() << ", body=" << n.getBody() << ", branches=" << n.getBranches() <<  "}";
	return os;
}
Object* IfNode::evaluate() { return nullptr; }
ElseNode::ElseNode(ASTNode* body) { this->body = body; }
ASTNode* ElseNode::getBody() { return body; }
static inline std::ostream& operator<<(std::ostream& os, ElseNode& n) {
	os << "ElseNode{body=" << n.getBody() << "}";
	return os;
}
Object* ElseNode::evaluate() { return nullptr; }
BlockNode::BlockNode(List<ASTNode> statements) { this->statements = statements; }
List<ASTNode> BlockNode::getStatements() { return statements; }
static inline std::ostream& operator<<(std::ostream& os, BlockNode& n) {
	os << "BlockNode{statements=" << n.getStatements() << "}";
	return os;
}
Object* BlockNode::evaluate() { return nullptr; }
BinaryExpressionNode::BinaryExpressionNode(ASTNode* left, String operator__, ASTNode* right) {
	this->left = left;
	this->operator__ = operator__;
	this->right = right;
}
ASTNode* BinaryExpressionNode::getLeft() { return left; }
String BinaryExpressionNode::getOperator() { return operator__; }
ASTNode* BinaryExpressionNode::getRight() { return right; }
Object* BinaryExpressionNode::evaluate() {
	Object leftValue = left->evaluate();
	Object rightValue = right->evaluate();
	if (operator__ == "+") {
		if (leftValue.type() == typeid(String) || rightValue.type() == typeid(String)) {
			std::stringstream stream;
			stream << leftValue << rightValue;
			return new Object(stream.str());
		}
		return new Object(std::any_cast<long double>(leftValue) + std::any_cast<long double>(rightValue));
	} else if (operator__ == "-") {
		return new Object(std::any_cast<long double>(leftValue) - std::any_cast<long double>(rightValue));
	} else if (operator__ == "*") {
		return new Object(std::any_cast<long double>(leftValue) * std::any_cast<long double>(rightValue));
	} else if (operator__ == "/") {
		return new Object(std::any_cast<long double>(leftValue) / std::any_cast<long double>(rightValue));
	}
	return nullptr;
}
static inline std::ostream& operator<<(std::ostream& os, BinaryExpressionNode& n) {
	os << "BinaryExpressionNode{left=" << n.getLeft() << ", operator=" << n.getOperator() << ", right=" << n.getRight() << "}";
	return os;
}
FunctionNode::FunctionNode(String functionName, List<ASTNode> arguments) {
	this->functionName = functionName;
	this->arguments = arguments;
}
String FunctionNode::getFunctionName() { return functionName; }
List<ASTNode> FunctionNode::getArguments() { return arguments; }
static inline std::ostream& operator<<(std::ostream& os, FunctionNode& n) {
	os << "FunctionNode{functionName='" << n.getFunctionName() << "', arguments=" << n.getArguments() << "}";
	return os;
}
Object* FunctionNode::evaluate() { return nullptr; }
AssignmentNode::AssignmentNode(String variableName, ASTNode* value) {
	this->variableName = variableName;
	this->value = value;
}
String AssignmentNode::getVariableName() { return variableName; }
ASTNode* AssignmentNode::getValue() { return value; }
static inline std::ostream& operator<<(std::ostream& os, AssignmentNode& n) {
	os << "AssignmentNode{variableName='" << n.getVariableName() << "', value=" << n.getValue() << "}";
	return os;
}
Object* AssignmentNode::evaluate() { return nullptr; }
VariableNode::VariableNode(String name, String type, Object* value) {
	this->name = name;
	this->type = type;
	this->value = value;
}
String VariableNode::getName() { return name; }
String VariableNode::getType() { return type; }
Object* VariableNode::getValue() { return value; }
Object* VariableNode::evaluate() { return value; }