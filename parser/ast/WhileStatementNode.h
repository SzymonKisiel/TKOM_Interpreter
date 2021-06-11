#ifndef _TKOM__INTERPRETER_WHILESTATEMENTNODE_H
#define _TKOM__INTERPRETER_WHILESTATEMENTNODE_H

#include "Node.h"
#include "ExpressionNode.h"
#include "StatementNode.h"
#include "../../execution/Context.h"

class StatementNode;
class Context;

// while_statement  = "while" , "(" , expression, ")", statement ;
class WhileStatementNode : public Node {
    std::unique_ptr<ExpressionNode> condition;
    std::unique_ptr<StatementNode> statement;
    std::string name = "";
public:
    WhileStatementNode(std::string name);
    void setCondition(std::unique_ptr<ExpressionNode> node);
    void setStatement(std::unique_ptr<StatementNode> node);
    void print(int depth = 0);
    void execute(Context & context);
};

#endif //_TKOM__INTERPRETER_WHILESTATEMENTNODE_H
