#ifndef _TKOM__INTERPRETER_MULTEXPRESSIONNODE_H
#define _TKOM__INTERPRETER_MULTEXPRESSIONNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"


class FactorNode;

// mult_expression = factor , { mult_operator , factor} ;
class MultExpressionNode : public Node {
    std::vector<std::unique_ptr<FactorNode>> operands;
    std::vector<TokenType> multOperations;
public:
    void addOperand(std::unique_ptr<FactorNode> node);
    void addOperation(TokenType multOperation);
    std::string toString();
    void print(int depth = 0);
    variant<std::monostate, string, int, float> evaluate();
    struct VisitMult {
        void operator()(int& lhs, int& rhs) { cout << "int * int\n"; lhs = lhs * rhs; }
        void operator()(float& lhs, float& rhs) { cout << "float * float\n"; lhs = lhs * rhs; }
        void operator()(int& lhs, float& rhs) { cout << "int * float\n"; lhs = lhs * rhs; }
        void operator()(float& lhs, int& rhs) { cout << "float * int\n"; lhs = lhs * rhs; }
        void operator()(auto, auto) { cout << "error\n"; /*ExecutionException*/ }
    };
    struct VisitDiv {
        void operator()(int& lhs, int& rhs) { cout << "int / int\n"; }
        void operator()(float& lhs, float& rhs) { cout << "float / float\n"; }
        void operator()(int& lhs, float& rhs) { cout << "int / float\n"; }
        void operator()(float& lhs, int& rhs) { cout << "float / int\n"; }
        void operator()(auto, auto) { cout << "error\n"; /*ExecutionException*/ }
    };
};


#endif //_TKOM__INTERPRETER_MULTEXPRESSIONNODE_H
