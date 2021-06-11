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
    variant<std::monostate, string, int, float> lhs = operands[0]->evaluate();
    variant<std::monostate, string, int, float> rhs;
    TokenType operation;
    for (int i = 0; i < compOperations.size(); ++i) {
        operation = compOperations[i];
        rhs = operands[i+1]->evaluate();
        switch (operation) {
            case TokenType::T_LESS:
                lhs = std::visit(VisitLess(), lhs, rhs);
                break;
            case TokenType::T_GREATER:
                break;
            case TokenType::T_LESS_OR_EQUAL:
                break;
            case TokenType::T_GREATER_OR_EQUAL:
                break;
            case TokenType::T_EQUAL:
                break;
            case TokenType::T_NOT_EQUAL:
                break;
            default:
                ; //ExecutionException
        }
    }
    std::visit(VisitPrint(), lhs);
    return lhs;
}
