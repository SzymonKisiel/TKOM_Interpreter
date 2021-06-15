#ifndef _TKOM__INTERPRETER_VISITCHECKTYPE_H
#define _TKOM__INTERPRETER_VISITCHECKTYPE_H

#include "../lexer/Token.h"

struct VisitCheckType {
    bool operator()(int&, TokenType& type)       { return type == TokenType::T_TYPE_INT; }
    bool operator()(float&, TokenType& type)     { return type == TokenType::T_TYPE_FLOAT; }
    bool operator()(string&, TokenType& type)    { return type == TokenType::T_TYPE_STRING; }
    bool operator()(auto&, auto&)                { return false; }
};


#endif //_TKOM__INTERPRETER_VISITCHECKTYPE_H
