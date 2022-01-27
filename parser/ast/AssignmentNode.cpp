#include "AssignmentNode.h"
#include "../../execution/VisitPrint.h"

void AssignmentNode::setId(std::string id) {
    this->id = id;
}

void AssignmentNode::setExpression(std::unique_ptr<ExpressionNode> expression) {
    this->expression = std::move(expression);
}

std::string AssignmentNode::toString(int depth) {
    std::string result = std::string();
    for (int i = 0; i < depth; ++i)
        result.append(prefix);
    result.append("ASSIGNMENT ")
            .append(id)
            .append("\n");

    if (expression != nullptr)
        result.append(expression->toString(depth + 1));

    return result;
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
