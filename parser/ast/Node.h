#ifndef _TKOM__INTERPRETER_NODE_H
#define _TKOM__INTERPRETER_NODE_H



class Node {
public:
    Node() = default;
    //virtual const bool isTerminal() = 0;
    //virtual void print(int depth = 0) = 0;
    //virtual void execute(Context & context) = 0;

    const std::string prefix = "  ";
};

#include "AddExpressionNode.h"
#include "ArgumentsNode.h"
#include "AssignmentNode.h"
#include "DeclarationNode.h"
#include "ExpressionNode.h"
#include "FactorNode.h"
#include "FunctionCallNode.h"
#include "FunctionNode.h"
#include "IfStatementNode.h"
#include "MultExpressionNode.h"
#include "ParametersNode.h"
#include "ProgramNode.h"
#include "ReturnStatementNode.h"
#include "SimpleStatementNode.h"
#include "StatementNode.h"
#include "WhileStatementNode.h"

#endif //_TKOM__INTERPRETER_NODE_H
