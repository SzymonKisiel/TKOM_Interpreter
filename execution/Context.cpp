#include "Context.h"
#include "PrintFunction.h"
#include "VisitCheckType.h"
#include "VisitPrint.h"

Context::Context() {
    enterScope();
    auto printFun = std::make_unique<PrintFunction>();
    addFunction("print", std::move(printFun));
}

Context::~Context() {
    exitScope();
}

void Context::enterScope() {
    variablesCountStack.push(0);
}

void Context::exitScope() {
    auto localCount = variablesCountStack.top();
    for (int i = 0; i < localCount; ++i) {
        auto variableToDelete = variablesStack.top();
        deleteVariable(variableToDelete);
        variablesStack.pop();
    }
    variablesCountStack.pop();
}


//variables

void Context::addVariable(std::string id, Value value) {
    const auto [it, success] = variables.insert(std::make_pair(id, value));
    if (!success)
        throw ExecutionException(std::string("Variable ").append(id).append(" already declared"));

    variablesCountStack.top()++;
    variablesStack.push(id);
}

void Context::assignToVariable(std::string id, Value value) {
    if (auto variable = variables.find(id); variable != variables.end()) {
        auto& oldValue = variable->second;
        if (!std::visit(VisitCompareType(), oldValue, value))
            throw ExecutionException(std::string("Can't assign value to ").append(id));
        oldValue = value;
    }
    else
        throw ExecutionException(std::string("Use of undeclared variable: ").append(id));
}

Value Context::getVariableValue(std::string id) {
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

void Context::deleteAllVariables() {
    variables.clear();
}

//functions

void Context::addFunction(std::string id, std::shared_ptr<Function> function) {
    const auto [it, success] = functions.insert(std::make_pair(id, std::move(function)));
    if (!success)
        throw ExecutionException(std::string("Function ").append(id).append(" already declared"));
}

Value Context::callFunction(std::string id, std::shared_ptr<ArgumentsNode> argumentsNode) {
    if (auto function = functions.find(id); function != functions.end()) {
        Context functionContext = *this;
        functionContext.deleteAllVariables();

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

void Context::print(std::string id) {
    cout << "Context print {\n";
    // debug print
    for (auto variable: variables) {
        cout << '\t' << variable.first << " = ";
        std::visit(VisitPrintValue(), variable.second);
        cout << endl;
    }
    for (auto function: functions) {
        cout << '\t' << function.first << endl;
    }
    cout << "}\n";
}
