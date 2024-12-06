//
// Created by SentientRook131 on 2024/12/1.
//
#include "Parser.h"
Parser::Parser(const List<Token>& tokens) {
    this->tokens = tokens;
}
ASTNode Parser::parse() {
    const List<ASTNode> statements = parseStatements();
    return static_cast<ASTNode>(BlockNode(statements));
}
List<ASTNode> Parser::parseStatements() {
    List<ASTNode> statements;
    while (!isAtEnd()) {
        ASTNode statement = parseStatement();
        if (&statement != nullptr) {
            statements.push_back(statement);
        }
        if (!isAtEnd() && check(SEPARATOR) && peek().getValue() == ";") {
            consume(SEPARATOR);
        }
    }
    return statements;
}

ASTNode Parser::parseStatement() {
    if (check(KEYWORD) && peek().getValue() == "if") {
        return parseIfStatement(true);
    } else if (check(IDENTIFIER)) {
        String identifier = peek().getValue();
        if (lookAhead(1).getType() == OPERATOR && lookAhead(1).getValue() == "=") {
            return parseAssignment();
        } else {
            return parseFunctionCall();
        }
    } else if (check(KEYWORD)) {
        for (const String& keyword : keywords) if (peek().getValue() == keyword) return parseVariable();
    } else if (check(SEPARATOR) && peek().getValue() == "{") {
        return parseBlock();
    }
    if (isAtEnd()) return static_cast<ASTNode>(NullNode());
    throw "Unexpected statement:" + std::to_string(peek().getLineNumber()) + ";" + std::to_string(peek().getColumnNumber());
}

ASTNode Parser::parseBlock() {
    consume(SEPARATOR);
    List<ASTNode> statements;
    while (!isAtEnd()) {
        if (check(SEPARATOR) && peek().getValue() == "}") {
            break;
        }
        ASTNode statement = parseStatement();
        if (&statement != nullptr) {
            statements.push_back(statement);
        }
        if (!isAtEnd() && check(SEPARATOR) && peek().getValue() == ";") {
            consume(SEPARATOR);
        }
    }
    return static_cast<ASTNode>(BlockNode(statements));
}

ASTNode Parser::parseIfStatement(bool expectElse) {
    consume(KEYWORD);
    consume(SEPARATOR);
    ASTNode condition = parseExpression();
    ASTNode body = parseBlock();
    consume(SEPARATOR);
    List<ASTNode> branches;
    while (peek().getType() == KEYWORD && peek().getValue() == "else" && expectElse) {
        consume(KEYWORD);
        if (peek().getType() == KEYWORD && peek().getValue() == "if") {
            branches.push_back(parseIfStatement(false));
        } else if (peek().getType() == SEPARATOR && peek().getValue() == "{") {
            branches.push_back(parseElseStatement());
        } else {
            throw "Unexpected statement:" + std::to_string(peek().getLineNumber()) + ";" + std::to_string(peek().getColumnNumber());
        }
    }
    return static_cast<ASTNode>(branches.empty() ? IfNode(&condition, &body) : IfNode(&condition, &body, branches));
}
ASTNode Parser::parseElseStatement() {
    ASTNode body = parseBlock();
    consume(SEPARATOR);
    return static_cast<ASTNode>(ElseNode(&body));
}
ASTNode Parser::parseFunctionCall() {
    String functionName = consume(IDENTIFIER).getValue();
    consume(SEPARATOR);
    List<ASTNode> arguments;
    while (!check(SEPARATOR) || peek().getValue() != ")") {
        arguments.push_back(parseExpression());
        if (check(SEPARATOR) && peek().getValue() == ",") consume(SEPARATOR);
    }
    consume(SEPARATOR);
    return static_cast<ASTNode>(FunctionNode(functionName, arguments));
}
ASTNode Parser::parseExpression() {
    ASTNode left = parseComparison();
    while (!isAtEnd() && check(OPERATOR) && (peek().getValue() == "+" || peek().getValue() == "-")) {
        String operator_ = consume(OPERATOR).getValue();
        ASTNode right = parseComparison();
        left = static_cast<ASTNode>(BinaryExpressionNode(&left, operator_, &right));
    }
    return left;
}
ASTNode Parser::parseComparison() {
    ASTNode left = parseTerm();
    while (!isAtEnd() && check(OPERATOR) && (peek().getValue() == ">" || peek().getValue() == "<" || peek().getValue() == ">=" || peek().getValue() == "<=" || peek().getValue() == "==" || peek().getValue() == "!=")) {
        String operator_ = consume(OPERATOR).getValue();
        ASTNode right = parseTerm();
        left = static_cast<ASTNode>(BinaryExpressionNode(&left, operator_, &right));
    }
    return left;
}
ASTNode Parser::parseTerm() {
    ASTNode left = parseFactor();
    while (!isAtEnd() && check(OPERATOR) && (peek().getValue() == "*" || peek().getValue() == "/")) {
        String operator_ = consume(OPERATOR).getValue();
        ASTNode right = parseFactor();
        left = static_cast<ASTNode>(BinaryExpressionNode(&left, operator_, &right));
    }
    return left;
}
ASTNode Parser::parseFactor() {
    if (check(NUMBER)) {
        return static_cast<ASTNode>(NumberNode(std::stold(consume(NUMBER).getValue())));
    } else if (check(IDENTIFIER)) {
        String identifier = consume(IDENTIFIER).getValue();
        if (check(SEPARATOR) && peek().getValue() == "(") {
            current--;
            return parseFunctionCall();
        }
    } else if (check(SEPARATOR) && peek().getValue() == "(") {
        consume(SEPARATOR);
        ASTNode expression = parseExpression();
        consume(SEPARATOR);
        return expression;
    } else if (check(STRING)) {
        StringNode node = StringNode(peek().getValue());
        consume(STRING);
        return static_cast<ASTNode>(node);
    }
}
ASTNode Parser::parseVariable() {
    String type = consume(IDENTIFIER).getValue();
    String identifier = consume(IDENTIFIER).getValue();
    if (check(SEPARATOR) && peek().getValue() == "=") {
        consume(SEPARATOR);
        Object expression = parseExpression();
        return static_cast<ASTNode>(VariableNode(identifier, type, &expression));
    }
    consume(SEPARATOR);
    return static_cast<ASTNode>(VariableNode(identifier, type, nullptr));
}
Token Parser::consume(TokenType type) {
    if (check(type)) return advance();
    std::exit(0);
}
bool Parser::check(TokenType type) {
    return !isAtEnd() && peek().getType() == type;
}
Token Parser::advance() {
    return tokens[current++];
}
Token Parser::peek() {
    return tokens[current];
}
Token Parser::lookAhead(int distance) {
    return tokens[current + distance];
}
bool Parser::isAtEnd() {
    return current >= tokens.size() || peek().getType() == EOF_;
}
ASTNode Parser::parseAssignment() {
    String variableName = consume(IDENTIFIER).getValue();
    consume(OPERATOR);
    ASTNode value = parseExpression();
    return static_cast<ASTNode>(AssignmentNode(variableName, &value));
}
