//
//  Lexer.h
//  TKOM
//
//  Created by Daniel Obrebski on 11.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#ifndef __TKOM__Lexer___
#define __TKOM__Lexer___

#include <stdio.h>
#include <string>
#include "Token.h"
#include "TokenType.h"
#include "Scanner.h"
#include <ctype.h>

class Lexer
{
public:
    Lexer(Scanner scan);
    Token getToken();
    int getColIdx();
    int getRowIdx();
    
private:
    Scanner scan;
    int colIdx;
    int rowIdx;
};

#endif /* defined(__TKOM__Lexer___) */
