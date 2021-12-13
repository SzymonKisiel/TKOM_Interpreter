#include "DeclarationNode.h"
//#include "../../execution/VisitCheckType.h"

void DeclarationNode::setType(TokenType type) {
    this->type = type;
}

void DeclarationNode::setId(std::string id) {
    this->id = id;
}

void DeclarationNode::setExpression(std::unique_ptr<ExpressionNode> expression) {
    this->expression = std::move(expression);
}

std::string DeclarationNode::toString(int depth) {
    std::string result = std::string();
    for (int i = 0; i < depth; ++i)
        result.append(prefix);
    result.append("DECLARATION ")
            .append(tokenTypeToString(type))
            .append(" ")
            .append(id)
            .append("\n");

    if (expression != nullptr)
        result.append(expression->toString(depth + 1));
    return result;
}

//void DeclarationNode::execute(Context &context) {
//    auto value = expression->evaluate(context);
//    std::variant<TokenType> test = type;
//    if (!std::visit(VisitCheckType(), value, test))
//        throw ExecutionException(std::string("Wrong value type in '")
//                                    .append(id).append("' declaration, expected ")
//                                    .append(tokenTypeToString(type))
//                                );
//    context.addVariable(id, expression->evaluate(context));
//}
