#ifndef _TKOM__INTERPRETER_PARAMETERSNODE_H
#define _TKOM__INTERPRETER_PARAMETERSNODE_H

#include "Node.h"
#include "../../lexer/Token.h"
#include <vector>

// parameters = parameter , {"," , parameter} ;
// parameter  = type , id ;
class ParametersNode : public Node {
    std::vector<TokenType> types;
    std::vector<std::string> identifiers;
public:
    void addType(TokenType type);
    void addIdentifier(std::string identifier);
    std::string toString();
    void print(int depth = 0);
};


#endif //_TKOM__INTERPRETER_PARAMETERSNODE_H
