//
//  Token.cpp
//  TKOM
//
//  Created by Daniel Obrebski on 11.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#include "Token.h"

Token::Token(TokenType type, std::string cargo) : type(type), cargo(cargo) {}

void Token::show()
{
    std::cout << cargo << " " << std::endl;
    
    return;

}

TokenType Token::getType()
{
    return type;
}

std::string Token::getCargo()
{
    return cargo;
}
