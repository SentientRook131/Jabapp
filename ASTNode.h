#pragma once
#include "usings.h"
#include <sstream>
class ASTNode {
	protected:
	String ASTName = "ASTNode";
	public:
	ASTNode() = default;
	virtual String& getASTName() { return ASTName; }
	virtual std::ostream& operator<<(const std::ostream& os) { }
	virtual Object* evaluate() = 0;
};
class NumberNode : public ASTNode {
	private:
	long double value;
	public:
	NumberNode(long double);
	long double* getValue();
	virtual Object* evaluate() override;
};
class IdentifierNode : public ASTNode {
	private:
	String name;
	public:
	IdentifierNode(String);
	String getName();
	virtual Object* evaluate() override;
};
class StringNode : public ASTNode {
	private:
	String value;
	public:
	StringNode(String);
	String* getValue();
	virtual Object* evaluate() override;
};
class IfNode : public ASTNode {
	private :
	ASTNode* condition;
	ASTNode* body;
	List<ASTNode> branches;
	public:
	IfNode(ASTNode*, ASTNode*, List<ASTNode> branches = List<ASTNode>());
	ASTNode* getCondition();
	ASTNode* getBody();
	List<ASTNode> getBranches();
	virtual Object* evaluate() override;
};
class ElseNode : public ASTNode {
	private:
	ASTNode* body;
	public:
	ElseNode(ASTNode*);
	ASTNode* getBody();
	virtual Object* evaluate() override;
};
class BlockNode : public ASTNode {
	private:
	List<ASTNode> statements;
	public:
	BlockNode(List<ASTNode>);
	List<ASTNode> getStatements();
	virtual Object* evaluate() override;
};
class BinaryExpressionNode : public ASTNode {
	private:
	ASTNode* left;
	String operator__;
	ASTNode* right;
	public:
	BinaryExpressionNode(ASTNode*, String operator__, ASTNode* right);
	ASTNode* getLeft();
	String getOperator();
	ASTNode* getRight();
	virtual Object* evaluate() override;
};
class FunctionNode : public ASTNode {
	private:
	String functionName;
	List<ASTNode> arguments;
	public:
	FunctionNode(String, List<ASTNode>);
	String getFunctionName();
	List<ASTNode> getArguments();
	virtual Object* evaluate() override;
};
class AssignmentNode : public ASTNode {
	private:
	String variableName;
	ASTNode* value;
	public:
	AssignmentNode(String, ASTNode*);
	ASTNode* getValue();
	String getVariableName();
	virtual Object* evaluate() override;
};
class VariableNode : public ASTNode {
	private:
	String name;
	String type;
	Object* value;
	public:
	VariableNode(String, String, Object*);
	String getName();
	String getType();
	Object* getValue();
	virtual Object* evaluate() override;
};