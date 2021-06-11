#ifndef _TKOM__INTERPRETER_FUNCTIONNODE_H
#define _TKOM__INTERPRETER_FUNCTIONNODE_H

#include "Node.h"
#include "StatementNode.h"
#include "ParametersNode.h"

class StatementNode;

// function = type , id ,  "(" , [parameters] , ")" , "{" , {statement} , "}" ;
class FunctionNode : public Node {
    std::string id;
    std::unique_ptr<ParametersNode> parameters;
    std::vector<std::unique_ptr<StatementNode>> statements;
    TokenType returnType;
public:
    void setId(std::string id);
    void setParameters(std::unique_ptr<ParametersNode> parameters);
    void addStatement(std::unique_ptr<StatementNode> statement);
    void setReturnType(TokenType returnType);
    std::string toString();
    void print(int depth = 0);
};


#endif //_TKOM__INTERPRETER_FUNCTIONNODE_H
