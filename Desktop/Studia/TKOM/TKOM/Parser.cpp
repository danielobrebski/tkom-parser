//
//  Parser.cpp
//  TKOM
//
//  Created by Daniel Obrebski on 21.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#include "Parser.h"

Parser::Parser(Lexer lex) : lex(lex) {};

void Parser::error(Token token)
{
    std::cout << "Spodziewany token: " << token.show() << std::endl;
}
void Parser::accept(TokenType tt)
{
    if(tokType == tt)
    {
        token = lex.getToken();
        tokType = token.getType();
    }
    else 
    {
        error(token);
    }
}

void Parser::nextToken()
{
    tokType = lex.getToken().getType();
}

void Parser::program(void)
{
    tokType = lex.getToken().getType();
    functionDef();
}

void Parser::functionDef(void)
{
    type();
    accept(TokenType::Ident);
    parameteres();
    statementBlock();
}

void Parser::type(void)
{
    if(tokType == TokenType::Int || tokType == TokenType::Long || tokType == TokenType::Float|| tokType == TokenType::Double)
        tokType = lex.getToken().getType();
        
}

void Parser::parameteres(void)
{
    accept(TokenType::LeftParenthes);
    
}

void Parser::arguments(void)
{
    
}

void Parser::statementBlock(void)
{
    
}

void Parser::forStatement(void)
{
    
}

void Parser::ifStatement(void)
{
    accept(TokenType::If);
    expect(TokenType::LeftParenthes);
    statementBlock();
    if(accept(TokenType::Else))
        statementBlock();
}

void Parser::whileStatement(void)
{
    accept(TokenType::While);
    expect(TokenType::LeftParenthes);
    condition();
    expect(TokenType::RightParenthes);
    
}

void Parser::returnStatement(void)
{
    accept(TokenType::Return);
    assignable();
    expect(TokenType::SemiCollon);
}

void Parser::assignmentStatement(void)
{
    variable();
    if(accept(TokenType::Assign))
        assignable();
    else
        error("Expect '=' symbol");
}

void Parser::initStatement(void)
{
    
}

void Parser::functionStatement(void)
{
    accept(TokenType::Ident);
    arguments();
}

void Parser::assignable(void)
{
    if(accept(TokenType::Ident))
        functionStatement();
    expression();
}

void Parser::expression(void)
{
    multiplicativeExpression();
}

void Parser::multiplicativeExpression(void)
{
    logicalShiftExpression();
}

void Parser::logicalShiftExpression(void)
{
    primaryExpression();
}

void Parser::primaryExpression(void)
{
    if(tokType == TokenType::Minus || tokType == TokenType::Number || tokType == TokenType::LeftBracket)
        literal();
}

void Parser::parenthExpression(void)
{
    
}

void Parser::condition(void)
{
    
}

void Parser::andCondition(void)
{
    
}

void Parser::equalityCondition(void)
{
    
}

void Parser::relationalCondition(void)
{
    
}

void Parser::incrementCondition(void)
{
    
}

void Parser::primaryCondition(void)
{
    
}

void Parser::parenthCondition(void)
{
    
}

void Parser::variable(void)
{
    
}

void Parser::literal(void)
{
    
}
