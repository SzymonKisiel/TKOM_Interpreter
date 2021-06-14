#ifndef _TKOM__INTERPRETER_FUNCTION_H
#define _TKOM__INTERPRETER_FUNCTION_H

#include <memory>
#include "Context.h"
class Context;
class ParametersNode;

class Function {
public:
    virtual void execute(Context & context) = 0;
    virtual std::shared_ptr<ParametersNode> getParameters() {
        return nullptr;
    };
};


#endif //_TKOM__INTERPRETER_FUNCTION_H
