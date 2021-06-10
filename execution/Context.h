#ifndef _TKOM__INTERPRETER_CONTEXT_H
#define _TKOM__INTERPRETER_CONTEXT_H

#include <map>
#include <string>
#include <variant>
#include <memory>
#include <FunctionNode.h>

class Context {
    std::map<std::string, std::unique_ptr<FunctionNode>> variables;
    std::map<std::string, std::variant<std::string, int, float>> functions;
public:
    void addVariable();
    void addFunction();
};


#endif //_TKOM__INTERPRETER_CONTEXT_H
