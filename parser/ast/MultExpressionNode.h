#ifndef _TKOM__INTERPRETER_MULTEXPRESSIONNODE_H
#define _TKOM__INTERPRETER_MULTEXPRESSIONNODE_H

#include <vector>
#include <memory>
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

    variant<std::monostate, string, int, float> evaluate() {
        variant<std::monostate, string, int, float> lhs = operands[0]->evaluate();
        variant<std::monostate, string, int, float> rhs;
        TokenType operation;
        for (int i = 0; i < multOperations.size(); ++i) {
            operation = multOperations[i];
            rhs = operands[i+1]->evaluate();
            if (operation == TokenType::T_MUL) {
                std::visit(VisitMult(), lhs, rhs);
            }
            else if (operation == TokenType::T_DIV) {
                std::visit(VisitDiv(), lhs, rhs);
            }
            else
                ;//ExecutionException
        }
        return lhs;
    }

    struct VisitMult {
        void operator()(int&, int&) { cout << "int * int\n"; }
        void operator()(float&, float&) { cout << "float * float\n"; }
        void operator()(int&, float&) { cout << "int * float\n"; }
        void operator()(float&, int&) { cout << "float * int\n"; }
        void operator()(auto, auto) { cout << "error\n"; /*ExecutionException*/ }
    };

    struct VisitDiv {
        void operator()(int&, int&) { cout << "int / int\n"; }
        void operator()(float&, float&) { cout << "float / float\n"; }
        void operator()(int&, float&) { cout << "int / float\n"; }
        void operator()(float&, int&) { cout << "float / int\n"; }
        void operator()(auto, auto) { cout << "error\n"; /*ExecutionException*/ }
    };
};


#endif //_TKOM__INTERPRETER_MULTEXPRESSIONNODE_H
