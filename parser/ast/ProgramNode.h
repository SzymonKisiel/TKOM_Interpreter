#ifndef _TKOM__INTERPRETER_PROGRAMNODE_H
#define _TKOM__INTERPRETER_PROGRAMNODE_H

#include <vector>
#include "Node.h"
#include "FunctionNode.h"

// program = {statement | function} ;
class ProgramNode : public Node {
    std::vector<std::unique_ptr<FunctionNode>> functions;
    std::vector<std::unique_ptr<StatementNode>> statements;
public:
    void addFunction(std::unique_ptr<FunctionNode> node) {
        if (node != nullptr)
            functions.push_back(std::move(node));
    }

    void addStatement(std::unique_ptr<StatementNode> node) {
        if (node != nullptr)
            statements.push_back(std::move(node));
    }

    const bool isTerminal() {
        return false;
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << "PROGRAM" << std::endl;
        if (isTerminal()) {
            return;
        }
        for (const auto &child: functions) {
            child->print(depth+1);
        }
        for (const auto &child: statements) {
            child->print(depth+1);
        }
    }
};


#endif //_TKOM__INTERPRETER_PROGRAMNODE_H
