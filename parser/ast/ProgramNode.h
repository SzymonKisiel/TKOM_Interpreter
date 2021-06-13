#ifndef _TKOM__INTERPRETER_PROGRAMNODE_H
#define _TKOM__INTERPRETER_PROGRAMNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"

class FunctionNode;

// program = {statement | function} ;
class ProgramNode : public Node {
    std::vector<std::shared_ptr<FunctionNode>> functions;
    std::vector<std::unique_ptr<StatementNode>> statements;
public:
    void addFunction(std::shared_ptr<FunctionNode> node);
    void addStatement(std::unique_ptr<StatementNode> node);
    const bool isTerminal();
    void print(int depth = 0);
    void execute();
};


#endif //_TKOM__INTERPRETER_PROGRAMNODE_H
