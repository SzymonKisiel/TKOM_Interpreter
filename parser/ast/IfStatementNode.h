#ifndef _TKOM__INTERPRETER_IFSTATEMENTNODE_H
#define _TKOM__INTERPRETER_IFSTATEMENTNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"
#include "../../execution/Context.h"


class StatementNode;
// if_statement     = "if" , "(" , expression, ")" , statement
//                 , {"elsif" , "(" , expression, ")" , statement}
//                 , ["else" , statement] ;
class IfStatementNode : public Node {
    std::unique_ptr<ExpressionNode> ifCondition;
    std::unique_ptr<StatementNode> ifStatement;
    std::vector<std::unique_ptr<ExpressionNode>> elsifCondition;
    std::vector<std::unique_ptr<StatementNode>> elsifStatement;
    std::unique_ptr<StatementNode> elseStatement;
public:
    void setIfCondition(std::unique_ptr<ExpressionNode> node);
    void setIfStatement(std::unique_ptr<StatementNode> node);
    void addElsifCondition(std::unique_ptr<ExpressionNode> node);
    void addElsifStatement(std::unique_ptr<StatementNode> node);
    void setElseStatement(std::unique_ptr<StatementNode> node);
    void print(int depth = 0);
    void execute(Context & context);
};

#endif //_TKOM__INTERPRETER_IFSTATEMENTNODE_H