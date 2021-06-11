#ifndef _TKOM__INTERPRETER_ASSIGNMENTNODE_H
#define _TKOM__INTERPRETER_ASSIGNMENTNODE_H

#include "ExpressionNode.h"

// assignment       = id, "=", expression ;
class AssignmentNode : public Node {
    std::string id;
    std::unique_ptr<ExpressionNode> expression;
public:
    void setId(std::string id);
    void setExpression(std::unique_ptr<ExpressionNode> expression);
    std::string toString();
    void print(int depth = 0) ;
};


#endif //_TKOM__INTERPRETER_ASSIGNMENTNODE_H
