#ifndef _TKOM__INTERPRETER_SOURCE_H
#define _TKOM__INTERPRETER_SOURCE_H


#include <fstream>

using namespace std;

class Source
{
    ifstream file;
    int row;
    int column;

public:
    Source(string filename) {
        file.open(filename, ios::in);
        row = 1;
        column = -1;
    }
    char getNextChar() {
        char c = file.get();
        if (c == '\n') {
            column = -1;
            ++row;
        }
        else {
            ++column;
        }
        return c;
    }
    const int getRow() {
        return row;
    }
    const int getColumn() {
        return column;
    }
};


#endif //_TKOM__INTERPRETER_SOURCE_H
