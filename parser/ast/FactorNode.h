#ifndef _TKOM__INTERPRETER_FACTORNODE_H
#define _TKOM__INTERPRETER_FACTORNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
//#include "../../execution/Context.h"


class FunctionCallNode;
class ExpressionNode;

// factor          = integer | float | geo | string | (["-"] , id) | function_call | "(" , expression , ")"  ;
class FactorNode : public Node {
    TokenType type;
    bool isPositive = true;
    variant<std::monostate, string, int, float /*, GeographicalCoordinate*/> value;
    std::string id;
    std::unique_ptr<FunctionCallNode> functionCall;
    std::unique_ptr<ExpressionNode> expression;
    enum FactorType {
        VALUE,
        ID,
        FUNCTION_CALL,
        EXPRESSION,
    };
    FactorType factorType;
public:
    void setValue(TokenType type, variant<std::monostate, string, int, float> value);
    void setId(std::string id);
    void setFunction(std::unique_ptr<FunctionCallNode> functionCall);
    void setGeo();
    void setExpression(std::unique_ptr<ExpressionNode> expression);
    void setNegative();
    FactorType getType();
    std::string toString();
    void print(int depth = 0);
//    variant<std::monostate, string, int, float> evaluate(Context & context);
    inline static const std::string factorTypeNames[4] = {
            "VALUE",
            "ID",
            "FUNCTION_CALL",
            "EXPRESSION",
    };
};


#endif //_TKOM__INTERPRETER_FACTORNODE_H
