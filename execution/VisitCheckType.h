#ifndef _TKOM__INTERPRETER_VISITCHECKTYPE_H
#define _TKOM__INTERPRETER_VISITCHECKTYPE_H

#include "../lexer/Token.h"

struct VisitCheckType {
    bool operator()(int&, TokenType& type)       { return type == TokenType::T_TYPE_INT; }
    bool operator()(float&, TokenType& type)     { return type == TokenType::T_TYPE_FLOAT; }
    bool operator()(string&, TokenType& type)    { return type == TokenType::T_TYPE_STRING; }
    bool operator()(auto&, auto&)                { return false; }
};

struct VisitCompareType {
    bool operator()(int&, int&)       { return true; }
    bool operator()(float&, float&)   { return true; }
    bool operator()(string&, string&) { return true; }
    bool operator()(auto&, auto&)     { return false; }
};


#endif //_TKOM__INTERPRETER_VISITCHECKTYPE_H
