#include "ArgumentsNode.h"

void ArgumentsNode::addArgument(std::shared_ptr<ExpressionNode> argument) {
    if (argument != nullptr)
        arguments.push_back(std::move(argument));
}

std::string ArgumentsNode::toString(int depth) const {
    std::string result = getPrefix(depth);
    result.append("ARGUMENTS\n");

    for (const auto &child: arguments) {
        result.append(child->toString(depth + 1));
    }

    return result;
}

std::vector<std::shared_ptr<ExpressionNode>> ArgumentsNode::getArguments() const {
    return arguments;
}
