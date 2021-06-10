#ifndef _TKOM__INTERPRETER_FACTORNODE_H
#define _TKOM__INTERPRETER_FACTORNODE_H

//#include "FunctionCallNode.h"
//#include "ExpressionNode.h"
#include "../../lexer/Token.h"

// factor          = integer | float | geo | string | (["-"] , id) | function_call | "(" , expression , ")"  ;
class FactorNode : public Node {
    TokenType type;
    bool isPositive = true;

    variant<std::monostate, string, int, float /*, GeographicalCoordinate*/> value;
    std::string id;
    //std::unique_ptr<FunctionCallNode> functionCall;
    //std::unique_ptr<ExpressionNode> expression;
    enum FactorType {
        VALUE,
        ID,
        FUNCTION_CALL,
        EXPRESSION,
    };
    FactorType factorType;

public:
    void setValue(TokenType type, variant<std::monostate, string, int, float> value) {
        this->type = type;
        this->value = std::move(value);
        factorType = FactorType::VALUE;
    }

    void setId(std::string id) {
        this->id = std::move(id);
        factorType = FactorType::ID;
    }

//    void setFunction(std::unique_ptr<FunctionCallNode> functionCall) {
//        this->functionCall = std::move(functionCall);
//        factorType = FactorType::FUNCTION_CALL;
//    }

    void setGeo() {

    }

    void setExpression() {

    }

    void setNegative() {
        isPositive = false;
    }

    FactorType getType() {
        return factorType;
    }

    std::string toString() {
        return std::string("FACTOR - ").append(tokenTypeToString(type));
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
    }

    variant<std::monostate, string, int, float> evaluate() {
        if (factorType == VALUE)
            return value;
    }
};


#endif //_TKOM__INTERPRETER_FACTORNODE_H
