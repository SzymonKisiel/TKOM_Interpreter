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

void Context::addFunction(std::string id, std::shared_ptr<Function> function) {
    functions.insert(std::make_pair(id, std::move(function)));
}

//void Context::callFunction(std::string id, std::unique_ptr<ArgumentsNode> arguments) {
//    if (auto function = functions.find(id); function != functions.end()) {
//        Context functionContext;
//        function->second->execute(*this); //TODO: functionContext instead of *this !!!
//    }
//    else
//        throw ExecutionException(std::string("Function ").append(id).append(" not found"));
//}

std::variant<std::monostate, string, int, float> Context::callFunction(std::string id, std::unique_ptr<ArgumentsNode> argumentsNode) {
    if (auto function = functions.find(id); function != functions.end()) {
        Context functionContext;
        if (argumentsNode != nullptr) {
            auto arguments = argumentsNode->getArguments();

            auto parametersNode = function->second;
            auto parameters = parametersNode->getParameters();
            auto paramId = parameters->getIdentifiers();


            if (arguments.size() != paramId.size())
                throw ExecutionException(std::string("Wrong arguments amount, ")
                                              .append("expected: ")
                                              .append(std::to_string(paramId.size()))
                                              .append(", provided: ")
                                              .append(std::to_string(arguments.size()))
                                        );

            auto itrArg = arguments.begin();
//            std::vector<std::string> testParams = {"test1", "test2", "test3", "test4", "test5", "test6", "test7", "test8", "test9"};
//            auto itrParam = testParams.begin();
            auto itrParam = paramId.begin();
            while(itrArg != arguments.end() && itrParam != paramId.end()) {
                functionContext.addVariable(*itrParam, (*itrArg)->evaluate(*this));
                ++itrArg;
                ++itrParam;
            }
        }
//        this->print();
//        functionContext.print();

//        auto returnValue = function->second->execute(functionContext);
//        std::visit(VisitPrintValue(), returnValue); cout << endl;
//        return returnValue;

        return function->second->execute(functionContext);
    }
    else
        throw ExecutionException(std::string("Function ").append(id).append(" not found"));
}

void Context::print() {
    cout << "Context print:\n";
    // debug print
    for (auto variable: variables) {
        cout << variable.first << " = ";
        std::visit(VisitPrintValue(), variable.second);
        cout << endl;
    }
}
