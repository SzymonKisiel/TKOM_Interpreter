#ifndef _TKOM__INTERPRETER_CONTEXT_H
#define _TKOM__INTERPRETER_CONTEXT_H

#include <map>
#include <stack>
#include <string>
#include <variant>
#include <memory>
#include "Function.h"
#include "../parser/ast/ArgumentsNode.h"

using Value = std::variant<std::monostate, std::string, int, float,
        GeographicCoordinate, GeographicDistance, GeographicPosition>;

class ArgumentsNode;

class Context {
    std::map<std::string, std::shared_ptr<Function>> functions;
    std::map<std::string, Value> variables;
    std::stack<std::string> variablesStack;
    std::stack<int> variablesCountStack;
public:
    Context();
    ~Context();
    void enterScope();
    void exitScope();

    void addVariable(std::string id, Value value);
    void assignToVariable(std::string id, Value value);
    Value getVariableValue(std::string id);
    void deleteVariable(std::string id);
    void deleteAllVariables();

    void addFunction(std::string id, std::shared_ptr<Function> function);
    Value callFunction(std::string id, std::shared_ptr<ArgumentsNode> arguments = nullptr, bool checkType = true);

    void print(std::string id = "");

    Context& operator=(const Context& context) {
        this->functions = context.functions;
        return *this;
    }
};


#endif //_TKOM__INTERPRETER_CONTEXT_H
