#include "FactorNode.h"
#include "../../execution/VisitPrint.h"

void FactorNode::setValue(Value value) {
    this->value = std::move(value);
    factorType = FactorType::VALUE;
}

//void FactorNode::setValue(std::variant<std::monostate, std::string, int, float> value) {
//    this->setValue(std::visit([](auto v) -> Value { return v; }, value));
//}

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
    switch (factorType) {
        case FactorType::VALUE:
            result.append(" = ")
                    .append(std::visit(VisitToString(), value));
            break;
        case FactorType::ID:
            result.append(" = ")
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

//std::string FactorNode::toString() {
//    switch (factorType) {
//        case FactorType::VALUE:
//            return std::string("FACTOR - ")
//                    .append(factorTypeNames[factorType])
//                    .append(" - ")
//                    .append(std::visit(VisitToString(), value));
//        case FactorType::ID:
//            return std::string("FACTOR - ")
//                    .append(factorTypeNames[factorType])
//                    .append(" - ")
//                    .append(id);
//        default:
//            return std::string("FACTOR - ").append(factorTypeNames[factorType]);
//
//    }
//}

//void FactorNode::print(int depth) {
//    for (int i = 0; i < depth; ++i)
//        std::cout << "  ";
//    std::cout << toString2() << std::endl;
//    if (expression != nullptr)
//        expression->print(depth+1);
//}

//variant<std::monostate, string, int, float> FactorNode::evaluate(Context & context) {
//    switch (factorType) {
//        case FactorType::VALUE:
//            return value;
//        case FactorType::ID:
//            return context.getVariableValue(id);
//        case FactorType::FUNCTION_CALL:
//            return functionCall->execute(context);
//        case FactorType::EXPRESSION:
//            return expression->evaluate(context);
//        default:
//            return variant<std::monostate, string, int, float>();
//    }
//}
