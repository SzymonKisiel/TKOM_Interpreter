#ifndef _TKOM__INTERPRETER_STATEMENTNODE_H
#define _TKOM__INTERPRETER_STATEMENTNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
//#include "../../execution/Context.h"


class WhileStatementNode;
class IfStatementNode;
class SimpleStatementNode;

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
        NONE,
    };
    StatementType statementType = StatementType::NONE;
public:
    void addStatement(std::unique_ptr<StatementNode> node);
    void setWhileStatement(std::unique_ptr<WhileStatementNode> node);
    void setIfStatement(std::unique_ptr<IfStatementNode> node);
    void setSimpleStatement(std::unique_ptr<SimpleStatementNode> node);
    std::string toString(int depth = 0);
//    variant<std::monostate, string, int, float> execute(Context & context);
};


#endif //_TKOM__INTERPRETER_STATEMENTNODE_H
