#ifndef _TKOM__INTERPRETER_DECLARATIONNODE_H
#define _TKOM__INTERPRETER_DECLARATIONNODE_H

#include "ExpressionNode.h"

// var_declaration  = type , id, "=", expression ;
class DeclarationNode : public Node {
    TokenType type;
    std::string id;
    std::unique_ptr<ExpressionNode> expression;
public:
    void setType(TokenType type) {
        this->type = type;
    }

    void setId(std::string id) {
        this->id = id;
    }

    void setExpression(std::unique_ptr<ExpressionNode> expression) {
        this->expression = std::move(expression);
    }

    std::string toString() {
        return std::string("DECLARATION - ")
                    .append(tokenTypeToString(type))
                    .append(" ")
                    .append(id);
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        if (expression != nullptr)
            expression->print(depth + 1);
    };
};


#endif //_TKOM__INTERPRETER_DECLARATIONNODE_H
