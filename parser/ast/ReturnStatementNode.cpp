#include "ReturnStatementNode.h"
#include "../../execution/VisitPrint.h" //debug

void ReturnStatementNode::setReturnExpression(std::unique_ptr <ExpressionNode> returnExpression) {
    this->returnExpression = std::move(returnExpression);
}

std::string ReturnStatementNode::toString(int depth) const {
    std::string result = getPrefix(depth);
    result.append("RETURN_STATEMENT\n");

    if (returnExpression != nullptr)
        result.append(returnExpression->toString(depth + 1));

    return result;
}

Value ReturnStatementNode::execute(Context &context) const {
    return returnExpression->evaluate(context);
}
