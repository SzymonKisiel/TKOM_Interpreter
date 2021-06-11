#ifndef _TKOM__INTERPRETER_EXPRESSIONNODE_H
#define _TKOM__INTERPRETER_EXPRESSIONNODE_H

#include <vector>
#include <memory>
#include "Node.h"
#include "../../lexer/Token.h"

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
};


#endif //_TKOM__INTERPRETER_EXPRESSIONNODE_H
