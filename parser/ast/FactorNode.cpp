#include "FactorNode.h"
#include "../../execution/VisitPrint.h"
#include "../../execution/VisitNegate.h"

void FactorNode::setValue(Value value) {
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

std::string FactorNode::toString(int depth) {
    std::string result = std::string();
    for (int i = 0; i < depth; ++i)
        result.append(prefix);
    result.append("FACTOR ")
            .append(factorTypeNames[factorType]);
    std::string sign = "";
    if (this->isPositive)
        sign = "-";
    switch (factorType) {
        case FactorType::VALUE:
            if (std::get_if<GeographicDistance>(&value)) {
                result.append(" = ")
                        .append(std::visit(VisitToString(), value));
            }
            else {
                result.append(" = ")
                        .append(sign)
                        .append(std::visit(VisitToString(), value));
            }
            break;
        case FactorType::ID:
            result.append(" = ")
                    .append(sign)
                    .append(id);
            break;
        case FactorType::FUNCTION_CALL:
            if (functionCall != nullptr)
                result.append(functionCall->toString(depth+1));
            break;
        case FactorType::EXPRESSION:
            if (expression != nullptr)
                result.append(expression->toString(depth+1));
            break;
    }

    result.append("\n");
    return result;
}

Value FactorNode::evaluate(Context & context) {
    Value returnValue;
    switch (factorType) {
        case FactorType::VALUE:
            if (isPositive)
                return value;
            else
                return std::visit(VisitNegate(), value);
        case FactorType::ID:
            returnValue = context.getVariableValue(id);
            if (isPositive)
                return returnValue;
            else
                return std::visit(VisitNegate(), returnValue);
        case FactorType::FUNCTION_CALL:
            returnValue = functionCall->execute(context);
            if (isPositive)
                return returnValue;
            else
                return std::visit(VisitNegate(), returnValue);
        case FactorType::EXPRESSION:
            returnValue = expression->evaluate(context);
            if (isPositive)
                return returnValue;
            else
                return std::visit(VisitNegate(), returnValue);
        default:
            return Value();
    }
}
