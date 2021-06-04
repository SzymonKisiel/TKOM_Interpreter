//
// Created by kislu on 03.06.2021.
//

#ifndef _TKOM__INTERPRETER_NODE_H
#define _TKOM__INTERPRETER_NODE_H


#include "ProgramNode.h"
#include "StatementNode.h"
#include "WhileStatementNode.h"
#include "DeclarationNode.h"
#include "FunctionNode.h"
#include "TestNode.h"
#include "IfStatementNode.h"

class Node {
public:
    Node() = default;
    //virtual const bool isTerminal() = 0;
    //virtual void print(int depth = 0) = 0;
};

#endif //_TKOM__INTERPRETER_NODE_H
