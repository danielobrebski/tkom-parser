//
//  ExpressionAst.cpp
//  TKOM
//
//  Created by Daniel Obrebski on 01.06.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#ifndef __TKOM__ExpressionAst__
#define __TKOM__ExpressionAst__

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

static std::map<std::string, double> variablesValues;

class ExprAST
{
public:
    virtual ~ExprAST() {};
    
    virtual double Evaluate(ExprAST *expr) { return 0; };
    virtual void EvaluateSubtree(ExprAST *expr) {};
    virtual std::string EvaluateVariable(ExprAST *expr) { return "0"; };
    virtual bool EvaluateCondition(ExprAST *expr) { return false; };
};


class NumberExprAST : public ExprAST
{
    double Val;
public:
    NumberExprAST(double val) : Val(val) {};
    
    double Evaluate(NumberExprAST *expr)
    {
        return Val;
    };
};

class VariableExprAST : public ExprAST
{
    std::string Name;
    ExprAST *RHS; //indexOperator
    double Val;
public:
    VariableExprAST(const std::string &name, ExprAST *rhs) : Name(name), RHS(rhs) {};
    
    double Evaluate(VariableExprAST *expr)
    {
        auto it = variablesValues.find(Name);
        if(it != variablesValues.end())
            return it->second;
        return 0;
    }
    
    std::string EvaluateVariable(VariableExprAST *expr)
    {
        if(RHS != nullptr)
            Name += RHS->EvaluateVariable(RHS);
        
        return Name;
    };
    
};

class AssignmentExprAST : public ExprAST
{
    std::string Op;
    ExprAST *LHS, *RHS; //LHS - variableExpr, RHS -
public:
    AssignmentExprAST(const std::string &op, ExprAST *lhs, ExprAST *rhs) : Op(op), LHS(lhs), RHS(rhs) {};
    
    void EvaluateSubtree(AssignmentExprAST *expr)
    {
        std::string temp = EvaluateVariable(LHS);
        auto it = variablesValues.find(temp);
        double temp1;
        if(it != variablesValues.end())
        {
            if(Op == "=")
            {
                temp1 = RHS->Evaluate(RHS);
                it->second = temp1;
            }
                
            else if(Op == "+=")
            {
                temp1 = RHS->Evaluate(RHS);
                it->second = it->second + temp1;
            }
                
            else if(Op == "-=")
            {
                temp1 = RHS->Evaluate(RHS);
                it->second = it->second - temp1;
            }
                
            else if(Op == "*=")
            {
                temp1 = RHS->Evaluate(RHS);
                it->second = it->second * temp1;
            }
                
            else if(Op == "/=")
            {
                temp1 = RHS->Evaluate(RHS);
                it->second = it->second / temp1;
            }
        }
    }
};

class InitialExprAST : public ExprAST
{
    ExprAST *LHS; //variable
    ExprAST *RHS; //assignable
    
public:
    InitialExprAST(ExprAST* lhs, ExprAST* rhs) : LHS(lhs), RHS(rhs) {};
    
    void EvaluateSubtree(InitialExprAST *expr)
    {
        std::string temp = LHS->EvaluateVariable(LHS);
        double temp1 = RHS->Evaluate(RHS);
        if(temp.find("[") != temp.npos)
            variablesValues.insert(std::pair<std::string, double> (temp, temp1));
        else
        {
            std::string name = temp.substr(0, temp.find("["));
            int first, second;
            std::size_t posb1 = temp.find("[");
            std::size_t pose1 = temp.find("]");
            first = stoi(temp.substr(posb1, pose1));
            
            std::size_t posb2 = temp.find("[");
            std::size_t pose2 = temp.find("]");
            second = stoi(temp.substr(posb2, pose2));
            
            for(int i = 0; i < first; i++)
            {
                for(int j = 0; j < second; j++)
                {
                    std::string toInsert = name+
                    "["+std::to_string(first)+"]"+"["+std::to_string(second)+"]";
                    variablesValues.insert(std::pair<std::string, double> (toInsert, 0));
                }
            }
            
        }
    }
};

class IndexExprAST : public ExprAST
{
    ExprAST *LHS; //assignable, notnullable
    ExprAST *RHS; //assignable, nullable
public:
    IndexExprAST(ExprAST *lhs, ExprAST *rhs) : LHS(lhs), RHS(rhs) {};
    
    std::string EvaluateVariable(IndexExprAST *expr)
    {
        std::string temp = "[";
        temp += std::to_string(LHS->Evaluate(LHS));
        temp += "]";
        
        if(RHS != nullptr)
        {
            temp += "[";
            temp += std::to_string(RHS->Evaluate(RHS));
            temp += "]";
        }
        return temp;
    };
};

class CallExprAST : public ExprAST
{
    ExprAST* Callee; //variable
    std::vector<ExprAST*> Args;
public:
    CallExprAST(ExprAST* callee, std::vector<ExprAST*> &args)
    : Callee(callee), Args(args) {};
    
