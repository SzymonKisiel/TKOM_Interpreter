#include "StatementNode.h"
#include "../../execution/VisitPrint.h" //debug
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

std::variant<std::monostate, std::string, int, float> StatementNode::execute(Context &context) {
    switch (statementType) {
        case StatementType::IF:
            return ifStatement->execute(context);
        case StatementType::WHILE:
            return whileStatement->execute(context);
        case StatementType::SIMPLE:
            return simpleStatement->execute(context);;
        case StatementType::BLOCK:
            for (const auto &statement: statements) {
                auto value = statement->execute(context);
                if (!std::get_if<std::monostate>(&value)) {
                    return value;
                }
            }
            break;
    }
    return std::monostate();
}
