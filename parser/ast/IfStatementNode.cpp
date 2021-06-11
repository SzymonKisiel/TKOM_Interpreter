#include "IfStatementNode.h"

void IfStatementNode::setIfCondition(std::unique_ptr<ExpressionNode> node) {
    ifCondition = std::move(node);
}

void IfStatementNode::setIfStatement(std::unique_ptr<StatementNode> node) {
    ifStatement = std::move(node);
}

void IfStatementNode::addElsifCondition(std::unique_ptr<ExpressionNode> node) {
    if (node != nullptr)
        elsifCondition.push_back(std::move(node));
}

void IfStatementNode::addElsifStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr)
        elsifStatement.push_back(std::move(node));
}

void IfStatementNode::setElseStatement(std::unique_ptr<StatementNode> node) {
    elseStatement = std::move(node);
}

void IfStatementNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << "IF_STATEMENT" << std::endl;
    if (ifCondition != nullptr)
        ifCondition->print(depth+1);
    if (ifStatement != nullptr)
        ifStatement->print(depth+1);
    if (!elsifCondition.empty()) {
        for (const auto &child: elsifCondition)
            child->print(depth+1);
        for (const auto &child: elsifStatement)
            child->print(depth+1);
    }
    if (elseStatement != nullptr)
        elseStatement->print(depth+1);
}

void IfStatementNode::execute(Context &context) {
    ifCondition->evaluate();
}
