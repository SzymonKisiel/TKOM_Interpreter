#include "Context.h"
#include "PrintFunction.h"

Context::Context() {
    auto printFun = std::make_unique<PrintFunction>();
    addFunction("print", std::move(printFun));
}

//variables

void Context::addVariable(std::string id, std::variant<std::monostate, std::string, int, float> value) {
    const auto [it, success] = variables.insert(std::make_pair(id, value));
    if (!success)
        throw ExecutionException(std::string("Variable ").append(id).append(" already declared"));
}

void Context::assignToVariable(std::string id, std::variant<std::monostate, std::string, int, float> value) {
    if (auto variable = variables.find(id); variable != variables.end()) {
        variable->second = value;
    }
}

variant<std::monostate, string, int, float> Context::getVariableValue(std::string id) {
    if (const auto variable = variables.find(id); variable != variables.end()) {
        return variable->second;
    }
    throw ExecutionException(std::string("Use of undeclared variable: ").append(id));
}

void Context::deleteVariable(std::string id) {
    if (auto variable = variables.find(id); variable != variables.end()) {
        variables.erase(variable);
    }
}

//functions

void Context::addFunction(std::string id, std::shared_ptr<Function> function) {
    const auto [it, success] = functions.insert(std::make_pair(id, std::move(function)));
    if (!success)
        throw ExecutionException(std::string("Function ").append(id).append(" already declared"));
}

std::variant<std::monostate, string, int, float> Context::callFunction(std::string id, std::unique_ptr<ArgumentsNode> argumentsNode) {
    if (auto function = functions.find(id); function != functions.end()) {
        Context functionContext = *this;

        auto functionNode = function->second;
        auto parameters = functionNode->getParameters();

        if (parameters == nullptr)
            if (argumentsNode == nullptr)   //0 parameters, 0 arguments
                return function->second->execute(functionContext);
            else {                          //n parameters, 0 arguments
                auto arguments = argumentsNode->getArguments();
                throw ExecutionException(std::string("Wrong arguments amount, expected: ")
                                                 .append(std::to_string(0))
                                                 .append(", provided: ")
                                                 .append(std::to_string(arguments.size()))
                );
            }
        else
            if (argumentsNode == nullptr) { //0 parameters, n arguments
                auto paramIds = parameters->getIdentifiers();
                throw ExecutionException(std::string("Wrong arguments amount, expected: ")
                                                 .append(std::to_string(paramIds.size()))
                                                 .append(", provided: ")
                                                 .append(std::to_string(0))
                );
            }
            else {                          //n parameters, n arguments
                auto paramIds = parameters->getIdentifiers();
                auto arguments = argumentsNode->getArguments();
                if (arguments.size() != paramIds.size())
                    throw ExecutionException(std::string("Wrong arguments amount, expected: ")
                                                     .append(std::to_string(paramIds.size()))
                                                     .append(", provided: ")
                                                     .append(std::to_string(arguments.size()))
                    );
                auto itrArg = arguments.begin();
                auto itrParam = paramIds.begin();
                while(itrArg != arguments.end() && itrParam != paramIds.end()) {
                    functionContext.addVariable(*itrParam, (*itrArg)->evaluate(*this));
                    ++itrArg;
                    ++itrParam;
                }
                return function->second->execute(functionContext);
            }
    }
    else
        throw ExecutionException(std::string("Use of undeclared function: ").append(id));
}

void Context::print() {
    cout << "Context print:\n";
    // debug print
    for (auto variable: variables) {
        cout << variable.first << " = ";
        std::visit(VisitPrintValue(), variable.second);
        cout << endl;
    }
    for (auto function: functions) {
        cout << function.first << endl;
    }
}
