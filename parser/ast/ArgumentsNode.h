#ifndef _TKOM__INTERPRETER_ARGUMENTSNODE_H
#define _TKOM__INTERPRETER_ARGUMENTSNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"

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
