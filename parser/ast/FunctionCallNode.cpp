#include "FunctionCallNode.h"

void FunctionCallNode::setId(std::string id) {
    this->id = id;
}

void FunctionCallNode::setArguments(std::shared_ptr<ArgumentsNode> arguments) {
    this->arguments = std::move(arguments);
}

std::string FunctionCallNode::toString(int depth) const {
    std::string result = getPrefix(depth);
    result.append("FUNCTION_CALL ")
            .append(id)
            .append("\n");

    if (arguments != nullptr)
        result.append(arguments->toString(depth + 1));

    return result;
}

Value FunctionCallNode::execute(Context &context) const {
    if (id == "print")
        return context.callFunction(id, arguments, false);
    else
        return context.callFunction(id, arguments);
}
