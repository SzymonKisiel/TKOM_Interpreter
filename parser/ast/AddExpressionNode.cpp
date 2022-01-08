#include "AddExpressionNode.h"
#include "../../execution/VisitOperations.h"

void AddExpressionNode::addOperand(std::unique_ptr<MultExpressionNode> node) {
    operands.push_back(std::move(node));
}

void AddExpressionNode::addOperation(TokenType addOperation) {
    addOperations.push_back(addOperation);
}

std::string AddExpressionNode::toString(int depth) {
    std::string result = std::string();
    for (int i = 0; i < depth; ++i)
        result.append(prefix);
    result.append("ADD_EXPRESSION");

    if (!addOperations.empty()) {
        for (const auto &operation: addOperations) {
            result.append(" ").append(tokenTypeToString(operation));
        }
    }
    result.append("\n");

    for (const auto &child: operands) {
        result.append(child->toString(depth+1));
    }
    return result;
}

std::variant<std::monostate, std::string, int, float> AddExpressionNode::evaluate(Context & context) {
    std::variant<std::monostate, std::string, int, float> lhs = operands[0]->evaluate(context);
    std::variant<std::monostate, std::string, int, float> rhs;
    TokenType operation;
    for (int i = 0; i < addOperations.size(); ++i) {
        operation = addOperations[i];
        rhs = operands[i+1]->evaluate(context);
        if (operation == TokenType::T_PLUS) {
            std::visit(VisitAdd(), lhs, rhs);
        }
        else if (operation == TokenType::T_MINUS) {
            std::visit(VisitSubstract(), lhs, rhs);
        }
        else if (operation == TokenType::T_OR) {
            std::visit(VisitOr(), lhs, rhs);
        }
    }
    return lhs;
}
