//
// Created by kislu on 03.06.2021.
//

#ifndef _TKOM__INTERPRETER_WHILESTATEMENTNODE_H
#define _TKOM__INTERPRETER_WHILESTATEMENTNODE_H

#include "Node.h"

class WhileStatementNode : public Node {
    std::unique_ptr<TestNode> condition;
    std::unique_ptr<StatementNode> statement;
    std::string name = "";
public:
    WhileStatementNode(std::string name) : name(std::move(name)) {
    }

    void setCondition(std::unique_ptr<TestNode> node) {
        if (node != nullptr)
            condition = std::move(node);
    }

    void setStatement(std::unique_ptr<StatementNode> node) {
        if (node != nullptr)
            statement = std::move(node);
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << "WHILE_STATEMENT" << std::endl;
        condition->print(depth+1);
        statement->print(depth+1);
    }
};


#endif //_TKOM__INTERPRETER_WHILESTATEMENTNODE_H
