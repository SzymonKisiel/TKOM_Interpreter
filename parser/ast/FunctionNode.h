#ifndef _TKOM__INTERPRETER_FUNCTIONNODE_H
#define _TKOM__INTERPRETER_FUNCTIONNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"

class StatementNode;
class ParametersNode;

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
    void execute(Context & context);
};


#endif //_TKOM__INTERPRETER_FUNCTIONNODE_H
