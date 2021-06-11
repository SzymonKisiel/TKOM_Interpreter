#ifndef _TKOM__INTERPRETER_ADDEXPRESIONNODE_H
#define _TKOM__INTERPRETER_ADDEXPRESIONNODE_H

#include "MultExpressionNode.h"

// add_expression  = mult_expression , {add_operator, mult_expression } ;
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
        std::string result("ADD_EXPRESSION");
        if (!addOperations.empty()) {
            result.append(" -");
            for (const auto &operation: addOperations) {
                result.append(" ").append(tokenTypeToString(operation));
            }
        }
        return result;
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        for (const auto &child: operands) {
            child->print(depth+1);
        }
    }

    variant<std::monostate, string, int, float> evaluate() {
        variant<std::monostate, string, int, float> test = 0;
        return test;
    }
};


#endif //_TKOM__INTERPRETER_ADDEXPRESIONNODE_H
