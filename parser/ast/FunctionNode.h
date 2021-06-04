//
// Created by kislu on 03.06.2021.
//

#ifndef _TKOM__INTERPRETER_FUNCTIONNODE_H
#define _TKOM__INTERPRETER_FUNCTIONNODE_H

#include "Node.h"
#include "TestNode.h"
#include "StatementNode.h"

class FunctionNode : public Node {
    //function = type , id ,  "(" , [parameters] , ")" , "{" , {statement} , "}" ;
    //type
    //id
    //parameters
    //statements
    TokenType returnType;
    std::vector<std::unique_ptr<TestNode>> children;
    std::unique_ptr<StatementNode> statement;
    std::string name = "";
public:
    FunctionNode(std::string name) : name(std::move(name)){
    }

    void setReturnType(TokenType returnType) {
        this->returnType = returnType;
    }

    void addChild(std::unique_ptr<TestNode> node) {
        children.push_back(std::move(node));
    }

    void setStatement(std::unique_ptr<StatementNode> statementNode)  {
        statement = std::move(statementNode);
    }

    const bool isTerminal() {
        return children.empty();
    }

    std::string toString() {
        return name;
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << "FUNCTION\t" << tokenTypeToString(returnType) << std::endl;
        if (isTerminal()) {
            return;
        }
        for (const auto &child: children) {
            child->print(depth+1);
        }
        statement->print(depth+1);
    }
};


#endif //_TKOM__INTERPRETER_FUNCTIONNODE_H
