#include "IfStatementNode.h"
//#include "../../execution/VisitCondition.h"

void IfStatementNode::setIfCondition(std::unique_ptr<ExpressionNode> node) {
    ifCondition = std::move(node);
}

void IfStatementNode::setIfStatement(std::unique_ptr<StatementNode> node) {
    ifStatement = std::move(node);
}

void IfStatementNode::addElsifCondition(std::unique_ptr<ExpressionNode> node) {
    if (node != nullptr)
        elsifConditions.push_back(std::move(node));
}

void IfStatementNode::addElsifStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr)
        elsifStatements.push_back(std::move(node));
}

void IfStatementNode::setElseStatement(std::unique_ptr<StatementNode> node) {
    elseStatement = std::move(node);
}

void IfStatementNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << "IF_STATEMENT" << std::endl;
    if (ifCondition != nullptr)
        ifCondition->print(depth+1);
    if (ifStatement != nullptr)
        ifStatement->print(depth+1);
    if (!elsifConditions.empty()) {
        for (const auto &child: elsifConditions)
            child->print(depth+1);
        for (const auto &child: elsifStatements)
            child->print(depth+1);
    }
    if (elseStatement != nullptr)
        elseStatement->print(depth+1);
}

//std::variant<std::monostate, string, int, float> IfStatementNode::execute(Context & context) {
//    auto condition = ifCondition->evaluate(context);
//    if (std::visit(VisitCondition(), condition)) {
//        return ifStatement->execute(context);
//    }
//    if (!elsifConditions.empty()) {
//        int i = 0;
//        for (const auto &elseIfCondition: elsifConditions) {
//            condition = elseIfCondition->evaluate(context);
//            if (std::visit(VisitCondition(), condition)) {
//                return elsifStatements[i]->execute(context);
//            }
//            ++i;
//        }
//    }
//    if (elseStatement != nullptr) {
//        return elseStatement->execute(context);
//    }
//    return std::monostate();
//}
