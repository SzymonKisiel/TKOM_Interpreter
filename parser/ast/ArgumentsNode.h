#ifndef _TKOM__INTERPRETER_ARGUMENTSNODE_H
#define _TKOM__INTERPRETER_ARGUMENTSNODE_H

#include <vector>
#include "ExpressionNode.h"

class ExpressionNode;

// arguments  = argument , {"," , argument} ;
// argument   = expression ;
class ArgumentsNode : public Node {
    std::vector<std::unique_ptr<ExpressionNode>> arguments;
public:
    void addArgument(std::unique_ptr<ExpressionNode> argument);
    std::string toString();
    void print(int depth = 0);
};


#endif //_TKOM__INTERPRETER_ARGUMENTSNODE_H
