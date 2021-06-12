#include "StatementNode.h"
#include <memory>


void StatementNode::addStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr)
        statements.push_back(std::move(node));
}

void StatementNode::setWhileStatement(std::unique_ptr<WhileStatementNode> node) {
    whileStatement = std::move(node);
}

void StatementNode::setIfStatement(std::unique_ptr<IfStatementNode> node) {
    ifStatement = std::move(node);
}

void StatementNode::setSimpleStatement(std::unique_ptr<SimpleStatementNode> node) {
    simpleStatement = std::move(node);
}

void StatementNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << "STATEMENT" << std::endl;
    for (const auto &child: statements) {
        child->print(depth+1);
    }
    if (whileStatement != nullptr)
        whileStatement->print(depth+1);
    if (ifStatement != nullptr)
        ifStatement->print(depth+1);
    if (simpleStatement != nullptr)
        simpleStatement->print(depth+1);
}

void StatementNode::execute(Context &context) {
    //switch (statementType)
    if (ifStatement != nullptr)
        ifStatement->execute(context);
}
