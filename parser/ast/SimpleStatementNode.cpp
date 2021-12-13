#include "SimpleStatementNode.h"
#include "../../execution/VisitPrint.h" //debug

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

std::string SimpleStatementNode::toString(int depth) {
    std::string result = std::string();
    for (int i = 0; i < depth; ++i)
        result.append(prefix);
    result.append("SIMPLE_STATEMENT\n");

    if (declaration != nullptr)
        result.append(declaration->toString(depth + 1));
    else if (assignment != nullptr)
        result.append(assignment->toString(depth + 1));
    else if (functionCall != nullptr)
        result.append(functionCall->toString(depth + 1));
    else if (returnStatement != nullptr)
        result.append(returnStatement->toString(depth + 1));

    return result;
}

//variant<std::monostate, string, int, float> SimpleStatementNode::execute(Context &context) {
//    switch (simpleStatementType) {
//        case SimpleStatementType::DECLARATION:
//            declaration->execute(context);
//            break;
//        case SimpleStatementType::ASSIGNMENT:
//            assignment->execute(context);
//            break;
//        case SimpleStatementType::FUNCTION_CALL:
//            functionCall->execute(context);
//            break;
//        case SimpleStatementType::RETURN_STATEMENT:
//            return returnStatement->execute(context);
//    }
//    return std::monostate();
//}
