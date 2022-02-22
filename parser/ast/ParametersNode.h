#ifndef _TKOM__INTERPRETER_PARAMETERSNODE_H
#define _TKOM__INTERPRETER_PARAMETERSNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
//#include "../../execution/Context.h"


// parameters = parameter , {"," , parameter} ;
// parameter  = type , id ;
class ParametersNode : public Node {
    std::vector<TokenType> types;
    std::vector<std::string> identifiers;
public:
    void addType(TokenType type);
    void addIdentifier(std::string identifier);

    std::string toString(int depth = 0) const;
    std::vector<TokenType> getTypes() const;
    std::vector<std::string> getIdentifiers() const;
};


#endif //_TKOM__INTERPRETER_PARAMETERSNODE_H
