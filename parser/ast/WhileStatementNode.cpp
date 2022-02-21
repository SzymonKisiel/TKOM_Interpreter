#include "WhileStatementNode.h"
#include "../../execution/VisitCondition.h"

void WhileStatementNode::setCondition(std::unique_ptr<ExpressionNode> node) {
    if (node != nullptr)
        condition = std::move(node);
}

void WhileStatementNode::setStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr)
        statement = std::move(node);
}

std::string WhileStatementNode::toString(int depth) const {
    std::string result = getPrefix(depth);
    result.append("WHILE_STATEMENT\n");

    result.append(condition->toString(depth+1));
    result.append(statement->toString(depth+1));

    return result;
}

Value WhileStatementNode::execute(Context &context) const {
    auto cond = condition->evaluate(context);
    while (std::visit(VisitCondition(), cond)) {
        auto value = statement->execute(context);
        if (!std::get_if<std::monostate>(&value)) {
            return value;
        }
        cond = condition->evaluate(context);
    }
    return std::monostate();
}
