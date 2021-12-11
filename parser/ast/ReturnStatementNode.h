#ifndef _TKOM__INTERPRETER_RETURNSTATEMENTNODE_H
#define _TKOM__INTERPRETER_RETURNSTATEMENTNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
//#include "../../execution/Context.h"


// return_statement = "return" , [expression] , ";" ;
class ReturnStatementNode : public Node {
    std::unique_ptr<ExpressionNode> returnExpression;
public:
    void setReturnExpression(std::unique_ptr<ExpressionNode> returnExpression);
    std::string toString();
    void print(int depth = 0);
//    variant<std::monostate, string, int, float> execute(Context & context);
};


#endif //_TKOM__INTERPRETER_RETURNSTATEMENTNODE_H
