#ifndef _TKOM__INTERPRETER_STATEMENTNODE_H
#define _TKOM__INTERPRETER_STATEMENTNODE_H

#include "Node.h"
#include "SimpleStatementNode.h"
#include "WhileStatementNode.h"
#include "IfStatementNode.h"
#include "../../execution/Context.h"
#include <memory>

class WhileStatementNode;
class IfStatementNode;
class Context;

// statement        = if_statement | while_statement | simple_statement | "{" , {statement} , "}" ;
class StatementNode : public Node {
    std::vector<std::unique_ptr<StatementNode>> statements;
    std::unique_ptr<SimpleStatementNode> simpleStatement;
    std::unique_ptr<WhileStatementNode> whileStatement;
    std::unique_ptr<IfStatementNode> ifStatement;
    enum StatementType {
        WHILE,
        IF,
        SIMPLE,
        BLOCK,
    };
    StatementType statementType;
public:
    void addStatement(std::unique_ptr<StatementNode> node);
    void setWhileStatement(std::unique_ptr<WhileStatementNode> node);
    void setIfStatement(std::unique_ptr<IfStatementNode> node);
    void setSimpleStatement(std::unique_ptr<SimpleStatementNode> node);
    void print(int depth = 0);
    void execute(Context & context);
};


#endif //_TKOM__INTERPRETER_STATEMENTNODE_H
