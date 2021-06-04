//
// Created by kislu on 04.06.2021.
//

#ifndef _TKOM__INTERPRETER_EXPRESSIONNODE_H
#define _TKOM__INTERPRETER_EXPRESSIONNODE_H


#include "AddExpresionNode.h"

class ExpressionNode : public Node {
    std::vector<std::unique_ptr<AddExpresionNode>> operands;
    std::vector<TokenType> compOperations;
public:
    void addOperand(std::unique_ptr<AddExpresionNode> node) {
        operands.push_back(std::move(node));
    };

    void addOperation(TokenType compOperation) {
        compOperations.push_back(compOperation);
    };

    std::string toString() {
        return "EXPRESSION_NODE";
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


#endif //_TKOM__INTERPRETER_EXPRESSIONNODE_H