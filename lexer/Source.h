#ifndef _TKOM__INTERPRETER_SOURCE_H
#define _TKOM__INTERPRETER_SOURCE_H


#include <fstream>

using namespace std;

class Source
{
protected:
    int row;
    int column;
public:
    virtual char getNextChar() = 0;
    const int getRow() {
        return row;
    }
    const int getColumn() {
        return column;
    }
};


#endif //_TKOM__INTERPRETER_SOURCE_H
