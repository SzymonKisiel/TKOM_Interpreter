#include "SimpleStatementNode.h"

void SimpleStatementNode::setDeclaration(std::unique_ptr <DeclarationNode> declaration) {
    this->declaration = std::move(declaration);
    simpleStatementType = SimpleStatementType::DECLARATION;
}

void SimpleStatementNode::setAssignment(std::unique_ptr <AssignmentNode> assignment) {
    this->assignment = std::move(assignment);
    simpleStatementType = SimpleStatementType::ASSIGNMENT;
}

void SimpleStatementNode::setFunctionCall(std::unique_ptr <FunctionCallNode> functionCall) {
    this->functionCall = std::move(functionCall);
    simpleStatementType = SimpleStatementType::FUNCTION_CALL;
}

void SimpleStatementNode::setReturnStatement(std::unique_ptr <ReturnStatementNode> returnStatement) {
    this->returnStatement = std::move(returnStatement);
    simpleStatementType = SimpleStatementType::RETURN_STATEMENT;
}

std::string SimpleStatementNode::toString() {
    return "SIMPLE_STATEMENT";
}

void SimpleStatementNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString() << std::endl;
    if (declaration != nullptr)
        declaration->print(depth + 1);
    else if (assignment != nullptr)
        assignment->print(depth + 1);
    else if (functionCall != nullptr)
        functionCall->print(depth + 1);
    else if (returnStatement != nullptr)
        returnStatement->print(depth + 1);
}