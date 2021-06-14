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
class FunctionNode : public Function {
    std::string id;
    std::shared_ptr<ParametersNode> parameters;
    std::vector<std::shared_ptr<StatementNode>> statements;
    TokenType returnType;
public:
    void setId(std::string id);
    void setParameters(std::unique_ptr<ParametersNode> parameters);
    void addStatement(std::unique_ptr<StatementNode> statement);
    void setReturnType(TokenType returnType);

    const string &getId();
    std::shared_ptr<ParametersNode> getParameters();

    std::string toString();
    void print(int depth = 0);
    variant<std::monostate, string, int, float> execute(Context & context);
};


#endif //_TKOM__INTERPRETER_FUNCTIONNODE_H
