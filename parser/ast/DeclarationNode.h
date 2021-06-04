#ifndef _TKOM__INTERPRETER_DECLARATIONNODE_H
#define _TKOM__INTERPRETER_DECLARATIONNODE_H

class DeclarationNode : public Node {
    std::string id;
    //type
    //value
    std::unique_ptr<Node> expression;
};


#endif //_TKOM__INTERPRETER_DECLARATIONNODE_H
