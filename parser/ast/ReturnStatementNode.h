#ifndef _TKOM__INTERPRETER_RETURNSTATEMENTNODE_H
#define _TKOM__INTERPRETER_RETURNSTATEMENTNODE_H


class ReturnStatementNode : public Node {
    std::unique_ptr<Expression> returnExpression;
};


#endif //_TKOM__INTERPRETER_RETURNSTATEMENTNODE_H
