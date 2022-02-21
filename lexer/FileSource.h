#ifndef _TKOM__INTERPRETER_FILESOURCE_H
#define _TKOM__INTERPRETER_FILESOURCE_H


#include "Source.h"

class FileSource : public Source {
    fstream file;
public:
    FileSource(string filename) {
        file.open(std::move(filename), ios::in);
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


#endif //_TKOM__INTERPRETER_FILESOURCE_H
