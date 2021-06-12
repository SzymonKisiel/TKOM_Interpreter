#ifndef _TKOM__INTERPRETER_CONTEXT_H
#define _TKOM__INTERPRETER_CONTEXT_H

#include <map>
#include <string>
#include <variant>
#include <memory>

class Context {
    //std::map<std::string, std::unique_ptr<FunctionNode>> functions;
    std::map<std::string, std::variant<std::monostate, std::string, int, float>> variables;
public:
    const std::map<std::string, std::variant<std::monostate, std::string, int, float>> &getVariables() ;

public:
    void addVariable(std::string id, std::variant<std::monostate, std::string, int, float> value);
    void addFunction();
};


#endif //_TKOM__INTERPRETER_CONTEXT_H
