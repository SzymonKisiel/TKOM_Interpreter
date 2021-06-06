#ifndef _TKOM__INTERPRETER_STATEMENTNODE_H
#define _TKOM__INTERPRETER_STATEMENTNODE_H

#include "Node.h"
#include "SimpleStatementNode.h"

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
};

WhileStatementNode::WhileStatementNode(std::string name) : name(std::move(name)) {
}

void WhileStatementNode::setCondition(std::unique_ptr<ExpressionNode> node) {
    if (node != nullptr)
        condition = std::move(node);
}

void WhileStatementNode::setStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr)
        statement = std::move(node);
}

void WhileStatementNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << "WHILE_STATEMENT" << std::endl;
    condition->print(depth+1);
    statement->print(depth+1);
}


void IfStatementNode::setIfCondition(std::unique_ptr<ExpressionNode> node) {
    ifCondition = std::move(node);
}

void IfStatementNode::setIfStatement(std::unique_ptr<StatementNode> node) {
    ifStatement = std::move(node);
}

void IfStatementNode::addElsifCondition(std::unique_ptr<ExpressionNode> node) {
    if (node != nullptr)
        elsifCondition.push_back(std::move(node));
}

void IfStatementNode::addElsifStatement(std::unique_ptr<StatementNode> node) {
    if (node != nullptr)
        elsifStatement.push_back(std::move(node));
}

void IfStatementNode::setElseStatement(std::unique_ptr<StatementNode> node) {
    elseStatement = std::move(node);
}

void IfStatementNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << "IF_STATEMENT" << std::endl;
    if (ifCondition != nullptr)
        ifCondition->print(depth+1);
    if (ifStatement != nullptr)
        ifStatement->print(depth+1);
    if (!elsifCondition.empty()) {
        for (const auto &child: elsifCondition)
            child->print(depth+1);
        for (const auto &child: elsifStatement)
            child->print(depth+1);
    }
    if (elseStatement != nullptr)
        elseStatement->print(depth+1);
}



#endif //_TKOM__INTERPRETER_STATEMENTNODE_H
