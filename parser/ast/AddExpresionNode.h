#ifndef _TKOM__INTERPRETER_ADDEXPRESIONNODE_H
#define _TKOM__INTERPRETER_ADDEXPRESIONNODE_H

#include "MultExpressionNode.h"

class AddExpresionNode : public Node {
    std::vector<std::unique_ptr<MultExpressionNode>> operands;
    std::vector<TokenType> addOperations;
public:
    void addOperand(std::unique_ptr<MultExpressionNode> node) {
        operands.push_back(std::move(node));
    };

    void addOperation(TokenType addOperation) {
        addOperations.push_back(addOperation);
    };

    std::string toString() {
        return "ADD_EXPRESSION_NODE";
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        for (const auto &child: operands) {
            child->print(depth+1);
        }
    }
};


#endif //_TKOM__INTERPRETER_ADDEXPRESIONNODE_H
