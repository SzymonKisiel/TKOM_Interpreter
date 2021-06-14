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
    void assignToVariable(std::string id, std::variant<std::monostate, std::string, int, float> value);
    variant<std::monostate, string, int, float> getVariableValue(std::string id);
    void deleteVariable(std::string id);
    void deleteAllVariables();

    void addFunction(std::string id, std::shared_ptr<Function> function);
    variant<std::monostate, string, int, float> callFunction(std::string id, std::shared_ptr<ArgumentsNode> arguments = nullptr);

    void print(std::string id = "");

    Context& operator=(Context& context) {
        this->functions = context.functions;
        return context;
    }
};


#endif //_TKOM__INTERPRETER_CONTEXT_H
