#ifndef _TKOM__INTERPRETER_STRINGSOURCE_H
#define _TKOM__INTERPRETER_STRINGSOURCE_H


#include "Source.h"

class StringSource : public Source {
    std::string stringSource;
    int stringIndex;
public:
    StringSource(std::string source);
    char getNextChar();
};


#endif //_TKOM__INTERPRETER_STRINGSOURCE_H
