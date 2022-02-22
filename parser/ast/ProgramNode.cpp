#include "ProgramNode.h"

void ProgramNode::addFunction(std::shared_ptr<FunctionNode> node) {
    if (node != nullptr)
        functions.push_back(std::move(node));
}

void ProgramNode::addStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr)
        statements.push_back(std::move(node));
}

bool ProgramNode::isTerminal() const {
    return false;
}

void ProgramNode::print(int depth) const {
    std::cout << this->toString() << std::endl;
}

std::string ProgramNode::toString() const {
    std::string result = "PROGRAM\n";
    for (const auto &child: functions) {
        result.append(child->toString(1));
    }
    for (const auto &child: statements) {
        result.append(child->toString(1));
    }
    return result;
}

void ProgramNode::execute() const {
    Context context;
    for (auto &function: functions) {
        std::string id = function->getId();
        context.addFunction(id, function);
    }

    for (const auto &statement: statements)
        statement->execute(context);
}
