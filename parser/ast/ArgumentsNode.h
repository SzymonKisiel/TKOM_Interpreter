#ifndef _TKOM__INTERPRETER_ARGUMENTSNODE_H
#define _TKOM__INTERPRETER_ARGUMENTSNODE_H

#include "ExpressionNode.h"

// arguments  = argument , {"," , argument} ;
// argument   = expression ;
class ArgumentsNode : public Node {
    std::vector<std::unique_ptr<ExpressionNode>> arguments;
public:
    void addArgument(std::unique_ptr<ExpressionNode> argument) {
        if (argument != nullptr)
            arguments.push_back(std::move(argument));
    }

    std::string toString() {
        return "ARGUMENTS";
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        for (const auto &child: arguments) {
            child->print(depth + 1);
        }
    }
};


#endif //_TKOM__INTERPRETER_ARGUMENTSNODE_H
