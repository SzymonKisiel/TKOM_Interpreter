#ifndef _TKOM__INTERPRETER_FACTORNODE_H
#define _TKOM__INTERPRETER_FACTORNODE_H

// factor          = integer | float | geo | string | (["-"] , id) | function_call | "(" , expression , ")"  ;
class FactorNode : public Node {
    TokenType type;
    //value
public:
    void setType(TokenType type) {
        this->type = type;
    }

    void setValue() {

    }

    std::string toString() {
        return std::string("FACTOR - ").append(tokenTypeToString(type));
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
    }
};


#endif //_TKOM__INTERPRETER_FACTORNODE_H
