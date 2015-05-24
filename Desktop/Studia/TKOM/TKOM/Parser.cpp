//
//  Parser.cpp
//  TKOM
//
//  Created by Daniel Obrebski on 21.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#include "Parser.h"

Parser::Parser(Lexer lex) : lex(lex) {};

void Parser::error(TokenType tt, int i)
{
    std::cout << std::endl;
    if(i == 0)
        std::cout << "Expected token: ";
    else
        std::cout << "Unexpected token: ";
    
    switch (int(tt))
    {
        case 0:
            std::cout << "static";
            break;
            ;
            
        case 1:
            std::cout << "if";
            break;
            ;
            
        case 2:
            std::cout << "for";
            break;
            ;
            
        case 3:
            std::cout << "else";
            break;
            ;
            
        case 4:
            std::cout << "while";
            break;
            ;
            
        case 5:
            std::cout << "return";
            break;
            ;
            
        case 6:
            std::cout << "int";
            break;
            ;
            
        case 7:
            std::cout << "void";
            break;
            ;
            
        case 8:
            std::cout << "long";
            break;
            ;
            
        case 9:
            std::cout << "float";
            break;
            ;
            
        case 10:
            std::cout << "double";
            break;
            ;
            
        case 11:
            std::cout << "+";
            break;
            ;
        case 12:
            std::cout << "=";
            break;
            ;
            
        case 13:
            std::cout << "/";
            break;
            ;
            
        case 14:
            std::cout << "==";
            break;
            ;
            
        case 15:
            std::cout << "!=";
            break;
            ;
            
        case 16:
            std::cout << "<";
            break;
            ;
            
        case 17:
            std::cout << "<=";
            break;
            ;
            
        case 18:
            std::cout << ">";
            break;
            ;
            
        case 19:
            std::cout << ">=";
            break;
            ;
            
        case 20:
            std::cout << "<<";
            break;
            ;
            
        case 21:
            std::cout << ">>";
            break;
            ;
            
        case 22:
            std::cout << "+=";
            break;
            ;
            
        case 23:
            std::cout << "-=";
            break;
            ;
            
        case 24:
            std::cout << "*=";
            break;
            ;
            
        case 25:
            std::cout << "/=";
            break;
            ;
            
        case 26:
            std::cout << "*";
            break;
            ;
            
        case 27:
            std::cout << "-";
            break;
            ;
            
        case 28:
            std::cout << "/";
            break;
            ;
            
        case 29:
            std::cout << "++";
            break;
            ;
            
        case 30:
            std::cout << "--";
            break;
            ;
            
        case 31:
            std::cout << "{";
            break;
            ;
            
        case 32:
            std::cout << "}";
            break;
            ;
            
        case 33:
            std::cout << "[";
            break;
            ;
            
        case 34:
            std::cout << "]";
            break;
            ;
            
        case 35:
            std::cout << "(";
            break;
            ;
            
        case 36:
            std::cout << ")";
            break;
            ;
            
        case 37:
            std::cout << ";";
            break;
            ;
            
        case 38:
            std::cout << ":";
            break;
            ;
            
        case 39:
            std::cout << ",";
            break;
            ;
            
        case 40:
            std::cout << "id";
            break;
            ;
            
        case 41:
            std::cout << "Number";
            break;
            ;
            
        case 42:
            std::cout << "//";
            break;
            ;
            
        case 43:
            std::cout << "eof";
            break;
            ;
            
        case 44:
            std::cout << "quote";
            break;
            ;
            
        case 45:
            std::cout << "and";
            break;
            ;
            
        case 46:
            std::cout << "or";
            break;
            ;
            
        case 47:
            std::cout << "!";
            break;
            ;
            
    }
    std::cout << " in line: " << lex.getRowIdx() << " in column: " << lex.getColIdx() << std::endl;
    
}


int Parser::accept(TokenType tt)
{
    if(tokType == tt)
    {
        nextToken();
        return 1;
    }
    else 
    {
        error(tt, 0);
        return 0;
    }
}

void Parser::nextToken()
{
    tokType = lex.getToken().getType();
}

