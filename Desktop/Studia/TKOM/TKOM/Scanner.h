//
//  Scanner.h
//  TKOM
//
//  Created by Daniel Obrebski on 11.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//



#ifndef __TKOM__Scanner__
#define __TKOM__Scanner__

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
#include "Character.h"

class Scanner
{
public:
    Scanner(std::string fileName);
    int fileLength();
    int get();
    void getBack();
    void run();

private:
    std::string fileName;
    unsigned int colIdx;
    unsigned int rowIdx;
    unsigned int srcIdx;
    unsigned int lastIdx;
    
    
    
};

#endif /* defined(__TKOM__Scanner__) */
