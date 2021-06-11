#ifndef _TKOM__INTERPRETER_STATEMENTNODE_H
#define _TKOM__INTERPRETER_STATEMENTNODE_H

#include "Node.h"
#include "SimpleStatementNode.h"
#include "../../execution/Context.h"
#include <memory>

class StatementNode;

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
    void addStatement(std::unique_ptr<StatementNode> node) {
        if (node != nullptr)
            statements.push_back(std::move(node));
    }

    void setWhileStatement(std::unique_ptr<WhileStatementNode> node) {
        whileStatement = std::move(node);
    }

    void setIfStatement(std::unique_ptr<IfStatementNode> node) {
        ifStatement = std::move(node);
    }

    void setSimpleStatement(std::unique_ptr<SimpleStatementNode> node) {
        simpleStatement = std::move(node);
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << "STATEMENT" << std::endl;
        for (const auto &child: statements) {
            child->print(depth+1);
        }
        if (whileStatement != nullptr)
            whileStatement->print(depth+1);
        if (ifStatement != nullptr)
            ifStatement->print(depth+1);
        if (simpleStatement != nullptr)
            simpleStatement->print(depth+1);
    }

    void execute(Context & context) {
        //switch (statementType)
        ifStatement->execute(context);
    }
};


#endif //_TKOM__INTERPRETER_STATEMENTNODE_H
