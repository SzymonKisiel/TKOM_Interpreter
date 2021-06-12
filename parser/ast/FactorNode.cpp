#include "FactorNode.h"

void FactorNode::setValue(TokenType type, variant<std::monostate, string, int, float> value) {
    this->type = type;
    this->value = std::move(value);
    factorType = FactorType::VALUE;
}

void FactorNode::setId(std::string id) {
    this->id = std::move(id);
    factorType = FactorType::ID;
}

void FactorNode::setFunction(std::unique_ptr<FunctionCallNode> functionCall) {
    this->functionCall = std::move(functionCall);
    factorType = FactorType::FUNCTION_CALL;
}

void FactorNode::setGeo() {

}

void FactorNode::setExpression(std::unique_ptr<ExpressionNode> expression) {
    this->expression = std::move(expression);
}

void FactorNode::setNegative() {
    isPositive = false;
}

std::string FactorNode::toString() {
    return std::string("FACTOR - ").append(factorTypeNames[factorType]/*tokenTypeToString(type)*/);
}

void FactorNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
}

variant<std::monostate, string, int, float> FactorNode::evaluate(Context & context) {
    if (factorType == VALUE)
        return value;
    else
        return variant<std::monostate, string, int, float>();
}
