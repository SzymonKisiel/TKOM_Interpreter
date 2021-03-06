#include "IfStatementNode.h"
#include "../../execution/VisitCondition.h"

void IfStatementNode::setIfCondition(std::unique_ptr<ExpressionNode> node) {
    ifCondition = std::move(node);
}

void IfStatementNode::setIfStatement(std::unique_ptr<StatementNode> node) {
    ifStatement = std::move(node);
}

void IfStatementNode::addElsifCondition(std::unique_ptr<ExpressionNode> node) {
    if (node != nullptr)
        elsifConditions.push_back(std::move(node));
}

void IfStatementNode::addElsifStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr)
        elsifStatements.push_back(std::move(node));
}

void IfStatementNode::setElseStatement(std::unique_ptr<StatementNode> node) {
    elseStatement = std::move(node);
}

std::string IfStatementNode::toString(int depth) const {
    std::string result = getPrefix(depth);
    result.append("IF_STATEMENT\n");

    if (ifCondition != nullptr)
        result.append(ifCondition->toString(depth+1));
    if (ifStatement != nullptr)
        result.append(ifStatement->toString(depth+1));
    if (!elsifConditions.empty()) {
        for (const auto &child: elsifConditions)
            result.append(child->toString(depth+1));
        for (const auto &child: elsifStatements)
            result.append(child->toString(depth+1));
    }
    if (elseStatement != nullptr)
        result.append(elseStatement->toString(depth+1));

    return result;
}

Value IfStatementNode::execute(Context & context) const {
    auto condition = ifCondition->evaluate(context);
    if (std::visit(VisitCondition(), condition)) {
        return ifStatement->execute(context);
    }
    if (!elsifConditions.empty()) {
        int i = 0;
        for (const auto &elseIfCondition: elsifConditions) {
            condition = elseIfCondition->evaluate(context);
            if (std::visit(VisitCondition(), condition)) {
                return elsifStatements[i]->execute(context);
            }
            ++i;
        }
    }
    if (elseStatement != nullptr) {
        return elseStatement->execute(context);
    }
    return std::monostate();
}
