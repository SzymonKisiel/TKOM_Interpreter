#include "ReturnStatementNode.h"
#include "../../execution/VisitPrint.h" //debug

void ReturnStatementNode::setReturnExpression(std::unique_ptr <ExpressionNode> returnExpression) {
    this->returnExpression = std::move(returnExpression);
}

std::string ReturnStatementNode::toString() {
    return "RETURN_STATEMENT";
}

void ReturnStatementNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
    if (returnExpression != nullptr)
        returnExpression->print(depth + 1);
}

variant<std::monostate, string, int, float> ReturnStatementNode::execute(Context &context) {
    return returnExpression->evaluate(context);
}
