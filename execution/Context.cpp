#include "Context.h"

void Context::addVariable(std::string id, std::variant<std::monostate, std::string, int, float> value) {
    variables.insert({id, value});
}

const std::map<std::string, std::variant<std::monostate, std::string, int, float>> &Context::getVariables() {
    return variables;
}