    double Evaluate(CallExprAST *expr)
    {
        //std::string callee = Callee->EvaluateVariable(Callee);
        //std::function
        
        return 0;
    };
};

class ConditionExprAST : public ExprAST
{
    std::string Op;
    ExprAST *LHS, *RHS;
public:
    ConditionExprAST(const std::string &op, ExprAST *lhs, ExprAST *rhs) : Op(op), LHS(lhs), RHS(rhs) {};
    
    void EvaluateSubtree(ConditionExprAST *expr)
    {
        LHS->EvaluateSubtree(LHS);
        
        RHS->EvaluateSubtree(RHS);
    };
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
    LHS(lhs), MHS(mhs), RHS(rhs), Block(block) {};
    
    void EvaluateSubtree(ForExprAST *expr)
    {
        while(!LHS->empty())
        {
            ExprAST* temp = LHS->back();
            LHS->pop_back();
            temp->EvaluateSubtree(temp);
            
        }
        
        while(!RHS->empty())
        {
            ExprAST* temp = RHS->back();
            RHS->pop_back();
            temp->EvaluateSubtree(temp);
            
        }
        //while condition - Evaluate Block
        Block->Evaluate(Block);
        
    };
};

class IfExprAST : public ExprAST
{
    ExprAST *LHS; //condition
    ExprAST *MHS, *RHS;
public:
    IfExprAST(ExprAST *lhs, ExprAST *mhs, ExprAST *rhs) :
    LHS(lhs), MHS(mhs), RHS(rhs) {};
    
    void EvaluateSubtree(IfExprAST *expr)
    {
        //if condition
        MHS->Evaluate(MHS);
        
        //if not condition
        RHS->Evaluate(RHS);
        
    };
};

class WhileExprAST : public ExprAST
{
    ExprAST *LHS; //condition
    ExprAST *RHS;
public:
    WhileExprAST(ExprAST *lhs, ExprAST *rhs) : RHS(rhs), LHS(lhs) {};
    
    void EvaluateSubtree(WhileExprAST *expr)
    {
        //while condition
        RHS->Evaluate(RHS);
        
    };
};

class IncrementExprAST : public ExprAST
{
    std::string Op;
    ExprAST *OHS; //variable
public:
    IncrementExprAST(const std::string &op, ExprAST *ohs) : Op(op), OHS(ohs) {};
    
    void EvaluateSubtree(IncrementExprAST *expr)
    {
        std::string Name = OHS->EvaluateVariable(OHS);
        auto it = variablesValues.find(Name);
        if(it != variablesValues.end())
        {
            if(Op == "++")
                it->second++;
            else if(Op == "--")
                it->second--;
        }
    };
};

class ArithmeticExprAST : public ExprAST
{
    std::vector<std::string> Op;
    ExprAST* LHS;
    std::vector<ExprAST*> RHS;
public:
    ArithmeticExprAST(const std::vector<std::string> &op, ExprAST *lhs, const std::vector<ExprAST*> &rhs) :
    Op(op), LHS(lhs), RHS(rhs) {};
    
    double Evaluate(ArithmeticExprAST *expr)
    {
        while(!Op.empty())
        {
            std::string op = Op.back();
            Op.pop_back();
            ExprAST* rhs = RHS.back();
            RHS.pop_back();
            double temp1, temp2;
            
            if(op == "+")
            {
                temp1 = LHS->Evaluate(LHS);
                temp2 = rhs->Evaluate(rhs);
                return temp1 + temp2;
            }
            
            else if(op == "-")
            {
                temp1 = LHS->Evaluate(LHS);
                temp2 = rhs->Evaluate(rhs);
                return temp1 - temp2;
            }
            
            else if(op == "/")
            {
                temp1 = LHS->Evaluate(LHS);
                temp2 = rhs->Evaluate(rhs);
                return temp1 / temp2;
            }
            
            else if(op == "*")
            {
                temp1 = LHS->Evaluate(LHS);
                temp2 = rhs->Evaluate(rhs);
                return temp1 * temp2;
            }
            
        }
        return 0;
    };
};

class MatrixExprAST: public ExprAST
{
    std::vector<std::vector<double> > Vec;
public:
    MatrixExprAST(const std::vector<std::vector<double> > &vec) : Vec(vec) {};
    
    double Evaluate(MatrixExprAST *expr)
    {
        
        return 0;
    };
};

class PrototypeAST
{
    std::string Name;
    std::vector<std::string> Args;
public:
    PrototypeAST(const std::string &name, const std::vector<std::string> &args)
    : Name(name), Args(args) {};
};

class FunctionAST
{
    PrototypeAST *Proto;
    ExprAST *Body;
public:
    FunctionAST(PrototypeAST *proto, ExprAST *body)
    : Proto(proto), Body(body) {}
};

#endif /* defined( __TKOM__ExpressionAst__) */
