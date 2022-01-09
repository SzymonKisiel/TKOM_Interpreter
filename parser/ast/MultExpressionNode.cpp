#include "MultExpressionNode.h"
#include "../../execution/VisitOperations.h"

void MultExpressionNode::addOperand(std::unique_ptr<FactorNode> node) {
    operands.push_back(std::move(node));
}

void MultExpressionNode::addOperation(TokenType multOperation) {
    multOperations.push_back(multOperation);
}

std::string MultExpressionNode::toString(int depth) {
    std::string result = std::string();
    for (int i = 0; i < depth; ++i)
        result.append(prefix);
    result.append("MULT_EXPRESSION");

    if (!multOperations.empty()) {
        for (const auto &operation: multOperations) {
            result.append(" ").append(tokenTypeToString(operation));
        }
    }
    result.append("\n");

    for (const auto &child: operands) {
        result.append(child->toString(depth+1));
    }
    return result;
}

Value MultExpressionNode::evaluate(Context & context) {
    Value lhs = operands[0]->evaluate(context);
    Value rhs;
    TokenType operation;
    for (int i = 0; i < multOperations.size(); ++i) {
        operation = multOperations[i];
        rhs = operands[i+1]->evaluate(context);
        if (operation == TokenType::T_MUL) {
            lhs = std::visit(VisitMult(), lhs, rhs);
        }
        else if (operation == TokenType::T_DIV) {
            lhs = std::visit(VisitDiv(), lhs, rhs);
        }
        else if (operation == TokenType::T_AND) {
            // TODO lhs = ...
            std::visit(VisitAnd(), lhs, rhs);
        }
    }
    return lhs;
}
