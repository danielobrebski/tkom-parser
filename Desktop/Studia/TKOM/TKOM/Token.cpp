//
//  Token.cpp
//  TKOM
//
//  Created by Daniel Obrebski on 11.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#include "Token.h"

Token::Token(TokenType type, std::string cargo)
{
    this->type = type;
    this->cargo = cargo;
}

void Token::show()
{
    if(type == TokenType::Ident)
    {
        std::cout << "Type: id " << std::endl;
        std::cout << "Cargo: " << cargo << std::endl;
        return;
    }
    
    if(type == TokenType::Number)
    {
        std::cout << "Type: Number " << std::endl;
        std::cout << "Cargo: " << cargo << std::endl;
        return;
    }
    std::cout << "Type: " << (int)type << std::endl;
    std::cout << "Cargo: " << cargo << std::endl;
    
    return;

}

TokenType Token::getType()
{
    return type;
}
