//
//  Character.h
//  TKOM
//
//  Created by Daniel Obrebski on 11.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#ifndef __TKOM__Character__
#define __TKOM__Character__

#include <stdio.h>
#include <string.h>
#include <sstream>

class Character
{
public:
    Character(char *cargo, int srcIdx, int rowIdx, int colIdx, std::string filename);
    Character(char cargo, int srcIdx, int rowIdx, int colIdx, std::string filename);
    std::string toString();
    char *cargo;
    int srcIdx;
    int rowIdx;
    int colIdx;
    std::string filename;
    
};

#endif /* defined(__TKOM__Character__) */
