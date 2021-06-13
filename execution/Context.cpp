#include "Context.h"
#include "PrintFunction.h"

Context::Context() {
    auto printFun = std::make_unique<PrintFunction>();
    addFunction("print", std::move(printFun));
}

//variables

void Context::addVariable(std::string id, std::variant<std::monostate, std::string, int, float> value) {
    variables.insert(std::make_pair(id, value));
}

const std::map<std::string, std::variant<std::monostate, std::string, int, float>> &Context::getVariables() {
    return variables;
}

void Context::assignToVariable(std::string id, std::variant<std::monostate, std::string, int, float> value) {
    if (auto variable = variables.find(id); variable != variables.end()) {
        variable->second = value;
    }
}

void Context::deleteVariable(std::string id) {
    if (auto variable = variables.find(id); variable != variables.end()) {
        variables.erase(variable);
    }
}

//functions

void Context::addFunction(std::string id, std::unique_ptr<Function> function) {
    functions.insert(std::make_pair(id, std::move(function)));
}

const std::map<std::string, std::unique_ptr<Function>> &Context::getFunctions() {
    return functions;
}

void Context::callFunction(std::string id, std::unique_ptr<ArgumentsNode> arguments = nullptr) {
    if (auto function = functions.find(id); function != functions.end()) {
        Context functionContext;
        function->second->execute(*this); //TODO: functionContext instead of *this !!!
    }
    else
        throw ExecutionException(std::string("Function ").append(id).append(" not found"));
}

