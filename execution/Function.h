#ifndef _TKOM__INTERPRETER_FUNCTION_H
#define _TKOM__INTERPRETER_FUNCTION_H


#include "Context.h"
class Context;

class Function {
public:
    virtual void execute(Context & context) = 0;
};


#endif //_TKOM__INTERPRETER_FUNCTION_H
