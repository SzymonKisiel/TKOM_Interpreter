#ifndef _TKOM__INTERPRETER_ADDEXPRESSIONNODE_H
#define _TKOM__INTERPRETER_ADDEXPRESSIONNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"
#include "../../exception/ExecutionException.h"

class MultExpressionNode;

// add_expression  = mult_expression , {add_operator, mult_expression } ;
class AddExpressionNode : public Node {
    std::vector<std::unique_ptr<MultExpressionNode>> operands;
    std::vector<TokenType> addOperations;
public:
    void addOperand(std::unique_ptr<MultExpressionNode> node);
    void addOperation(TokenType addOperation);
    std::string toString();
    void print(int depth = 0);
    std::variant<std::monostate, std::string, int, float> evaluate(Context & context);
    struct VisitAdd {
        void operator()(int& lhs, int& rhs) { lhs = lhs + rhs; }
        void operator()(float& lhs, float& rhs) { lhs = lhs + rhs; }
        void operator()(int& lhs, float& rhs) { lhs = lhs + rhs; }
        void operator()(float& lhs, int& rhs) { lhs = lhs + rhs; }
        void operator()(std::string& lhs, std::string& rhs) { lhs.append(rhs); }
        void operator()(auto& lhs, auto& rhs) { throw ExecutionException("Addition error"); }
    };
    struct VisitSubstract {
        void operator()(int& lhs, int& rhs) { lhs = lhs - rhs; }
        void operator()(float& lhs, float& rhs) { lhs = lhs - rhs; }
        void operator()(int& lhs, float& rhs) { lhs = lhs - rhs; }
        void operator()(float& lhs, int& rhs) { lhs = lhs - rhs; }
        void operator()(auto& lhs, auto& rhs) { throw ExecutionException("Subtraction error"); }
    };
    struct VisitOr {
        void operator()(int& lhs, int& rhs) {
            cout << lhs << " and " << rhs << endl;
            if (lhs != 0 || rhs != 0)
                lhs = 1;
            else
                lhs = 0;
        }
        void operator()(float& lhs, float& rhs) {
            if (lhs != 0 || rhs != 0)
                lhs = 1;
            else
                lhs = 0;
        }
        void operator()(int& lhs, float& rhs) {
            if (lhs != 0 || rhs != 0)
                lhs = 1;
            else
                lhs = 0;
        }
        void operator()(float& lhs, int& rhs) {
            if (lhs != 0 || rhs != 0)
                lhs = 1;
            else
                lhs = 0;
        }
        void operator()(auto& lhs, auto& rhs) { throw ExecutionException("Logical 'or' error"); }
    };
};


#endif //_TKOM__INTERPRETER_ADDEXPRESSIONNODE_H
