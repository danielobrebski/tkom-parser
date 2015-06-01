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
    token = lex.getToken();
    tokType = token.getType();
}

std::vector<FunctionAST> Parser::program(void)
{
    std::vector<FunctionAST> functions;
    nextToken();
    while(tokType == TokenType::Int || tokType == TokenType::Long || tokType == TokenType::Float|| tokType == TokenType::Double)
        functions.push_back(*functionDef());
    return functions;
    
}

FunctionAST* Parser::functionDef(void)
{
    ExprAST *body;
    type();
    std::string name = token.getCargo();
    accept(TokenType::Ident);
    std::vector<std::string> para = parameteres();
    PrototypeAST *proto = new PrototypeAST(name,para);
    body = statementBlock();
   
    return new FunctionAST(proto, body);
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

std::vector<std::string> Parser::parameteres(void)
{
    std::vector<std::string> params;
    
    accept(TokenType::LeftParenthes);
    if(tokType == TokenType::Int || tokType == TokenType::Long || tokType == TokenType::Float|| tokType == TokenType::Double)
    {
        type();
        params.push_back(token.getCargo());
        accept(TokenType::Ident);
        while(tokType == TokenType::Comma)
        {
            nextToken();
            type();
            params.push_back(token.getCargo());
            accept(TokenType::Ident);
        }
    }
    accept(TokenType::RightParenthes);
    return params;
    
}

std::vector<ExprAST*> Parser::arguments(void)
{
    std::vector<ExprAST*> args;
    accept(TokenType::LeftParenthes);
    args.push_back(assignable());
    while(tokType == TokenType::Comma)
    {
        nextToken();
        args.push_back(assignable());
    }
    accept(TokenType::RightParenthes);
    return args;
}

ExprAST* Parser::statementBlock(void)
{
    accept(TokenType::LeftBrace);
    ExprAST *stmt = nullptr;
    int ret = 1;
    while(ret == 1)
    {
        switch (tokType)
        {
            case TokenType::For:
                stmt = forStatement();
                break;
                ;
            
            case TokenType::If:
                stmt = ifStatement();
                break;
                ;
            
            case TokenType::While:
                stmt = whileStatement();
                break;
                ;
            
            case TokenType::Return:
                stmt = returnStatement();
                break;
                ;
            
            
            case TokenType::Ident:
                stmt = assignmentFunctionStatement(0);
                accept(TokenType::SemiCollon);
                break;
                ;
            
            case TokenType::LeftBrace:
                stmt = statementBlock();
                break;
                ;
            
            case TokenType::Int:
            case TokenType::Long:
            case TokenType::Float:
            case TokenType::Double:
            case TokenType::Static:
                stmt = initStatement();
                accept(TokenType::SemiCollon);
                break;
                ;
                
            default:
                ret = 0;
            
        }
    }
    accept(TokenType::RightBrace);
    
    return stmt;
}

ExprAST* Parser::forStatement(void)
{
    std::vector<ExprAST*> ass1, ass2, cond;
    ExprAST *block;
    
    accept(TokenType::For);
    accept(TokenType::LeftParenthes);
    
    if(tokType == TokenType::Ident)
    {
        ass1.push_back(assignmentFunctionStatement(0));
        while(tokType == TokenType::Comma)
        {
            nextToken();
            ass1.push_back(assignmentFunctionStatement(0));
        }

    }
    
    accept(TokenType::SemiCollon);
    cond.push_back(condition());
    accept(TokenType::SemiCollon);
    
    if(tokType == TokenType::Ident)
    {
        ass2.push_back(assignmentFunctionStatement(0));
        while(tokType == TokenType::Comma)
        {
            nextToken();
            ass2.push_back(assignmentFunctionStatement(0));
        }
        
    }
    accept(TokenType::RightParenthes);
    block = statementBlock();
    return new ForExprAST(&ass1, &cond, &ass2, block);
}

ExprAST* Parser::ifStatement(void)
{
    ExprAST *cond, *block;
    ExprAST *els = nullptr;
    accept(TokenType::If);
    accept(TokenType::LeftParenthes);
    cond = condition();
    accept(TokenType::RightParenthes);
    block = statementBlock();
    if(accept(TokenType::Else))
        els = statementBlock();
    return new IfExprAST(cond, block, els);
}

ExprAST* Parser::whileStatement(void)
{
    ExprAST *cond, *block;
    accept(TokenType::While);
    accept(TokenType::LeftParenthes);
    cond = condition();
    accept(TokenType::RightParenthes);
    block = statementBlock();
    
    return new WhileExprAST(cond, block);
    
}

ExprAST* Parser::returnStatement(void)
{
    ExprAST *assb;
    accept(TokenType::Return);
    assb = assignable();
    accept(TokenType::SemiCollon);
    return assb;
}

ExprAST* Parser::assignmentFunctionStatement(int synchronize)
{
    ExprAST *lhs, *rhs;
    ExprAST *ret;
    std::vector<ExprAST*> args;
    lhs = variable();
    if(synchronize == 1 || synchronize == 0)
    {
        if(tokType == TokenType::LeftParenthes)
        {
            args = arguments();
            return new CallExprAST(lhs, args);
        }
    }
    if(synchronize == 0)
    {
        if(tokType == TokenType::Decrement || tokType == TokenType::Increment)
        {
            ret = new IncrementExprAST(token.getCargo(), lhs);
            nextToken();
            return ret;
        }
        else if(tokType == TokenType::Assign || tokType == TokenType::PlusEqual || tokType == TokenType::MinusEqual || tokType == TokenType::MultiplyEqual || tokType == TokenType::DivideEqual)
        {
            std::string op = token.getCargo();
            nextToken();
            rhs = assignable();
            ret = new AssignmentExprAST(op, lhs, rhs);
            return ret;
        }
    }
    return nullptr;
}

ExprAST* Parser::initStatement(void)
{
    ExprAST *var, *ass = nullptr;
    type();
    var = variable();
    if(tokType == TokenType::Assign)
    {
        nextToken();
        ass = assignable();
    }
    return new InitialExprAST(var, ass);
}


ExprAST* Parser::assignable(void)
{
    ExprAST* expr;
    expr = expression();
    return expr;
}

ExprAST* Parser::expression(void)
{
    ExprAST *LHS;
    std::vector<ExprAST*> RHS;
    std::vector<std::string> op;
    LHS = multiplicativeExpression();
    while(tokType == TokenType::Plus || tokType == TokenType::Minus)
    {
        op.push_back(token.getCargo());
        nextToken();
        RHS.push_back(multiplicativeExpression());
    }
    return new ArithmeticExprAST(op, LHS, RHS);
}

ExprAST* Parser::multiplicativeExpression(void)
{
    ExprAST *LHS;
    std::vector<ExprAST*> RHS;
    std::vector<std::string> op;
    LHS = logicalShiftExpression();
    while(tokType == TokenType::Multiply || tokType == TokenType::Divide || tokType == TokenType::Slash)
    {
        op.push_back(token.getCargo());
        nextToken();
        RHS.push_back(logicalShiftExpression());
    }
    
    return new ArithmeticExprAST(op, LHS, RHS);

}

ExprAST* Parser::logicalShiftExpression(void)
{
    ExprAST *LHS;
    std::vector<ExprAST*> RHS;
    std::vector<std::string> op;
    LHS = primaryExpression();
    while(tokType == TokenType::LeftLogicalShift || tokType == TokenType::RightLogicalShift)
    {
        op.push_back(token.getCargo());
        nextToken();
        RHS.push_back(primaryExpression());
    }
    return new ArithmeticExprAST(op, LHS, RHS);
}

ExprAST* Parser::primaryExpression(void)
{
    ExprAST *ret = nullptr;

    if(tokType == TokenType::Minus || tokType == TokenType::Number || tokType == TokenType::LeftBrace)
        ret = literal();
    
    else if(tokType == TokenType::Ident)
        ret = variable();
    
    else if(tokType == TokenType::LeftParenthes)
        ret = parenthExpression();
    return ret;
}

ExprAST* Parser::parenthExpression(void)
{
    ExprAST *ret;
    accept(TokenType::LeftParenthes);
    ret = expression();
    accept(TokenType::RightParenthes);
    return ret;
}

ExprAST* Parser::condition(void)
{
    ExprAST *LHS, *RHS = nullptr;
    std::string op;
    LHS = andCondition();
    if(tokType == TokenType::Comma || tokType == TokenType::Or)
    {
        op = token.getCargo();
        nextToken();
        RHS = andCondition();
    }
    return new ConditionExprAST(op, LHS, RHS);
}

ExprAST* Parser::andCondition(void)
{
    ExprAST *LHS, *RHS = nullptr;
    std::string op;
    LHS = equalityCondition();
    if(tokType == TokenType::And)
    {
        op = token.getCargo();
        nextToken();
        RHS = equalityCondition();
    }
    return new ConditionExprAST(op, LHS, RHS);

}

ExprAST* Parser::equalityCondition(void)
{
    ExprAST *LHS, *RHS = nullptr;
    std::string op;
    LHS = relationalCondition();
    if(tokType == TokenType::Equal || tokType == TokenType::NotEqual)
    {
        op = token.getCargo();
        nextToken();
        RHS = relationalCondition();
    }
    return new ConditionExprAST(op, LHS, RHS);

}

ExprAST* Parser::relationalCondition(void)
{
    ExprAST *LHS, *RHS = nullptr;
    std::string op;
    LHS = primaryCondition();
    if(tokType == TokenType::LessThan || tokType == TokenType::LessThanOrEqual || tokType == TokenType::MoreThan || tokType == TokenType::MoreThanOrEqual)
    {
        op = token.getCargo();
        nextToken();
        RHS = primaryCondition();
    }
    return new ConditionExprAST(op, LHS, RHS);

}

ExprAST* Parser::primaryCondition(void)
{
    ExprAST* ret = nullptr;
    
    if(tokType == TokenType::Minus || tokType == TokenType::Number || tokType == TokenType::LeftBrace)
        ret = literal();
    
    else if(tokType == TokenType::Ident)
        ret = variable();
    
    else if(tokType == TokenType::LeftParenthes)
        ret = parenthCondition();
    
    return ret;
    
}

ExprAST* Parser::parenthCondition(void)
{
    ExprAST *ret;
    accept(TokenType::LeftParenthes);
    ret = condition();
    accept(TokenType::RightParenthes);
    return ret;
}

ExprAST* Parser::indexOperator(void)
{
    ExprAST *LHS, *RHS = nullptr;
    accept(TokenType::LeftBracket);
    LHS = assignable();
    accept(TokenType::RightBracket);
    if(tokType == TokenType::LeftBracket)
    {
        nextToken();
        RHS = assignable();
        accept(TokenType::RightBracket);
    }
    return new IndexExprAST(LHS, RHS);
}

ExprAST* Parser::variable(void)
{
    std::string name = token.getCargo();
    ExprAST *expr = nullptr;
    accept(TokenType::Ident);
    if(tokType == TokenType::LeftBracket)
    {
        expr = indexOperator();
    }
    return new VariableExprAST(name, expr);
}

ExprAST* Parser::literal(void)
{
    ExprAST *literal;
    if(tokType == TokenType::Minus || tokType == TokenType::Number)
        literal = numberLiteral();
    else if(tokType == TokenType::LeftBrace)
    {
        literal = matrixLiteral();
    }
    
    else
    {
        literal = nullptr;
        error(tokType, 1);
    }
    
    return literal;
}

ExprAST* Parser::numberLiteral(void)
{
    double val = 0;
    if(tokType == TokenType::Minus)
    {
        val = -val;
        nextToken();
    }
    
    val+=stoi(token.getCargo());
    accept(TokenType::Number);
    return new NumberExprAST(val);
}

ExprAST* Parser::matrixLiteral(void)
{
    std::vector<std::vector<double> > tempvec;
    std::vector<double> row;
    accept(TokenType::LeftBrace);
    while(tokType == TokenType::LeftBrace)
    {
        nextToken();
        row.push_back(stod(token.getCargo()));
        
        accept(TokenType::Number);
        while(tokType == TokenType::Comma)
        {
            nextToken();
            row.push_back(stod(token.getCargo()));
            accept(TokenType::Number);
            
        }
        tempvec.push_back(row);
        row.clear();
        accept(TokenType::RightBrace);
        if(tokType == TokenType::Comma)
            nextToken();
        else
            break;
    }
    accept(TokenType::RightBrace);
    
    return new MatrixExprAST(tempvec);
}
