//
//  Token.h
//  TKOM
//
//  Created by Daniel Obrebski on 11.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#ifndef __TKOM__Token__
#define __TKOM__Token__

#include <stdio.h>
#include <iostream>
#include "TokenType.h"
#include "Character.h"
#include <string>

class Token
{
public:
    Token(TokenType type, std::string cargo);
    void show();
    TokenType getType();
    std::string getCargo();
    
private:
    TokenType type;
    std::string cargo;
};



#endif /* defined(__TKOM__Token__) */
