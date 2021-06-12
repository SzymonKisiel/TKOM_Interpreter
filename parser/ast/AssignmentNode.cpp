#include "AssignmentNode.h"

void AssignmentNode::setId(std::string id) {
    this->id = id;
}

void AssignmentNode::setExpression(std::unique_ptr<ExpressionNode> expression) {
    this->expression = std::move(expression);
}

std::string AssignmentNode::toString() {
    return std::string("ASSIGNMENT - ").append(id);
}

void AssignmentNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
    if (expression != nullptr)
        expression->print(depth + 1);
}

void AssignmentNode::execute(Context &context) {
    cout << "TODO: assignment\n";
}
