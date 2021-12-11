#include "ProgramNode.h"

void ProgramNode::addFunction(std::shared_ptr<FunctionNode> node) {
    if (node != nullptr)
        functions.push_back(std::move(node));
}

void ProgramNode::addStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr)
        statements.push_back(std::move(node));
}

const bool ProgramNode::isTerminal() {
    return false;
}

void ProgramNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << "PROGRAM" << std::endl;
    if (isTerminal()) {
        return;
    }
    for (const auto &child: functions) {
        child->print(depth+1);
    }
    for (const auto &child: statements) {
        child->print(depth+1);
    }
}

//void ProgramNode::execute() {
//    Context context;
//    for (auto &function: functions) {
//        std::string id = function->getId();
//        context.addFunction(id, function);
//    }
//
//    for (const auto &statement: statements)
//        statement->execute(context);
//}