void Parser::program(void)
{
    nextToken();
    while(tokType == TokenType::Int || tokType == TokenType::Int || tokType == TokenType::Long || tokType == TokenType::Float|| tokType == TokenType::Double)
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
    if(tokType == TokenType::Static)
        nextToken();
    if(tokType == TokenType::Int || tokType == TokenType::Long || tokType == TokenType::Float|| tokType == TokenType::Double)
        nextToken();
    else
        error(tokType, 1);
}

void Parser::parameteres(void)
{
    accept(TokenType::LeftParenthes);
    if(tokType == TokenType::Int || tokType == TokenType::Long || tokType == TokenType::Float|| tokType == TokenType::Double)
    {
        type();
        accept(TokenType::Ident);
        while(tokType == TokenType::Comma)
        {
            nextToken();
            type();
            accept(TokenType::Ident);
        }
    }
    accept(TokenType::RightParenthes);
    
}

void Parser::arguments(void)
{
    accept(TokenType::LeftParenthes);
    assignable();
    while(tokType == TokenType::Comma)
    {
        nextToken();
        assignable();
    }
    accept(TokenType::RightParenthes);
    
}

void Parser::statementBlock(void)
{
    accept(TokenType::LeftBrace);
    int ret = 1;
    while(ret == 1)
    {
        switch (tokType)
        {
            case TokenType::For:
                forStatement();
                break;
                ;
            
            case TokenType::If:
                ifStatement();
                break;
                ;
            
            case TokenType::While:
                whileStatement();
                break;
                ;
            
            case TokenType::Return:
                returnStatement();
                break;
                ;
            
            
            case TokenType::Ident:
                assignmentFunctionStatement(0);
                accept(TokenType::SemiCollon);
                break;
                ;
            
            case TokenType::LeftBrace:
                statementBlock();
                break;
                ;
            
            case TokenType::Int:
            case TokenType::Long:
            case TokenType::Float:
            case TokenType::Double:
            case TokenType::Static:
                initStatement();
                accept(TokenType::SemiCollon);
                break;
                ;
                
            default:
                ret = 0;
            
        }
    }
    accept(TokenType::RightBrace);
}

void Parser::forStatement(void)
{
    accept(TokenType::For);
    accept(TokenType::LeftParenthes);
    
    if(tokType == TokenType::Ident)
    {
        assignmentFunctionStatement(0);
        while(tokType == TokenType::Comma)
        {
            nextToken();
            assignmentFunctionStatement(0);
        }

    }
    
    accept(TokenType::SemiCollon);
    condition();
    accept(TokenType::SemiCollon);
    
    if(tokType == TokenType::Ident)
    {
        assignmentFunctionStatement(0);
        while(tokType == TokenType::Comma)
        {
            nextToken();
            assignmentFunctionStatement(0);
        }
        
    }
    accept(TokenType::RightParenthes);
    statementBlock();
}

void Parser::ifStatement(void)
{
    accept(TokenType::If);
    accept(TokenType::LeftParenthes);
    statementBlock();
    if(accept(TokenType::Else))
        statementBlock();
}

void Parser::whileStatement(void)
{
    accept(TokenType::While);
    accept(TokenType::LeftParenthes);
    condition();
    accept(TokenType::RightParenthes);
    statementBlock();
    
}

void Parser::returnStatement(void)
{
    accept(TokenType::Return);
    assignable();
    accept(TokenType::SemiCollon);
}

void Parser::assignmentFunctionStatement(int synchronize)
{
    variable();
    if(synchronize == 1 || synchronize == 0)
    {
        if(tokType == TokenType::LeftParenthes)
        {
            arguments();
            return;
        }
    }
    if(synchronize == 0)
    {
        if(tokType == TokenType::Decrement || tokType == TokenType::Increment)
            nextToken();
        else if(tokType == TokenType::Assign || tokType == TokenType::PlusEqual || tokType == TokenType::MinusEqual || tokType == TokenType::MultiplyEqual || tokType == TokenType::DivideEqual)
        {
            nextToken();
            assignable();
        }
    }
}

void Parser::initStatement(void)
{
    type();
    variable();
    if(tokType == TokenType::Assign)
    {
        nextToken();
        assignable();
    }
}


