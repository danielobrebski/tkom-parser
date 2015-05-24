//
//  main.cpp
//  TKOM
//
//  Created by Daniel Obrebski on 11.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#include <iostream>
#include "Scanner.h"
#include "Lexer.h"
#include "TokenType.h"
#include "Parser.h"
#include "Token.h"

int main()
{
    std::string filename = "/Users/dani/Desktop/Studia/a/a/main.c";
    Scanner scan = *new Scanner(filename);
    Lexer lex = *new Lexer(scan);
    Parser par = *new Parser(lex);
    
    par.program();

    

    
}
