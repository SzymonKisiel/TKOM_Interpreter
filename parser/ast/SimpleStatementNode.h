#ifndef _TKOM__INTERPRETER_SIMPLESTATEMENTNODE_H
#define _TKOM__INTERPRETER_SIMPLESTATEMENTNODE_H

#include "DeclarationNode.h"
#include "AssignmentNode.h"
#include "FunctionCallNode.h"
#include "ReturnStatementNode.h"

// simple_statement = (var_declaration | assignment | function_call | return_statement) , ";" ;
class SimpleStatementNode : public Node {
    std::unique_ptr <DeclarationNode> declaration;
    std::unique_ptr <AssignmentNode> assignment;
    std::unique_ptr <FunctionCallNode> functionCall;
    std::unique_ptr <ReturnStatementNode> returnStatement;
    enum SimpleStatementType {
        DECLARATION,
        ASSIGNMENT,
        FUNCTION_CALL,
        RETURN_STATEMENT
    };
    SimpleStatementType simpleStatementType;
public:
    void setDeclaration(std::unique_ptr <DeclarationNode> declaration) {
        this->declaration = std::move(declaration);
        simpleStatementType = SimpleStatementType::DECLARATION;
    }

    void setAssignment(std::unique_ptr <AssignmentNode> assignment) {
        this->assignment = std::move(assignment);
        simpleStatementType = SimpleStatementType::ASSIGNMENT;
    };

    void setFunctionCall(std::unique_ptr <FunctionCallNode> functionCall) {
        this->functionCall = std::move(functionCall);
        simpleStatementType = SimpleStatementType::FUNCTION_CALL;
    };

    void setReturnStatement(std::unique_ptr <ReturnStatementNode> returnStatement) {
        this->returnStatement = std::move(returnStatement);
        simpleStatementType = SimpleStatementType::RETURN_STATEMENT;
    };

    std::string toString() {
        return "SIMPLE_STATEMENT";
    }

    void print(int depth = 0) {
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
    };
};




#endif //_TKOM__INTERPRETER_SIMPLESTATEMENTNODE_H
