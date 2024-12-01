#pragma once
#include <usings.h>
#include <sstream>
class ASTNode {
	protected:
	String ASTName = "ASTNode";
	public:
	virtual ~ASTNode() = default;
	ASTNode() = default;
	virtual String& getASTName() { return ASTName; }
	virtual std::ostream& operator<<(std::ostream& os) { return os; }
	virtual Object* evaluate() { return nullptr; }
};
class NumberNode final : public ASTNode {
	long double value;
	public:
	explicit NumberNode(long double);
	long double* getValue();
	Object* evaluate() override;
};
class IdentifierNode final : public ASTNode {
	String name;
	public:
	explicit IdentifierNode(const String &);
	String getName();
	Object* evaluate() override;
};
class StringNode final : public ASTNode {
	String value;
	public:
	explicit StringNode(const String &);
	String* getValue();
	Object* evaluate() override;
};
class IfNode final : public ASTNode {
	ASTNode* condition;
	ASTNode* body;
	List<ASTNode> branches;
	public:
	IfNode(ASTNode*, ASTNode*, const List<ASTNode> &branches = List<ASTNode>());
	[[nodiscard]] ASTNode* getCondition() const;
	[[nodiscard]] ASTNode* getBody() const;
	List<ASTNode> getBranches();
	Object* evaluate() override;
};
class ElseNode final : public ASTNode {
	ASTNode* body;
	public:
	explicit ElseNode(ASTNode*);
	[[nodiscard]] ASTNode* getBody() const;
	Object* evaluate() override;
};
class BlockNode final : public ASTNode {
	List<ASTNode> statements;
	public:
	explicit BlockNode(const List<ASTNode> &);
	List<ASTNode> getStatements();
	Object* evaluate() override;
};
class BinaryExpressionNode final : public ASTNode {
	ASTNode* left;
	String operator_;
	ASTNode* right;
	public:
	BinaryExpressionNode(ASTNode*, const String &operator_, ASTNode* right);
	[[nodiscard]] ASTNode* getLeft() const;
	String getOperator();
	[[nodiscard]] ASTNode* getRight() const;
	Object* evaluate() override;
};
class FunctionNode final : public ASTNode {
	String functionName;
	List<ASTNode> arguments;
	public:
	FunctionNode(const String &, const List<ASTNode> &);
	String getFunctionName();
	List<ASTNode> getArguments();
	Object* evaluate() override;
};
class AssignmentNode final : public ASTNode {
	String variableName;
	ASTNode* value;
	public:
	AssignmentNode(const String &, ASTNode*);
	[[nodiscard]] ASTNode* getValue() const;
	String getVariableName();
	Object* evaluate() override;
};
class VariableNode final : public ASTNode {
	String name;
	String type;
	Object* value;
	public:
	VariableNode(const String &, const String &, Object*);
	String getName();
	String getType();
	[[nodiscard]] Object* getValue() const;
	Object* evaluate() override;
};