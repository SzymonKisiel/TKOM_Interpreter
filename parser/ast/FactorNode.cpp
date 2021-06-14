#include "FactorNode.h"
#include "../../execution/VisitPrint.h"

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

void FactorNode::setExpression(std::unique_ptr<ExpressionNode> expression) {
    this->expression = std::move(expression);
    factorType = FactorType::EXPRESSION;
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
    if (expression != nullptr)
        expression->print(depth+1);
}

variant<std::monostate, string, int, float> FactorNode::evaluate(Context & context) {
    switch (factorType) {
        case FactorType::VALUE:
            return value;
        case FactorType::ID:
            return context.getVariableValue(id);
        case FactorType::FUNCTION_CALL:
            return functionCall->execute(context);
        case FactorType::EXPRESSION:
            return expression->evaluate(context);
        default:
            return variant<std::monostate, string, int, float>();
    }
}
