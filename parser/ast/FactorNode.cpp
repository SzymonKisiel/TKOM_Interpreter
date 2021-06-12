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
        case FactorType::ID: {
            auto variables = context.getVariables();
            if (const auto variable = variables.find(id); variable != variables.end()) {
                {   //debug print
                    cout << "var: " << variable->first << " ";
                    std::visit(VisitPrintValue(), variable->second);
                    cout << endl;
                }
                return variable->second;
            }
            return variant<std::monostate, string, int, float>();
        }
        case FactorType::FUNCTION_CALL:
            cout << "TODO: Factor - function call\n";
            return variant<std::monostate, string, int, float>();
        case FactorType::EXPRESSION:
            return expression->evaluate(context);
        default:
            return variant<std::monostate, string, int, float>();
    }
}
