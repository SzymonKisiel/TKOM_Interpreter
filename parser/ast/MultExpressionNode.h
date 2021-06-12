#ifndef _TKOM__INTERPRETER_MULTEXPRESSIONNODE_H
#define _TKOM__INTERPRETER_MULTEXPRESSIONNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"
#include "../../exception/ExecutionException.h"


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
    variant<std::monostate, string, int, float> evaluate(Context & context);
    struct VisitMult {
        void operator()(int& lhs, int& rhs) { lhs = lhs * rhs; }
        void operator()(float& lhs, float& rhs) { lhs = lhs * rhs; }
        void operator()(int& lhs, float& rhs) { lhs = lhs * rhs; }
        void operator()(float& lhs, int& rhs) { lhs = lhs * rhs; }
        void operator()(auto& lhs, auto& rhs) { throw ExecutionException("Multiplication error"); }
    };
    struct VisitDiv {
        void operator()(int& lhs, int& rhs) { lhs = lhs / rhs; }
        void operator()(float& lhs, float& rhs) { lhs = lhs / rhs; }
        void operator()(int& lhs, float& rhs) { lhs = lhs / rhs; }
        void operator()(float& lhs, int& rhs) { lhs = lhs / rhs; }
        void operator()(auto& lhs, auto& rhs) { throw ExecutionException("Division error"); }
    };
};


#endif //_TKOM__INTERPRETER_MULTEXPRESSIONNODE_H
