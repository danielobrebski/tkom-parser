//
//  Scanner.cpp
//  TKOM
//
//  Created by Daniel Obrebski on 11.05.2015.
//  Copyright (c) 2015 Daniel Obrebski. All rights reserved.
//

#include "Scanner.h"

Scanner::Scanner(std::string fileName)
{
    this->fileName = fileName;
    this->colIdx = 0;
    this->rowIdx = 0;
    this->srcIdx = -1;
    this->lastIdx = fileLength();
}

void Scanner::run()
{
    std::string temp;
    while(1)
    {
        temp = this->get();
        std::cout << temp;
        if(temp.find("EOF") != std::string::npos)
            break;
    }
}

int Scanner::fileLength()
{
    std::ifstream file;
    file.open(fileName, std::ios::binary);
    if(!file.good())
    {
        assert(file.good());
        return -1;
    }
    file.seekg(0, std::ios::end);
    unsigned int idx = (unsigned)file.tellg() - 1;
    return idx;
}

void Scanner::getBack()
{
    srcIdx--;
}

int Scanner::get()
{
    char temp;
    std::ifstream file;

    file.open(fileName, std::ios::binary);
    if(!file.good())
    {
        assert(file.good());
        return '-2';
    }
    srcIdx++;
    
    if(srcIdx >= 0)
    {
        file.seekg(srcIdx);
        file.get(temp);
        if(temp == '\n')
        {
            colIdx = 0;
            rowIdx++;
        }
    }
    
    if(srcIdx > lastIdx)
    {
        temp = EOF;
        Character endChar = *new Character(&temp, srcIdx, rowIdx, colIdx, fileName);
        std::string end = endChar.toString();
        temp = EOF;
        return temp;
    }
    else
    {
        char* ret = new char[1];
        ret[0] = temp;
        Character nChar = *new Character(ret, srcIdx, rowIdx, colIdx, fileName);
        std::string made = nChar.toString();
        colIdx++;
        return temp;
    }
    
    return '-3';
    
    
}


