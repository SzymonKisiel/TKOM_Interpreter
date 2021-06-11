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