void Parser::assignable(void)
{
        expression();
}

void Parser::expression(void)
{
    multiplicativeExpression();
    if(tokType == TokenType::Plus || tokType == TokenType::Minus)
    {
        nextToken();
        multiplicativeExpression();
    }
}

void Parser::multiplicativeExpression(void)
{
    logicalShiftExpression();
    if(tokType == TokenType::Multiply || tokType == TokenType::Slash)
    {
        nextToken();
        logicalShiftExpression();
    }

}

void Parser::logicalShiftExpression(void)
{
    primaryExpression();
    if(tokType == TokenType::LeftLogicalShift || tokType == TokenType::RightLogicalShift)
    {
        nextToken();
        primaryExpression();
    }
}

void Parser::primaryExpression(void)
{
    if(tokType == TokenType::Minus || tokType == TokenType::Number || tokType == TokenType::LeftBrace)
        literal();
    
    else if(tokType == TokenType::Ident)
        variable();
    
    else if(tokType == TokenType::LeftParenthes)
        parenthExpression();
    
    else
        error(tokType, 1);
}

void Parser::parenthExpression(void)
{
    accept(TokenType::LeftParenthes);
    expression();
    accept(TokenType::RightParenthes);
}

void Parser::condition(void)
{
    andCondition();
    while(tokType == TokenType::Comma || tokType == TokenType::Or)
    {
        nextToken();
        andCondition();
    }
}

void Parser::andCondition(void)
{
    equalityCondition();
    while(tokType == TokenType::And)
    {
        nextToken();
        equalityCondition();
    }

}

void Parser::equalityCondition(void)
{
    relationalCondition();
    while(tokType == TokenType::Equal || tokType == TokenType::NotEqual)
    {
        nextToken();
        relationalCondition();
    }

}

void Parser::relationalCondition(void)
{
    incrementCondition();
    while(tokType == TokenType::LessThan || tokType == TokenType::LessThanOrEqual || tokType == TokenType::MoreThan || tokType == TokenType::MoreThanOrEqual)
    {
        nextToken();
        incrementCondition();
    }

}

void Parser::incrementCondition(void)
{
    primaryCondition();
    while(tokType == TokenType::Increment || tokType == TokenType::Decrement)
    {
        nextToken();
        primaryCondition();
    }

}

void Parser::primaryCondition(void)
{
    if(tokType == TokenType::Minus)
        nextToken();
    
    if(tokType == TokenType::Minus || tokType == TokenType::Number || tokType == TokenType::LeftBrace)
        literal();
    
    else if(tokType == TokenType::Ident)
        variable();
    
    else if(tokType == TokenType::LeftParenthes)
        parenthCondition();
    

    
}

void Parser::parenthCondition(void)
{
    accept(TokenType::LeftParenthes);
    condition();
    accept(TokenType::RightParenthes);
}

void Parser::indexOperator(void)
{
    accept(TokenType::LeftBracket);
    assignable();
    accept(TokenType::RightBracket);
    if(tokType == TokenType::LeftBracket)
    {
        nextToken();
        assignable();
        accept(TokenType::RightBracket);
    }
}

void Parser::variable(void)
{
    accept(TokenType::Ident);
    if(tokType == TokenType::LeftBracket)
        indexOperator();
}

void Parser::literal(void)
{
    if(tokType == TokenType::Minus || tokType == TokenType::Number)
        numberLiteral();
    else if(tokType == TokenType::LeftBrace)
        matrixLiteral();
    
    else
        error(tokType, 1);
}

void Parser::numberLiteral(void)
{
    if(tokType == TokenType::Minus)
        nextToken();
    accept(TokenType::Number);
}

void Parser::matrixLiteral(void)
{
    
    accept(TokenType::LeftBrace);
    while(tokType == TokenType::LeftBrace)
    {
        nextToken();
        accept(TokenType::Number);
        while(tokType == TokenType::Comma)
        {
            nextToken();
            accept(TokenType::Number);
            
        }
        accept(TokenType::RightBrace);
        if(tokType == TokenType::Comma)
            nextToken();
        else
            break;
    }
    accept(TokenType::RightBrace);
}
