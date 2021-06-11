#ifndef _TKOM__INTERPRETER_DECLARATIONNODE_H
#define _TKOM__INTERPRETER_DECLARATIONNODE_H

#include "ExpressionNode.h"

// var_declaration  = type , id, "=", expression ;
class DeclarationNode : public Node {
    TokenType type;
    std::string id;
    std::unique_ptr<ExpressionNode> expression;
public:
    void setType(TokenType type);
    void setId(std::string id);
    void setExpression(std::unique_ptr<ExpressionNode> expression);
    std::string toString();
    void print(int depth = 0);
};


#endif //_TKOM__INTERPRETER_DECLARATIONNODE_H
