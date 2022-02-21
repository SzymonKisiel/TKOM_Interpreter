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

std::string StatementNode::toString(int depth) const {
    std::string result = getPrefix(depth);
    result.append("STATEMENT\n");

    for (const auto &child: statements) {
        result.append(child->toString(depth+1));
    }
    if (whileStatement != nullptr)
        result.append(whileStatement->toString(depth+1));
    if (ifStatement != nullptr)
        result.append(ifStatement->toString(depth+1));
    if (simpleStatement != nullptr)
        result.append(simpleStatement->toString(depth+1));

    return result;
}

Value StatementNode::execute(Context &context) const {
    if (statementType == StatementType::SIMPLE)
        return simpleStatement->execute(context);

    context.enterScope();
    Value value = std::monostate();
    switch (statementType) {
        case StatementType::IF:
            value = ifStatement->execute(context);
            break;
        case StatementType::WHILE:
            value = whileStatement->execute(context);
            break;
        case StatementType::BLOCK:
            for (const auto &statement: statements) {
                value = statement->execute(context);
                if (!std::get_if<std::monostate>(&value)) {
                    context.exitScope();
                    return value;
                }
            }
            break;
    }
    context.exitScope();
    return value;
}
