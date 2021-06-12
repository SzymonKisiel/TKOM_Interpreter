#include "StatementNode.h"
#include <memory>


void StatementNode::addStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr) {
        statementType = StatementType::BLOCK;
        statements.push_back(std::move(node));
    }
}

void StatementNode::setWhileStatement(std::unique_ptr<WhileStatementNode> node) {
    if (node != nullptr) {
        statementType = StatementType::WHILE;
        whileStatement = std::move(node);
    }
}

void StatementNode::setIfStatement(std::unique_ptr<IfStatementNode> node) {
    if (node != nullptr) {
        statementType = StatementType::IF;
        ifStatement = std::move(node);
    }
}

void StatementNode::setSimpleStatement(std::unique_ptr<SimpleStatementNode> node) {
    if (node != nullptr) {
        statementType = StatementType::SIMPLE;
        simpleStatement = std::move(node);
    }
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
    cout << "statement: ";
    switch (statementType) {
        case StatementType::IF:
            ifStatement->execute(context);
            break;
        case StatementType::WHILE:
            whileStatement->execute(context);
            break;
        case StatementType::SIMPLE:
            simpleStatement->execute(context);
            break;
        case StatementType::BLOCK:
            cout << "block\n";
            for (const auto &statement: statements) {
                statement->execute(context);
            }
            break;
        default:
            cout << "empty statement" << endl;
            //ExecutionException("Statement error");
    }

}
