#include "WhileStatementNode.h"

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

void WhileStatementNode::execute(Context &context) {
    cout << "TODO: while statement execution\n";
    /*while (VisitCond(),) {

    }*/
}
