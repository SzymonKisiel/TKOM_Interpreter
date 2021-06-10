#ifndef _TKOM__INTERPRETER_FUNCTIONCALLNODE_H
#define _TKOM__INTERPRETER_FUNCTIONCALLNODE_H

#include <iostream>
#include "ArgumentsNode.h"

// function_call    = id ,  "(" , [arguments] , ")" ;
class FunctionCallNode : public Node {
    std::string id;
    std::unique_ptr<ArgumentsNode> arguments;
public:
    void setId(std::string id) {
        this->id = id;
    }

    void setArguments(std::unique_ptr<ArgumentsNode> arguments) {
        this->arguments = std::move(arguments);
    }

    std::string toString() {
        return std::string("FUNCTION_CALL - ").append(id);
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        if (arguments != nullptr)
            arguments->print(depth + 1);
    };
};


#endif //_TKOM__INTERPRETER_FUNCTIONCALLNODE_H
