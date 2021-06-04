//
// Created by kislu on 03.06.2021.
//

#ifndef _TKOM__INTERPRETER_IFSTATEMENTNODE_H
#define _TKOM__INTERPRETER_IFSTATEMENTNODE_H

#include "Node.h"

class IfStatementNode : public Node {
    std::unique_ptr<Node> ifCondition;
    std::unique_ptr<Node> ifStatement;
    std::vector<std::unique_ptr<Node>> elsifCondition;
    std::vector<std::unique_ptr<Node>> elsifStatement;
    std::unique_ptr<Node> elseCondition;
    std::unique_ptr<Node> elseStatement;
};


#endif //_TKOM__INTERPRETER_IFSTATEMENTNODE_H
