#include "StringSource.h"

StringSource::StringSource(string source) {
    stringSource = std::move(source);
    stringIndex = 0;
    row = 1;
    column = -1;
}

char StringSource::getNextChar() {
    char c = stringSource[stringIndex];
    if (stringIndex >= stringSource.size())
        return EOF;

    ++stringIndex;
    if (c == '\n') {
        column = -1;
        ++row;
    }
    else {
        ++column;
    }
    return c;
}
