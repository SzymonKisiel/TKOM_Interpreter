#ifndef _TKOM__INTERPRETER_DECLARATIONNODE_H
#define _TKOM__INTERPRETER_DECLARATIONNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"


// var_declaration  = type , id, "=", expression ;
class DeclarationNode : public Node {
    TokenType type;
    std::string id;
    std::unique_ptr<ExpressionNode> expression;
public:
    void setType(TokenType type);
    void setId(std::string id);
    void setExpression(std::unique_ptr<ExpressionNode> expression);

    std::string toString(int depth = 0) const;
    void execute(Context & context) const;
};


#endif //_TKOM__INTERPRETER_DECLARATIONNODE_H
