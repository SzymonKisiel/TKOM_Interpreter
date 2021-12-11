#ifndef _TKOM__INTERPRETER_FUNCTIONCALLNODE_H
#define _TKOM__INTERPRETER_FUNCTIONCALLNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
//#include "../../execution/Context.h"


class ArgumentsNode;

// function_call    = id ,  "(" , [arguments] , ")" ;
class FunctionCallNode : public Node {
    std::string id;
    std::shared_ptr<ArgumentsNode> arguments;
public:
    void setId(std::string id);
    void setArguments(std::shared_ptr<ArgumentsNode> arguments);
    std::string toString();
    void print(int depth = 0);
//    std::variant<std::monostate, string, int, float> execute(Context & context);
};


#endif //_TKOM__INTERPRETER_FUNCTIONCALLNODE_H
