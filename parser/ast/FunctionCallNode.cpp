#include "FunctionCallNode.h"

void FunctionCallNode::setId(std::string id) {
    this->id = id;
}

void FunctionCallNode::setArguments(std::shared_ptr<ArgumentsNode> arguments) {
    this->arguments = std::move(arguments);
}

std::string FunctionCallNode::toString(int depth) {
    std::string result = std::string();
    for (int i = 0; i < depth; ++i)
        result.append(prefix);
    result.append("FUNCTION_CALL ")
            .append(id)
            .append("\n");

    if (arguments != nullptr)
        result.append(arguments->toString(depth + 1));

    return result;
}

Value FunctionCallNode::execute(Context &context) {
    if (id == "print")
        return context.callFunction(id, arguments, false);
    else
        return context.callFunction(id, arguments);
}
