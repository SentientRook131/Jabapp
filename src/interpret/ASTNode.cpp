#include <memory>
#include <runtime/usings.h>
#include <interpret/lexer/Token.h>
#include <interpret/parser/ASTNode.h>

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
IdentifierNode::IdentifierNode(const String &name) {
	this->name = name;
}
String IdentifierNode::getName() { return name; }
Object* IdentifierNode::evaluate() { return nullptr; }
static inline std::ostream& operator<<(std::ostream& os, IdentifierNode& n) {
	os << "IdentifierNode{name='" << n.getName() << "'}";
	return os;
}
StringNode::StringNode(const String &value) { this->value = value; }
String* StringNode::getValue() { return &value; }
Object* StringNode::evaluate() { return new Object(value); }
static inline std::ostream& operator<<(std::ostream& os, StringNode& n) {
	os << "StringNode{value='" << n.getValue() << "'}";
	return os;
}
IfNode::IfNode(ASTNode* condition, ASTNode* body, const List<ASTNode> &branches) {
	this->condition = condition;
	this->body = body;
	this->branches = branches;
}
ASTNode* IfNode::getCondition() const { return condition; }
ASTNode* IfNode::getBody() const { return body; }
List<ASTNode> IfNode::getBranches() { return branches; }
static std::ostream& operator<<(std::ostream& os, IfNode& n) {
	os << "IfNode{condition=" << n.getCondition() << ", body=" << n.getBody() << ", branches=" << n.getBranches() <<  "}";
	return os;
}
Object* IfNode::evaluate() { return nullptr; }
ElseNode::ElseNode(ASTNode* body) { this->body = body; }
ASTNode* ElseNode::getBody() const { return body; }
static std::ostream& operator<<(std::ostream& os, ElseNode& n) {
	os << "ElseNode{body=" << n.getBody() << "}";
	return os;
}
Object* ElseNode::evaluate() { return nullptr; }
BlockNode::BlockNode(const List<ASTNode> &statements) { this->statements = statements; }
List<ASTNode> BlockNode::getStatements() { return statements; }
static inline std::ostream& operator<<(std::ostream& os, BlockNode& n) {
	os << "BlockNode{statements=" << n.getStatements() << "}";
	return os;
}
Object* BlockNode::evaluate() { return nullptr; }
BinaryExpressionNode::BinaryExpressionNode(ASTNode* left, const String &operator_, ASTNode* right) {
	this->left = left;
	this->operator__ = operator_;
	this->right = right;
}
ASTNode* BinaryExpressionNode::getLeft() const { return left; }
String BinaryExpressionNode::getOperator() { return operator__; }
ASTNode* BinaryExpressionNode::getRight() const { return right; }
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
FunctionNode::FunctionNode(const String &functionName, const List<ASTNode> &arguments) {
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
AssignmentNode::AssignmentNode(const String &variableName, ASTNode* value) {
	this->variableName = variableName;
	this->value = value;
}
String AssignmentNode::getVariableName() { return variableName; }
ASTNode* AssignmentNode::getValue() const { return value; }
static inline std::ostream& operator<<(std::ostream& os, AssignmentNode& n) {
	os << "AssignmentNode{variableName='" << n.getVariableName() << "', value=" << n.getValue() << "}";
	return os;
}
Object* AssignmentNode::evaluate() { return nullptr; }
VariableNode::VariableNode(const String &name, const String &type, Object* value) {
	this->name = name;
	this->type = type;
	this->value = value;
}
String VariableNode::getName() { return name; }
String VariableNode::getType() { return type; }
Object* VariableNode::getValue() const { return value; }
Object* VariableNode::evaluate() { return value; }