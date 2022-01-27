#ifndef _TKOM__INTERPRETER_WHILESTATEMENTNODE_H
#define _TKOM__INTERPRETER_WHILESTATEMENTNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"


class StatementNode;
class Context;

// while_statement  = "while" , "(" , expression, ")", statement ;
class WhileStatementNode : public Node {
    std::unique_ptr<ExpressionNode> condition;
    std::unique_ptr<StatementNode> statement;
public:
    void setCondition(std::unique_ptr<ExpressionNode> node);
    void setStatement(std::unique_ptr<StatementNode> node);
    std::string toString(int depth = 0);
    Value execute(Context & context);
};

#endif //_TKOM__INTERPRETER_WHILESTATEMENTNODE_H
