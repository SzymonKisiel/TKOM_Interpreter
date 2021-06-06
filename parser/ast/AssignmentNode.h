#ifndef _TKOM__INTERPRETER_ASSIGNMENTNODE_H
#define _TKOM__INTERPRETER_ASSIGNMENTNODE_H

#include "ExpressionNode.h"

// assignment       = id, "=", expression ;
class AssignmentNode : public Node {
    std::string id;
    std::unique_ptr<ExpressionNode> expression;
public:
    void setId(std::string id) {
        this->id = id;
    }

    void setExpression(std::unique_ptr<ExpressionNode> expression) {
        this->expression = std::move(expression);
    }

    std::string toString() {
        return std::string("ASSIGNMENT - ").append(id);
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        if (expression != nullptr)
            expression->print(depth + 1);
    };
};


#endif //_TKOM__INTERPRETER_ASSIGNMENTNODE_H
