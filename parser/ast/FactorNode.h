#ifndef _TKOM__INTERPRETER_FACTORNODE_H
#define _TKOM__INTERPRETER_FACTORNODE_H

#include <memory>
#include <vector>
#include <variant>
#include <string>
#include "Node.h"
#include "../../lexer/Token.h"
#include "../../execution/Context.h"
#include "../../structures/GeographicCoordinate.h"
#include "../../structures/GeographicDistance.h"
#include "../../structures/GeographicPosition.h"

using Value = std::variant<std::monostate, std::string, int, float,
        GeographicCoordinate, GeographicDistance, GeographicPosition>;

class FunctionCallNode;
class ExpressionNode;

//factor = ["-"] , ( integer | float | id | function_call | "(" , expression , ")" )
//       | string | geo_dist | geo | geo_coord ;
class FactorNode : public Node {
    bool isPositive = true;
    Value value;
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
    void setValue(Value value);
    void setId(std::string id);
    void setFunction(std::unique_ptr<FunctionCallNode> functionCall);
    void setExpression(std::unique_ptr<ExpressionNode> expression);
    void setPositive();
    void setNegative();

    std::string toString(int depth = 0) const;
    Value evaluate(Context & context) const;

    inline static const std::string factorTypeNames[4] = {
            "VALUE",
            "ID",
            "FUNCTION_CALL",
            "EXPRESSION",
    };
};


#endif //_TKOM__INTERPRETER_FACTORNODE_H
