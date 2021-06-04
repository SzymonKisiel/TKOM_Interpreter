#ifndef _TKOM__INTERPRETER_TESTNODE_H
#define _TKOM__INTERPRETER_TESTNODE_H


#include <vector>
#include <memory>
#include <iostream>

#include "Node.h"
#include "ExpressionNode.h"

class TestNode : public Node {
private:
    std::vector<std::unique_ptr<TestNode>> children;
    std::vector<std::unique_ptr<ExpressionNode>> expressions;
    std::string name = "TEST";
public:
    TestNode() = default;

    TestNode(std::string name) : name(std::move(name)){
    }

    void addChild(std::unique_ptr<TestNode> node) {
        if (node != nullptr)
            children.push_back(std::move(node));
    }

    void addExpression(std::unique_ptr<ExpressionNode> node) {
        if (node != nullptr)
            expressions.push_back(std::move(node));
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
        for (const auto &child: expressions) {
            child->print(depth+1);
        }
    }
};

#endif //_TKOM__INTERPRETER_TESTNODE_H
