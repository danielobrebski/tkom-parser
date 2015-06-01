//
//  Parser.h
//  TKOM
//
//  Created by Daniel Obrebski on 21.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#ifndef __TKOM__Parser__
#define __TKOM__Parser__

#include <stdio.h>

#include "Lexer.h"
#include "TokenType.h"
#include "ExpressionAst.cpp"

class Parser
{
public:
    Parser(Lexer lex);
    std::vector<FunctionAST> program(void);
    FunctionAST* functionDef(void);
    void type(void);
    std::vector<std::string> parameteres(void);
    std::vector<ExprAST*> arguments(void);
    ExprAST* statementBlock(void);
    ExprAST* forStatement(void);
    ExprAST* ifStatement(void);
    ExprAST* whileStatement(void);
    ExprAST* returnStatement(void);
    ExprAST* assignmentFunctionStatement(int synchronize);
    ExprAST* initStatement(void);
    
    ExprAST* assignable(void);
    ExprAST* expression(void);
    ExprAST* multiplicativeExpression(void);
    ExprAST* logicalShiftExpression(void);
    ExprAST* primaryExpression(void);
    ExprAST* parenthExpression(void);
    ExprAST* condition(void);
    ExprAST* andCondition(void);
    ExprAST* equalityCondition(void);
    ExprAST* relationalCondition(void);
    ExprAST* primaryCondition(void);
    ExprAST* parenthCondition(void);
    ExprAST* indexOperator(void);
    ExprAST* variable(void);
    ExprAST* literal(void);
    ExprAST* numberLiteral(void);
    ExprAST* matrixLiteral(void);
    
    /*
     literal = numberLiteral | matrixLiteral .
     variable = id [ indexOp ] .
     numberLiteral = [ "-"] "Infinity" | finiteNumber .
     finiteNumber = digit { digit } [ "." { digit } ] .
     matrixLiteral = "{" { "{" numberLiteral  { "," numberLiteral } "}" } "}" .
     */
    
 
private:
    Lexer lex;
    Token token = *new Token(TokenType::Unknown, "");
    TokenType tokType;
    TokenType buf;
    void error(TokenType tt, int i);
    int accept(TokenType tt);
    void nextToken();

};



#endif /* defined(__TKOM__Parser__) */
