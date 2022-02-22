#ifndef _TKOM__INTERPRETER_FUNCTIONNODE_H
#define _TKOM__INTERPRETER_FUNCTIONNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"
#include "../../execution/Function.h"

class StatementNode;
class ParametersNode;

// function = type , id ,  "(" , [parameters] , ")" , "{" , {statement} , "}" ;
class FunctionNode : public Function, Node {
    std::string id;
    std::shared_ptr<ParametersNode> parameters;
    std::vector<std::shared_ptr<StatementNode>> statements;
    TokenType returnType;
public:
    void setId(std::string id);
    void setParameters(std::unique_ptr<ParametersNode> parameters);
    void addStatement(std::unique_ptr<StatementNode> statement);
    void setReturnType(TokenType returnType);

    std::string getId() const;
    std::shared_ptr<ParametersNode> getParameters() const;
    std::string toString(int depth = 0) const;
    Value execute(Context & context) const;
};


#endif //_TKOM__INTERPRETER_FUNCTIONNODE_H
