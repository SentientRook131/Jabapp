//
// Created by yy182 on 2024/12/1.
//

#ifndef PARSER_H
#define PARSER_H
#include <ASTNode.h>
#include <Token.h>

class Parser {
    List<Token> tokens;
    List<String> keywords = {"int", "short", "long", "float", "double", "bool", "char"};
    int current = 0;
    ASTNode null;
public:
    explicit Parser(const List<Token>& tokens);
    [[nodiscard]] ASTNode parse();
private:
    [[nodiscard]] List<ASTNode> parseStatements();
    [[nodiscard]] ASTNode parseStatement();
    [[nodiscard]] ASTNode parseBlock();
    [[nodiscard]] ASTNode parseIfStatement(bool);
    [[nodiscard]] ASTNode parseElseStatement();
    [[nodiscard]] ASTNode parseFunctionCall();
    [[nodiscard]] ASTNode parseExpression();
    [[nodiscard]] ASTNode parseComparison();
    [[nodiscard]] ASTNode parseTerm();
    [[nodiscard]] ASTNode parseFactor();
    [[nodiscard]] ASTNode parseVariable();
    Token consume(TokenType);
    [[nodiscard]] bool check(TokenType);
    [[nodiscard]] Token advance();
    [[nodiscard]] Token peek();
    [[nodiscard]] Token lookAhead(int);
    [[nodiscard]] bool isAtEnd();
    [[nodiscard]] ASTNode parseAssignment();
};

#endif //PARSER_H
