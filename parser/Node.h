#ifndef _TKOM__INTERPRETER_NODE_H
#define _TKOM__INTERPRETER_NODE_H


#include <vector>
#include <memory>

#include <iostream>

class Node
{
private:
    std::vector<std::unique_ptr<Node>> children;
    std::string name = "";
public:

    Node() = default;

    Node(std::string name) {
        this->name = name;
    }

    void addChild(std::unique_ptr<Node> & node) {
        if (node != nullptr)
            children.push_back(std::move(node));
    }

    bool isTerminal() {
        return children.empty();
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << name << std::endl;
        if (isTerminal()) {
            return;
        }
        for (auto itr = children.begin(); itr != children.end(); ++itr) {
            (*itr)->print(depth+1);
        }
    }
};


#endif //_TKOM__INTERPRETER_NODE_H
