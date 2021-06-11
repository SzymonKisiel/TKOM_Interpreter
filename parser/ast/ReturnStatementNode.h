#ifndef _TKOM__INTERPRETER_RETURNSTATEMENTNODE_H
#define _TKOM__INTERPRETER_RETURNSTATEMENTNODE_H

#include "Node.h"
#include "ExpressionNode.h"

// return_statement = "return" , [expression] , ";" ;
class ReturnStatementNode : public Node {
    std::unique_ptr<ExpressionNode> returnExpression;
public:
    void setReturnExpression(std::unique_ptr<ExpressionNode> returnExpression);
    std::string toString();
    void print(int depth = 0);
};


#endif //_TKOM__INTERPRETER_RETURNSTATEMENTNODE_H
