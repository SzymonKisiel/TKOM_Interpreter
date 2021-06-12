#include "DeclarationNode.h"
#include "../../execution/VisitPrint.h"

void DeclarationNode::setType(TokenType type) {
    this->type = type;
}

void DeclarationNode::setId(std::string id) {
    this->id = id;
}

void DeclarationNode::setExpression(std::unique_ptr<ExpressionNode> expression) {
    this->expression = std::move(expression);
}

std::string DeclarationNode::toString() {
    return std::string("DECLARATION - ")
            .append(tokenTypeToString(type))
            .append(" ")
            .append(id);
}

void DeclarationNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
    if (expression != nullptr)
        expression->print(depth + 1);
}

void DeclarationNode::execute(Context &context) {
    context.addVariable(id, expression->evaluate(context));
    //debug print
//    auto variables = context.getVariables();
//    if (auto variable = variables.find(id); variable != variables.end()) {
//        cout << "declaration: " << variable->first << " = ";
//        std::visit(VisitPrintValue(), variable->second);
//        cout << endl;
//    }
//    for (auto variable: variables) {
//        cout << variable.first << " = ";
//        std::visit(VisitPrintValue(), variable.second);
//        cout << endl;
//    }
}
