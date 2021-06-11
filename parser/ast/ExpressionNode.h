#ifndef _TKOM__INTERPRETER_EXPRESSIONNODE_H
#define _TKOM__INTERPRETER_EXPRESSIONNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"


class AddExpressionNode;

// expression      = add_expression , {comp_operator, add_expression } ;
class ExpressionNode : public Node {
    std::vector<std::unique_ptr<AddExpressionNode>> operands;
    std::vector<TokenType> compOperations;
public:
    void addOperand(std::unique_ptr<AddExpressionNode> node);
    void addOperation(TokenType compOperation);
    std::string toString();
    void print(int depth = 0);
    variant<std::monostate, string, int, float> evaluate();
    struct VisitLess {
        int operator() (int& lhs, int& rhs) {
            if (lhs < rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, float& rhs) {
            if (lhs < rhs)
                return 1;
            return 0;
        }
        int operator() (int& lhs, float& rhs) {
            if (lhs < rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, int& rhs) {
            if (lhs < rhs)
                return 1;
            return 0;
        }
        int operator() (auto lhs, auto rhs) { cout << "error\n"; /*ExecutionException*/ }
    };
    struct VisitGreater {
        int operator() (int& lhs, int& rhs) {
            if (lhs > rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, float& rhs) {
            if (lhs > rhs)
                return 1;
            return 0;
        }
        int operator() (int& lhs, float& rhs) {
            if (lhs > rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, int& rhs) {
            if (lhs > rhs)
                return 1;
            return 0;
        }
        int operator() (auto lhs, auto rhs) { cout << "error\n"; /*ExecutionException*/ }
    };
    struct VisitLessOrEqual {
        int operator() (int& lhs, int& rhs) {
            if (lhs <= rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, float& rhs) {
            if (lhs <= rhs)
                return 1;
            return 0;
        }
        int operator() (int& lhs, float& rhs) {
            if (lhs <= rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, int& rhs) {
            if (lhs <= rhs)
                return 1;
            return 0;
        }
        int operator() (auto lhs, auto rhs) { cout << "error\n"; /*ExecutionException*/ }
    };
    struct VisitGreaterOrEqual {
        int operator() (int& lhs, int& rhs) {
            if (lhs >= rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, float& rhs) {
            if (lhs >= rhs)
                return 1;
            return 0;
        }
        int operator() (int& lhs, float& rhs) {
            if (lhs >= rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, int& rhs) {
            if (lhs >= rhs)
                return 1;
            return 0;
        }
        int operator() (auto lhs, auto rhs) { cout << "error\n"; /*ExecutionException*/ }
    };
    struct VisitEqual {
        int operator() (int& lhs, int& rhs) {
            if (lhs == rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, float& rhs) {
            if (lhs == rhs)
                return 1;
            return 0;
        }
        int operator() (int& lhs, float& rhs) {
            if (lhs == rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, int& rhs) {
            if (lhs == rhs)
                return 1;
            return 0;
        }
        int operator() (auto lhs, auto rhs) { cout << "error\n"; /*ExecutionException*/ }
    };
    struct VisitNotEqual {
        int operator() (int& lhs, int& rhs) {
            if (lhs != rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, float& rhs) {
            if (lhs != rhs)
                return 1;
            return 0;
        }
        int operator() (int& lhs, float& rhs) {
            if (lhs != rhs)
                return 1;
            return 0;
        }
        int operator() (float& lhs, int& rhs) {
            if (lhs != rhs)
                return 1;
            return 0;
        }
        int operator() (auto lhs, auto rhs) { cout << "error\n"; /*ExecutionException*/ }
    };
};


#endif //_TKOM__INTERPRETER_EXPRESSIONNODE_H
