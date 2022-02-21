#include "FunctionNode.h"
#include "../../execution/VisitCheckType.h"

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

std::string FunctionNode::toString(int depth) const {
    std::string result = getPrefix(depth);
    result.append("FUNCTION ")
            .append(tokenTypeToString(returnType))
            .append(" ")
            .append(id)
            .append("\n");

    if (parameters != nullptr)
        result.append(parameters->toString(depth+1));
    for (const auto &child: statements) {
        result.append(child->toString(depth+1));
    }

    return result;
}

Value FunctionNode::execute(Context &context) const {
    for (const auto& statement: statements) {
        auto value = statement->execute(context);
        if (!std::get_if<std::monostate>(&value)) {
            std::variant<TokenType> returnTypeV = returnType;
            if (!std::visit(VisitCheckType(), value, returnTypeV))
                throw ExecutionException(std::string("Wrong return value type in '")
                                                 .append(id).append("' function, expected ")
                                                 .append(tokenTypeToString(returnType))
                );
            return value;
        }
    }
    return std::monostate();
}

const string &FunctionNode::getId() const {
    return id;
}

std::shared_ptr<ParametersNode> FunctionNode::getParameters() const {
    return parameters;
}
