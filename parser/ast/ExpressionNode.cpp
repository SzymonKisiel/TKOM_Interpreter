#include "ExpressionNode.h"
#include "../../execution/VisitOperations.h"

void ExpressionNode::addOperand(std::unique_ptr<AddExpressionNode> node) {
    operands.push_back(std::move(node));
}

void ExpressionNode::addOperation(TokenType compOperation) {
    compOperations.push_back(compOperation);
}

std::string ExpressionNode::toString(int depth) {
    std::string result = std::string();
    for (int i = 0; i < depth; ++i)
        result.append(prefix);
    result.append("EXPRESSION");

    if (!compOperations.empty()) {
        for (const auto &operation: compOperations) {
            result.append(" ").append(tokenTypeToString(operation));
        }
    }
    result.append("\n");

    for (const auto &child: operands) {
        result.append(child->toString(depth+1));
    }
    return result;
}

Value ExpressionNode::evaluate(Context & context) {
    Value lhs = operands[0]->evaluate(context);
    Value rhs;
    TokenType operation;
    for (int i = 0; i < compOperations.size(); ++i) {
        operation = compOperations[i];
        rhs = operands[i+1]->evaluate(context);
        switch (operation) {
            case TokenType::T_LESS:
                lhs = std::visit(VisitLess(), lhs, rhs);
                break;
            case TokenType::T_GREATER:
                lhs = std::visit(VisitGreater(), lhs, rhs);
                break;
            case TokenType::T_LESS_OR_EQUAL:
                lhs = std::visit(VisitLessOrEqual(), lhs, rhs);
                break;
            case TokenType::T_GREATER_OR_EQUAL:
                lhs = std::visit(VisitGreaterOrEqual(), lhs, rhs);
                break;
            case TokenType::T_EQUAL:
                lhs = std::visit(VisitEqual(), lhs, rhs);
                break;
            case TokenType::T_NOT_EQUAL:
                lhs = std::visit(VisitNotEqual(), lhs, rhs);
                break;
        }
    }
    return lhs;
}
