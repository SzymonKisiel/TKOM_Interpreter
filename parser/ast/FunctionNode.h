#ifndef _TKOM__INTERPRETER_FUNCTIONNODE_H
#define _TKOM__INTERPRETER_FUNCTIONNODE_H

#include "Node.h"
#include "StatementNode.h"
#include "ParametersNode.h"

// function = type , id ,  "(" , [parameters] , ")" , "{" , {statement} , "}" ;
class FunctionNode : public Node {
    std::string id;
    std::unique_ptr<ParametersNode> parameters;
    std::vector<std::unique_ptr<StatementNode>> statements;
    TokenType returnType;
public:
    void setId(std::string id) {
        this->id = id;
    }

    void setParameters(std::unique_ptr<ParametersNode> parameters)  {
        this->parameters = std::move(parameters);
    }

    void addStatement(std::unique_ptr<StatementNode> statement) {
        statements.push_back(std::move(statement));
    }

    void setReturnType(TokenType returnType) {
        this->returnType = returnType;
    }

    std::string toString() {
        return std::string("FUNCTION - ")
                    .append(tokenTypeToString(returnType))
                    .append(" ")
                    .append(id);
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        if (parameters != nullptr)
            parameters->print(depth+1);
        for (const auto &child: statements) {
            child->print(depth+1);
        }
    }
};


#endif //_TKOM__INTERPRETER_FUNCTIONNODE_H
