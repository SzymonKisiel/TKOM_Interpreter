#include "AssignmentNode.h"
#include "../../execution/VisitPrint.h"

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
    context.assignToVariable(id, expression->evaluate(context));
    // debug print
//    auto variables = context.getVariables();
//    if (auto variable = variables.find(id); variable != variables.end()) {
//        cout << "assignment: " << variable->first << " = ";
//        std::visit(VisitPrintValue(), variable->second);
//        cout << endl;
//    }
//    for (auto variable: variables) {
//        cout << variable.first << " = ";
//        std::visit(VisitPrintValue(), variable.second);
//        cout << endl;
//    }
}
