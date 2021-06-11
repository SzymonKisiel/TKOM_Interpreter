#include "AddExpressionNode.h"

void AddExpressionNode::addOperand(std::unique_ptr<MultExpressionNode> node) {
    operands.push_back(std::move(node));
}

void AddExpressionNode::addOperation(TokenType addOperation) {
    addOperations.push_back(addOperation);
}

std::string AddExpressionNode::toString() {
    std::string result("ADD_EXPRESSION");
    if (!addOperations.empty()) {
        result.append(" -");
        for (const auto &operation: addOperations) {
            result.append(" ").append(tokenTypeToString(operation));
        }
    }
    return result;
}

void AddExpressionNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
    for (const auto &child: operands) {
        child->print(depth+1);
    }
}

variant<std::monostate, string, int, float> AddExpressionNode::evaluate() {
    return variant<std::monostate, string, int, float>();
}
