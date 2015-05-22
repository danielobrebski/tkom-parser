//
//  Character.cpp
//  TKOM
//
//  Created by Daniel Obrebski on 11.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#include "Character.h"

Character::Character(char *cargo, int srcIdx, int rowIdx, int colIdx, std::string filename)
{
    this->cargo = cargo;
    this->srcIdx = srcIdx;
    this->rowIdx = rowIdx;
    this->colIdx = colIdx;
    this->filename = filename;
}


std::string Character::toString()
{
    if(cargo[0] == ' ')
    {
        strcpy(cargo, "     space");
    }
    
    if(cargo[0] == '\n')
    {
        strcpy(cargo, "    newline");
    }
    
    if(cargo[0] == '\t')
    {
        strcpy(cargo,  "    tab");
    }
    
    if(cargo[0] == EOF)
    {
        strcpy(cargo, "    eof");
    }
    
    else
    {
        strcpy(cargo, &cargo[0]);
    }
    
    std::stringstream ss;
    ss << this->rowIdx << "       " << this->colIdx << "      " << this->cargo << '\n';
    std::string output = ss.str();
    return output;
    
}