#include "FunctionNode.h"

void FunctionNode::setId(std::string id) {
    this->id = id;
}

void FunctionNode::setParameters(std::unique_ptr<ParametersNode> parameters) {
    this->parameters = std::move(parameters);
}

void FunctionNode::addStatement(std::unique_ptr<StatementNode> statement) {
    statements.push_back(std::move(statement));
}

void FunctionNode::setReturnType(TokenType returnType) {
    this->returnType = returnType;
}

std::string FunctionNode::toString() {
    return std::string("FUNCTION - ")
            .append(tokenTypeToString(returnType))
            .append(" ")
            .append(id);
}

void FunctionNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
    if (parameters != nullptr)
        parameters->print(depth+1);
    for (const auto &child: statements) {
        child->print(depth+1);
    }
}

variant<std::monostate, string, int, float> FunctionNode::execute(Context &context) {
    cout << "TODO: Function execute (" << id << ")\n";
    for (const auto& statement: statements) {
        auto value = statement->execute(context);
        if (!std::get_if<std::monostate>(&value)) {
            return value;
        }
    }
    return std::monostate();
}

const string &FunctionNode::getId() {
    return id;
}

std::shared_ptr<ParametersNode> FunctionNode::getParameters() {
    return parameters;
}
