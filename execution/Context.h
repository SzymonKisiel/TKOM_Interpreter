#ifndef _TKOM__INTERPRETER_CONTEXT_H
#define _TKOM__INTERPRETER_CONTEXT_H

#include <map>
#include <string>
#include <variant>
#include <memory>
#include "Function.h"
#include "../parser/ast/ArgumentsNode.h"
class ArgumentsNode;

class Context {
    std::map<std::string, std::shared_ptr<Function>> functions;
    std::map<std::string, std::variant<std::monostate, std::string, int, float>> variables;
public:
    Context();
    void addVariable(std::string id, std::variant<std::monostate, std::string, int, float> value);
    const std::map<std::string, std::variant<std::monostate, std::string, int, float>> &getVariables();
    void assignToVariable(std::string id, std::variant<std::monostate, std::string, int, float> value);
    void deleteVariable(std::string id);

    void addFunction(std::string id, std::shared_ptr<Function> function);
    const std::map<std::string, std::shared_ptr<Function>> &getFunctions();
    variant<std::monostate, string, int, float> callFunction(std::string id, std::unique_ptr<ArgumentsNode> arguments = nullptr);

    void print();
};


#endif //_TKOM__INTERPRETER_CONTEXT_H
