#include "MultExpressionNode.h"

void MultExpressionNode::addOperand(std::unique_ptr<FactorNode> node) {
    operands.push_back(std::move(node));
}

void MultExpressionNode::addOperation(TokenType multOperation) {
    multOperations.push_back(multOperation);
}

std::string MultExpressionNode::toString() {
    std::string result("MULT_EXPRESSION");
    if (!multOperations.empty()) {
        result.append(" -");
        for (const auto &operation: multOperations) {
            result.append(" ").append(tokenTypeToString(operation));
        }
    }
    return result;
}

void MultExpressionNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
    for (const auto &child: operands) {
        child->print(depth+1);
    }
}

//variant<std::monostate, string, int, float> MultExpressionNode::evaluate(Context & context) {
//    variant<std::monostate, string, int, float> lhs = operands[0]->evaluate(context);
//    variant<std::monostate, string, int, float> rhs;
//    TokenType operation;
//    for (int i = 0; i < multOperations.size(); ++i) {
//        operation = multOperations[i];
//        rhs = operands[i+1]->evaluate(context);
//        if (operation == TokenType::T_MUL) {
//            std::visit(VisitMult(), lhs, rhs);
//        }
//        else if (operation == TokenType::T_DIV) {
//            std::visit(VisitDiv(), lhs, rhs);
//        }
//        else if (operation == TokenType::T_AND) {
//            std::visit(VisitAnd(), lhs, rhs);
//        }
//    }
//    return lhs;
//}
