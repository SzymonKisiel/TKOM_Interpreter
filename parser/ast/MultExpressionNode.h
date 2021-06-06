#ifndef _TKOM__INTERPRETER_MULTEXPRESSIONNODE_H
#define _TKOM__INTERPRETER_MULTEXPRESSIONNODE_H

#include "FactorNode.h"

// mult_expression = factor , { mult_operator , factor} ;
class MultExpressionNode : public Node {
    std::vector<std::unique_ptr<FactorNode>> operands;
    std::vector<TokenType> multOperations;
public:
    void addOperand(std::unique_ptr<FactorNode> node) {
        operands.push_back(std::move(node));
    };

    void addOperation(TokenType multOperation) {
        multOperations.push_back(multOperation);
    };

    std::string toString() {
        std::string result("MULT_EXPRESSION");
        if (!multOperations.empty()) {
            result.append(" -");
            for (const auto &operation: multOperations) {
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
};


#endif //_TKOM__INTERPRETER_MULTEXPRESSIONNODE_H
