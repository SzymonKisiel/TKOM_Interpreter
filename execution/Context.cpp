#include "Context.h"

void Context::addVariable(std::string id, std::variant<std::monostate, std::string, int, float> value) {
    variables.insert({id, value});
}

const std::map<std::string, std::variant<std::monostate, std::string, int, float>> &Context::getVariables() {
    return variables;
}

//void Context::addFunction(std::string id, std::unique_ptr<FunctionNode> function) {
//    functions.insert({id, std::move(function)});
//}
//
//const std::map<std::string, std::unique_ptr<FunctionNode>> &Context::getFunctions() {
//    return functions;
//}

void Context::assignToVariable(std::string id, std::variant<std::monostate, std::string, int, float> value) {
    if (auto variable = variables.find(id); variable != variables.end()) {
        variable->second = value;
    }
}
