#ifndef _TKOM__INTERPRETER_TOKEN_H
#define _TKOM__INTERPRETER_TOKEN_H



#include <string>
#include <variant>
#include <iostream>
#include "TokenType.h"

using namespace std;


std::string tokenTypeToString(TokenType);

class Token {
    enum TokenType type;
    int row;
    int column;
    std::variant<std::monostate, std::string, int, float> value = std::monostate();
public:
    inline static const std::string tokenTypeNames[50] = {
            "T_WHILE",
            "T_IF",
            "T_ELSIF",
            "T_ELSE",
            "T_RETURN",
            "T_ASSIGN",
            "T_OPEN",
            "T_CLOSE",
            "T_OPEN_BRACKET",
            "T_CLOSE_BRACKET",
            "T_SEMICOLON",
            "T_COMMA",
            "T_ID",
            "T_LESS",
            "T_GREATER",
            "T_LESS_OR_EQUAL",
            "T_GREATER_OR_EQUAL",
            "T_EQUAL",
            "T_NOT_EQUAL",
            "T_PLUS",
            "T_MINUS",
            "T_OR",
            "T_MUL",
            "T_DIV",
            "T_AND",
            "T_TYPE_VOID",
            "T_TYPE_INT",
            "T_TYPE_FLOAT",
            "T_TYPE_STRING",
            "T_TYPE_GEO",
            "T_TYPE_GEOCOORD",
            "T_TYPE_GEODIST",
            "T_INT",
            "T_FLOAT",
            "T_STRING",
            "T_GEO_DEGREE",
            "T_GEO_MINUTE",
            "T_GEO_SECOND",
            "T_GEO_DIRECTION_N",
            "T_GEO_DIRECTION_S",
            "T_GEO_DIRECTION_W",
            "T_GEO_DIRECTION_E",
            "T_MULTICOMMENT",
            "T_END",
            "T_UNKNOWN",
    };

    Token(enum TokenType type, int row, int column, std::variant<std::monostate, string, int, float> value);
    Token(enum TokenType type, int row, int column);
    Token(enum TokenType type);
    const enum TokenType getType();
    std::variant<std::monostate, string, int, float> getValue();
    const string* getStringValue();
    const int* getIntValue();
    const float* getFloatValue();
    const int getRow();
    const int getColumn();
    const bool isValue();
    const bool isType();
    const bool isCompOperator();
    const bool isMultOperator();
    const bool isAddOperator();
    const bool isOperator();
    const bool isGeoDirection();
    const bool isGeoUnit();
    const string getTypeString();
    void print();
};

#endif //_TKOM__INTERPRETER_TOKEN_H
