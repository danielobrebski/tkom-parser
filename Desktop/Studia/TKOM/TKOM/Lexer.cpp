//
//  Lexer.cpp
//  TKOM
//
//  Created by Daniel Obrebski on 11.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#include "Lexer.h"

Lexer::Lexer(Scanner scan):scan(scan)
{
    colIdx = scan.getColIdx();
    rowIdx = scan.getRowIdx();
}

Token Lexer::getToken()
{
    static std::string IdentifierStr;
    static double numVal;
    static int LastChar = ' ';
    
    colIdx = scan.getColIdx();
    rowIdx = scan.getRowIdx();
    
    LastChar = scan.get();
    
    
    // Skip any whitespace.
    while (isspace(LastChar) && LastChar != EOF)
        LastChar = scan.get();
    
    if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
        IdentifierStr = LastChar;
        while (isalnum((LastChar = scan.get())) || LastChar == 95)
            IdentifierStr += LastChar;
        
        scan.getBack();
        
        if (IdentifierStr == "static")
        {
            Token tok = *new Token(TokenType::Static, "static");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "if")
        {
            Token tok = *new Token(TokenType::If, "if");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "for")
        {
            Token tok = *new Token(TokenType::For, "for");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "else")
        {
            Token tok = *new Token(TokenType::Else, "else");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "while")
        {
            Token tok = *new Token(TokenType::While, "while");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "return")
        {
            Token tok = *new Token(TokenType::Return, "return");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "int")
        {
            Token tok = *new Token(TokenType::Int, "int");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "void")
        {
            Token tok = *new Token(TokenType::Void, "void");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "long")
        {
            Token tok = *new Token(TokenType::Long, "long");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "float")
        {
            Token tok = *new Token(TokenType::Float, "float");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "double")
        {
            Token tok = *new Token(TokenType::Double, "double");
            //tok.show();
            return tok;
        }
        
        if (IdentifierStr == "and")
        {
            Token tok = *new Token(TokenType::And, "and");
            //tok.show();
            return tok;
        }

        
        if (IdentifierStr == "or")
        {
            Token tok = *new Token(TokenType::Or, "or");
            //tok.show();
            return tok;
        }

        Token tok = *new Token(TokenType::Ident, IdentifierStr);
        
        //tok.show();
        return tok;
        

    }
    
    if (isdigit(LastChar) || LastChar == '.') {   // Number: [0-9.]+
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = scan.get();
        } while (isdigit(LastChar) || LastChar == '.');
        
        if(NumStr == ".")
        {
            return *new Token(TokenType::Unknown, "");
        }
        numVal = strtod(NumStr.c_str(), 0);
        scan.getBack();
        Token tok = *new Token(TokenType::Number, std::to_string(numVal));
        //tok.show();
        return tok;
    }

    if(LastChar == '+')
    {
        if((LastChar = scan.get()) == '+')
        {
            Token tok = *new Token(TokenType::Increment, "increment");
            //tok.show();
            return tok;
            
        }
        if(LastChar == '=')
        {
            Token tok = *new Token(TokenType::PlusEqual, "plusequal");
            //tok.show();
            return tok;
        }
        
        scan.getBack();
        Token tok = *new Token(TokenType::Plus, "plus");
        //tok.show();
        return tok;
        
        
    }
    
    if(LastChar == '-')
    {
        if((LastChar = scan.get()) == '-')
        {
            Token tok = *new Token(TokenType::Decrement, "decrement");
            //tok.show();
            return tok;
        }
        if(LastChar == '=')
        {
            Token tok = *new Token(TokenType::MinusEqual, "minusequal");
            //tok.show();
            return tok;
        }
        scan.getBack();
        Token tok = *new Token(TokenType::Minus, "minus");
        //tok.show();
        return tok;
    }
    
    if(LastChar == '=')
    {
        if((LastChar = scan.get()) == '=')
        {
            Token tok = *new Token(TokenType::Equal, "equal");
            //tok.show();
            return tok;
        }
        
        scan.getBack();
        Token tok = *new Token(TokenType::Assign, "assign");
        //tok.show();
        return tok;
    }
    
    if(LastChar == '*')
    {
        if((LastChar = scan.get()) == '=')
        {
            Token tok = *new Token(TokenType::MultiplyEqual, "multiplyequal");
            //tok.show();
            return tok;
        }
        scan.getBack();
        Token tok = *new Token(TokenType::Multiply, "multiply");
        //tok.show();
        return tok;
        
    }
    
    if(LastChar == '!')
    {
        if((LastChar = scan.get()) == '=')
        {
            Token tok = *new Token(TokenType::NotEqual, "notequal");
            //tok.show();
            return tok;
        }
        scan.getBack();
        Token tok = *new Token(TokenType::Exclamation, "exclamation");
        //tok.show();
        return tok;
        
    }
    
    if(LastChar == '&')
    {
        if((LastChar = scan.get()) == '&')
        {
            Token tok = *new Token(TokenType::And, "&&");
            //tok.show();
            return tok;
        }
    }
    
    if(LastChar == '|')
    {
        if((LastChar = scan.get()) == '|')
        {
            Token tok = *new Token(TokenType::Or, "||");
            //tok.show();
            return tok;
        }
    }
    
    
    if (LastChar == '/')
    {
        
        if((LastChar = scan.get()) == '/')
        {
            do LastChar = scan.get();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
            scan.getBack();
            Token tok = *new Token(TokenType::Comment, "comment");
            //tok.show();
            return tok;
        }
        
        
        if(LastChar == '=')
        {
            Token tok = *new Token(TokenType::DivideEqual, "divideequal");
            //tok.show();
            return tok;
        }
        scan.getBack();
        Token tok = *new Token(TokenType::Divide, "divide");
        //tok.show();
        return tok;
    }

    
    if(LastChar == '<')
    {
        if((LastChar = scan.get()) == '<')
        {
            Token tok = *new Token(TokenType::LeftLogicalShift, "LeftLogicalShift");
            //tok.show();
            return tok;
            
        }
        if(LastChar == '=')
        {
            Token tok = *new Token(TokenType::LessThanOrEqual, "lessthenorequal");
            //tok.show();
            return tok;
        }
        scan.getBack();
        Token tok = *new Token(TokenType::LessThan, "lessthan");
        //tok.show();
        return tok;
    }
    
    if(LastChar == '>')
    {
        if((LastChar = scan.get()) == '>')
        {
            Token tok = *new Token(TokenType::RightLogicalShift, "rightlogicalshift");
            //tok.show();
            return tok;
            
        }
        if(LastChar == '=')
        {
            Token tok = *new Token(TokenType::MoreThanOrEqual, "morethanorequal");
            //tok.show();
            return tok;
        }
        scan.getBack();
        Token tok = *new Token(TokenType::MoreThan, "morethan");
        //tok.show();
        return tok;
    }
    
    if(LastChar == '[')
    {
        Token tok = *new Token(TokenType::LeftBracket, "leftbracket");
        //tok.show();
        return tok;
    }
    
    if(LastChar == ']')
    {
        Token tok = *new Token(TokenType::RightBracket, "rightbracket");
        //tok.show();
        return tok;
    }
    
    if(LastChar == '{')
    {
        Token tok = *new Token(TokenType::LeftBrace, "leftbrace");
        //tok.show();
        return tok;
    }
    
    if(LastChar == '}')
    {
        Token tok = *new Token(TokenType::RightBrace, "rightbrace");
        //tok.show();
        return tok;
    }
    
    if(LastChar == '(')
    {
        Token tok = *new Token(TokenType::LeftParenthes, "leftparenthes");
        //tok.show();
        return tok;
    }
    
    if(LastChar == ')')
    {
        Token tok = *new Token(TokenType::RightParenthes, "rightparenthes");
        //tok.show();
        return tok;
    }
    
    if(LastChar == ';')
    {
        Token tok = *new Token(TokenType::SemiCollon, "semicollon");
        //tok.show();
        return tok;
    }
    
    if(LastChar == ':')
    {
        Token tok = *new Token(TokenType::Collon, "collon");
        //tok.show();
        return tok;
    }
    
    if(LastChar == ',')
    {
        Token tok = *new Token(TokenType::Comma, "comma");
        //tok.show();
        return tok;
    }
    
    if(LastChar == '"')
    {
        Token tok = *new Token(TokenType::Quote, "quote");
        //tok.show();
        return tok;
    }
    

    
    if(LastChar == EOF)
    {
        Token tok = *new Token(TokenType::Eof, "eof");
        //tok.show();
        return tok;
    }
    
    
    return *new Token(TokenType::Unknown, "");
    
    
}

int Lexer::getColIdx()
{
    return colIdx;
}

int Lexer::getRowIdx()
{
    return rowIdx;
}
