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

variant<std::monostate, string, int, float> AddExpressionNode::evaluate(Context & context) {
    variant<std::monostate, string, int, float> lhs = operands[0]->evaluate(context);
    variant<std::monostate, string, int, float> rhs;
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
