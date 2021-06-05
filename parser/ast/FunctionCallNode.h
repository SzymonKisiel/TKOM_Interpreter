#ifndef _TKOM__INTERPRETER_FUNCTIONCALLNODE_H
#define _TKOM__INTERPRETER_FUNCTIONCALLNODE_H

#include "ArgumentsNode.h"

class FunctionCallNode : public Node {
    //id
    //args
    std::unique_ptr<ArgumentsNode> arguments;
public:
    void setArguments(std::unique_ptr<ArgumentsNode> arguments) {
        this->arguments = std::move(arguments);
    }

    std::string toString() {
        return "FUNCTION_CALL";
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
