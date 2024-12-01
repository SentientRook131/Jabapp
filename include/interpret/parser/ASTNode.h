#pragma once
#include <../include/runtime/usings.h>
#include <sstream>
class ASTNode {
	protected:
	String ASTName = "ASTNode";
	public:
	ASTNode() = default;
	virtual String& getASTName() { return ASTName; }
	virtual std::ostream& operator<<(std::ostream& os) { return os; }
	virtual Object* evaluate() { return nullptr; }
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
	IdentifierNode(const String &);
	String getName();
	virtual Object* evaluate() override;
};
class StringNode : public ASTNode {
	private:
	String value;
	public:
	StringNode(const String &);
	String* getValue();
	virtual Object* evaluate() override;
};
class IfNode : public ASTNode {
	private :
	ASTNode* condition;
	ASTNode* body;
	List<ASTNode> branches;
	public:
	IfNode(ASTNode*, ASTNode*, const List<ASTNode> &branches = List<ASTNode>());
	ASTNode* getCondition() const;
	ASTNode* getBody() const;
	List<ASTNode> getBranches();
	virtual Object* evaluate() override;
};
class ElseNode : public ASTNode {
	private:
	ASTNode* body;
	public:
	ElseNode(ASTNode*);
	ASTNode* getBody() const;
	virtual Object* evaluate() override;
};
class BlockNode : public ASTNode {
	private:
	List<ASTNode> statements;
	public:
	BlockNode(const List<ASTNode> &);
	List<ASTNode> getStatements();
	virtual Object* evaluate() override;
};
class BinaryExpressionNode : public ASTNode {
	private:
	ASTNode* left;
	String operator__;
	ASTNode* right;
	public:
	BinaryExpressionNode(ASTNode*, const String &operator__, ASTNode* right);
	ASTNode* getLeft() const;
	String getOperator();
	ASTNode* getRight() const;
	virtual Object* evaluate() override;
};
class FunctionNode : public ASTNode {
	private:
	String functionName;
	List<ASTNode> arguments;
	public:
	FunctionNode(const String &, const List<ASTNode> &);
	String getFunctionName();
	List<ASTNode> getArguments();
	virtual Object* evaluate() override;
};
class AssignmentNode : public ASTNode {
	private:
	String variableName;
	ASTNode* value;
	public:
	AssignmentNode(const String &, ASTNode*);
	ASTNode* getValue() const;
	String getVariableName();
	virtual Object* evaluate() override;
};
class VariableNode : public ASTNode {
	private:
	String name;
	String type;
	Object* value;
	public:
	VariableNode(const String &, const String &, Object*);
	String getName();
	String getType();
	Object* getValue() const;
	virtual Object* evaluate() override;
};