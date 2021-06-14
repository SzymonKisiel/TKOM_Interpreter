#include "FunctionCallNode.h"

void FunctionCallNode::setId(std::string id) {
    this->id = id;
}

void FunctionCallNode::setArguments(std::unique_ptr<ArgumentsNode> arguments) {
    this->arguments = std::move(arguments);
}

std::string FunctionCallNode::toString() {
    return std::string("FUNCTION_CALL - ").append(id);
}

void FunctionCallNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
    if (arguments != nullptr)
        arguments->print(depth + 1);
}

std::variant<std::monostate, string, int, float> FunctionCallNode::execute(Context &context) {
    return context.callFunction(id, std::move(arguments));
}
