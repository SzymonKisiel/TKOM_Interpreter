#ifndef _TKOM__INTERPRETER_ADDEXPRESSIONNODE_H
#define _TKOM__INTERPRETER_ADDEXPRESSIONNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"

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
    std::variant<std::monostate, std::string, int, float> evaluate();
};


#endif //_TKOM__INTERPRETER_ADDEXPRESSIONNODE_H