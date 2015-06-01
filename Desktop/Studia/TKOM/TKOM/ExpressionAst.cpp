//
//  ExpressionAst.cpp
//  TKOM
//
//  Created by Daniel Obrebski on 01.06.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//


#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

class ExprAST
{
public:
    virtual ~ExprAST() {}
};

class NumberExprAST : public ExprAST
{
    double Val;
public:
    NumberExprAST(double val) : Val(val) {}
};

class VariableExprAST : public ExprAST
{
    std::string Name;
    ExprAST *RHS;
public:
    VariableExprAST(const std::string &name, ExprAST *rhs) : Name(name), RHS(rhs) {}
};

class AssignmentExprAST : public ExprAST
{
    std::string Op;
    ExprAST *LHS, *RHS;
public:
    AssignmentExprAST(const std::string &op, ExprAST *lhs, ExprAST *rhs) : Op(op), LHS(lhs), RHS(rhs) {}
};

class InitialExprAST : public ExprAST
{
    ExprAST *LHS;
    ExprAST *RHS;
public:
    InitialExprAST(ExprAST* lhs, ExprAST* rhs) : LHS(lhs), RHS(rhs) {}
};

class IndexExprAST : public ExprAST
{
    ExprAST *LHS;
    ExprAST *RHS;
public:
    IndexExprAST(ExprAST *lhs, ExprAST *rhs) : LHS(lhs), RHS(rhs) {}
};

class CallExprAST : public ExprAST
{
    ExprAST* Callee;
    std::vector<ExprAST*> Args;
public:
    CallExprAST(ExprAST* callee, std::vector<ExprAST*> &args)
    : Callee(callee), Args(args) {}
};

class ConditionExprAST : public ExprAST
{
    std::string Op;
    ExprAST *LHS, *RHS;
public:
    ConditionExprAST(const std::string &op, ExprAST *lhs, ExprAST *rhs) : Op(op), LHS(lhs), RHS(rhs) {}
};

class ForExprAST : public ExprAST
{
    std::vector<ExprAST*> *LHS, *RHS; //assignments
    std::vector<ExprAST*> *MHS; //conditions
    ExprAST *Block;
public:
    ForExprAST(std::vector<ExprAST*> *lhs,
               std::vector<ExprAST*> *mhs, std::vector<ExprAST*> *rhs,
               ExprAST *block) :
    LHS(lhs), MHS(mhs), RHS(rhs), Block(block) {}
};

class IfExprAST : public ExprAST
{
    ExprAST *LHS; //condition
    ExprAST *MHS, *RHS;
public:
    IfExprAST(ExprAST *lhs, ExprAST *mhs, ExprAST *rhs) :
    LHS(lhs), MHS(mhs), RHS(rhs) {}
};

class WhileExprAST : public ExprAST
{
    ExprAST *LHS; //condition
    ExprAST *RHS;
public:
    WhileExprAST(ExprAST *lhs, ExprAST *rhs) : RHS(rhs), LHS(lhs) {}
};

class IncrementExprAST : public ExprAST
{
    std::string Op;
    ExprAST *OHS;
public:
    IncrementExprAST(const std::string &op, ExprAST *ohs) : Op(op), OHS(ohs) {}
};

class ArithmeticExprAST : public ExprAST
{
    std::vector<std::string> Op;
    ExprAST* LHS;
    std::vector<ExprAST*> RHS;
public:
    ArithmeticExprAST(const std::vector<std::string> &op, ExprAST *lhs, const std::vector<ExprAST*> &rhs) :
    Op(op), LHS(lhs), RHS(rhs) {}
};

class MatrixExprAST: public ExprAST
{
    std::vector<std::vector<double> > Vec;
public:
    MatrixExprAST(const std::vector<std::vector<double> > &vec) : Vec(vec) {}
    
};

class PrototypeAST
{
    std::string Name;
    std::vector<std::string> Args;
public:
    PrototypeAST(const std::string &name, const std::vector<std::string> &args)
    : Name(name), Args(args) {}
};

class FunctionAST
{
    PrototypeAST *Proto;
    ExprAST *Body;
public:
    FunctionAST(PrototypeAST *proto, ExprAST *body)
    : Proto(proto), Body(body) {}
};
