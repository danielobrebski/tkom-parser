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

class Parser
{
public:
    Parser(Lexer lex);
    void program(void);
    void functionDef(void);
    void type(void);
    void parameteres(void);
    void arguments(void);
    void statementBlock(void);
    void forStatement(void);
    void ifStatement(void);
    void whileStatement(void);
    void returnStatement(void);
    void assignmentFunctionStatement(int synchronize);
    void initStatement(void);
    
    void assignable(void);
    void expression(void);
    void multiplicativeExpression(void);
    void logicalShiftExpression(void);
    void primaryExpression(void);
    void parenthExpression(void);
    void condition(void);
    void andCondition(void);
    void equalityCondition(void);
    void relationalCondition(void);
    void incrementCondition(void);
    void primaryCondition(void);
    void parenthCondition(void);
    void indexOperator(void);
    void variable(void);
    void literal(void);
    void numberLiteral(void);
    void matrixLiteral(void);
    
    /*
     literal = numberLiteral | matrixLiteral .
     variable = id [ indexOp ] .
     numberLiteral = [ "-"] "Infinity" | finiteNumber .
     finiteNumber = digit { digit } [ "." { digit } ] .
     matrixLiteral = "{" { "{" numberLiteral  { "," numberLiteral } "}" } "}" .
     */
    
 
private:
    Lexer lex;
    static Token token;
    TokenType tokType;
    TokenType buf;
    void error(TokenType tt, int i);
    int accept(TokenType tt);
    void nextToken();

};



#endif /* defined(__TKOM__Parser__) */
