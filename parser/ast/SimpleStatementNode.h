#ifndef _TKOM__INTERPRETER_SIMPLESTATEMENTNODE_H
#define _TKOM__INTERPRETER_SIMPLESTATEMENTNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"

class DeclarationNode;
class AssignmentNode;
class FunctionCallNode;
class ReturnStatementNode;

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
    void setDeclaration(std::unique_ptr <DeclarationNode> declaration);
    void setAssignment(std::unique_ptr <AssignmentNode> assignment);
    void setFunctionCall(std::unique_ptr <FunctionCallNode> functionCall);
    void setReturnStatement(std::unique_ptr <ReturnStatementNode> returnStatement);
    std::string toString();
    void print(int depth = 0);
};




#endif //_TKOM__INTERPRETER_SIMPLESTATEMENTNODE_H
