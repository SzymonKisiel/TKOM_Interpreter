#include "WhileStatementNode.h"
//#include "../../execution/VisitCondition.h"

WhileStatementNode::WhileStatementNode(std::string name) : name(std::move(name)) {
}

void WhileStatementNode::setCondition(std::unique_ptr<ExpressionNode> node) {
    if (node != nullptr)
        condition = std::move(node);
}

void WhileStatementNode::setStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr)
        statement = std::move(node);
}

void WhileStatementNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << "WHILE_STATEMENT" << std::endl;
    condition->print(depth+1);
    statement->print(depth+1);
}

//std::variant<std::monostate, std::string, int, float> WhileStatementNode::execute(Context &context) {
//    auto cond = condition->evaluate(context);
//    while (std::visit(VisitCondition(), cond)) {
//        auto value = statement->execute(context);
//        if (!std::get_if<std::monostate>(&value)) {
//            return value;
//        }
//        cond = condition->evaluate(context);
//    }
//    return std::monostate();
//}
