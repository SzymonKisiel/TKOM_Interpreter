#include "ReturnStatementNode.h"
#include "../../execution/VisitPrint.h" //debug

void ReturnStatementNode::setReturnExpression(std::unique_ptr <ExpressionNode> returnExpression) {
    this->returnExpression = std::move(returnExpression);
}

std::string ReturnStatementNode::toString(int depth) {
    std::string result = std::string();
    for (int i = 0; i < depth; ++i)
        result.append(prefix);
    result.append("RETURN_STATEMENT\n");

    if (returnExpression != nullptr)
        result.append(returnExpression->toString(depth + 1));

    return result;
}

variant<std::monostate, string, int, float> ReturnStatementNode::execute(Context &context) {
    return returnExpression->evaluate(context);
}
