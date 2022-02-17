#include "ArgumentsNode.h"

void ArgumentsNode::addArgument(std::shared_ptr<ExpressionNode> argument) {
    if (argument != nullptr)
        arguments.push_back(std::move(argument));
}

std::string ArgumentsNode::toString() {
    return "ARGUMENTS";
}

void ArgumentsNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
    for (const auto &child: arguments) {
        child->print(depth + 1);
    }
}

std::vector<std::shared_ptr<ExpressionNode>> ArgumentsNode::getArguments() {
    return arguments;
}
