#ifndef SOURCE_H
#define SOURCE_H

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
    ~Source() {
        file.close();
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
    int getRow() {
        return row;
    }
    int getColumn() {
        return column;
    }
};

#endif // SOURCE_H
