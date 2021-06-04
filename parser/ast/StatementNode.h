//
// Created by kislu on 03.06.2021.
//

#ifndef _TKOM__INTERPRETER_STATEMENTNODE_H
#define _TKOM__INTERPRETER_STATEMENTNODE_H

#include "Node.h"

class StatementNode : public Node {
    std::vector<std::unique_ptr<TestNode>> children;
    std::vector<std::unique_ptr<StatementNode>> statements;
    std::unique_ptr<WhileStatementNode> whileStatement;
    std::string name = "";
public:
    StatementNode(std::string name) : name(std::move(name)) {
    }

    void addChild(std::unique_ptr<TestNode> node) {
        if (node != nullptr)
            children.push_back(std::move(node));
    }

    void addStatement(std::unique_ptr<StatementNode> node) {
        if (node != nullptr)
            statements.push_back(std::move(node));
    }

    void setWhileStatement(std::unique_ptr<WhileStatementNode> node) {
        whileStatement = std::move(node);
    }

    const bool isTerminal() {
        return children.empty();
    }

    std::string toString() {
        return name;
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        if (isTerminal()) {
            return;
        }
        for (const auto &child: children) {
            child->print(depth+1);
        }
        for (const auto &child: statements) {
            child->print(depth+1);
        }
        if (whileStatement != nullptr)
            whileStatement->print(depth+1);
    }
};


#endif //_TKOM__INTERPRETER_STATEMENTNODE_H
