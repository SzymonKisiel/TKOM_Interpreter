#ifndef _TKOM__INTERPRETER_FUNCTIONCALLNODE_H
#define _TKOM__INTERPRETER_FUNCTIONCALLNODE_H

#include <iostream>
#include "ArgumentsNode.h"

class ArgumentsNode;

// function_call    = id ,  "(" , [arguments] , ")" ;
class FunctionCallNode : public Node {
    std::string id;
    std::unique_ptr<ArgumentsNode> arguments;
public:
    void setId(std::string id);
    void setArguments(std::unique_ptr<ArgumentsNode> arguments);
    std::string toString();
    void print(int depth = 0);
};


#endif //_TKOM__INTERPRETER_FUNCTIONCALLNODE_H
