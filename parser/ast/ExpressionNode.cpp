#include "ExpressionNode.h"
#include "AddExpressionNode.h"


void ExpressionNode::addOperand(std::unique_ptr<AddExpressionNode> node) {
    operands.push_back(std::move(node));
}

void ExpressionNode::addOperation(TokenType compOperation) {
    compOperations.push_back(compOperation);
}

std::string ExpressionNode::toString() {
    std::string result("EXPRESSION");
    if (!compOperations.empty()) {
        result.append(" -");
        for (const auto &operation: compOperations) {
            result.append(" ").append(tokenTypeToString(operation));
        }
    }
    return result;
}

void ExpressionNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
    for (const auto &child: operands) {
        child->print(depth+1);
    }
}

variant<std::monostate, string, int, float> ExpressionNode::evaluate() {
    return variant<std::monostate, string, int, float>();
}
