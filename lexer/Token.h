#ifndef _TKOM__INTERPRETER_TOKEN_H
#define _TKOM__INTERPRETER_TOKEN_H



#include <string>
#include <variant>

#include <iostream>

using namespace std;

enum TokenType {
    T_WHILE,
    T_IF,
    T_ELSIF,
    T_ELSE,
    T_RETURN,
    T_ASSIGN,
    T_OPEN,
    T_CLOSE,
    T_OPEN_BRACKET,
    T_CLOSE_BRACKET,
    T_SEMICOLON,
    T_COMMA,
    T_ID,
    T_LESS,
    T_GREATER,
    T_LESS_OR_EQUAL,
    T_GREATER_OR_EQUAL,
    T_EQUAL,
    T_NOT_EQUAL,
    T_PLUS,
    T_MINUS,
    T_OR,
    T_MUL,
    T_DIV,
    T_AND,
    T_TYPE_VOID,
    T_TYPE_INT,
    T_TYPE_FLOAT,
    T_TYPE_STRING,
    T_TYPE_GEO,
    T_TYPE_GEOCOORD,
    T_INT,
    T_FLOAT,
    T_STRING,
    T_GEO_DEGREE,
    T_GEO_MINUTE,
    T_GEO_SECOND,
    T_GEO_DIRECTION_N,
    T_GEO_DIRECTION_S,
    T_GEO_DIRECTION_W,
    T_GEO_DIRECTION_E,
    T_MULTICOMMENT,
    T_END,
    T_UNKNOWN
};

std::string tokenTypeToString(TokenType tokenType);

class Token {
    TokenType type;
    int row;
    int column;
    variant<std::monostate, string, int, float> value;
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
    Token(TokenType type, int row, int column, variant<std::monostate, string, int, float> value) :
            type(type), row(row), column(column), value(std::move(value)) {
    }
    Token(TokenType type, int row, int column) :
            type(type), row(row), column(column), value(std::monostate{}) {
    }
    Token(TokenType type) : type(type) {
        Token(type, 0, 0);
    }
    const TokenType getType() {
        return this->type;
    }
    variant<std::monostate, string, int, float> getValue() {
        return value;
    }
    const string getStringValue() {
        return std::get<string>(this->value);
    }
    const int getIntValue() {
        return std::get<int>(this->value);
    }

    const float getFloatValue() {
        return std::get<float>(this->value);
    }

//    variant<std::monostate, string, int, float> getValue() {
//        return value;
//    }

    const int getRow() {
        return this->row;
    }
    const int getColumn() {
        return this->column;
    }

    bool isType() {
        if (this->type >= TokenType::T_TYPE_VOID && this->type <= TokenType::T_TYPE_GEOCOORD)
            return true;
        return false;
    }

    bool isCompOperator() {
        if (this->type >= TokenType::T_LESS && this->type <= TokenType::T_NOT_EQUAL)
            return true;
        return false;
    }
    bool isMultOperator() {
        if (this->type == TokenType::T_MUL ||
            this->type == TokenType::T_AND)
            return true;
        return false;
    }
    bool isAddOperator() {
        if (this->type == TokenType::T_PLUS ||
            this->type == TokenType::T_MINUS ||
            this->type == TokenType::T_OR)
            return true;
        return false;
    }
    bool isOperator() {
        if (this->type >= TokenType::T_LESS && this->type <= TokenType::T_AND)
            return true;
        return false;
    }
    bool isExpressionPart() {
        if (isOperator())
            return true;
        if (this->type == TokenType::T_INT ||
            this->type == TokenType::T_FLOAT ||
            this->type == TokenType::T_STRING ||
            this->type == TokenType::T_OPEN ||
            this->type == TokenType::T_CLOSE ||
            this->type == TokenType::T_ID /*||
            this->type == TokenType::T_COMMA*/)
            return true;
        return false;
    }

    string getTypeString() {
        return tokenTypeNames[this->getType()];
    }

    void print() {
        cout << this->getRow() << '\t'
             << this->getColumn() << '\t'
             << tokenTypeNames[this->getType()] << '\t';
//        if (std::string* ptr_str = std::get_if<std::string>(&value); ptr_str != nullptr)
//            cout << *ptr_str;
        if (this->getType() == TokenType::T_INT)
            cout << this->getIntValue();
        else if (this->getType() == TokenType::T_FLOAT)
            cout << this->getFloatValue();
        else if (this->getType() == TokenType::T_STRING)
            cout << this->getStringValue();
        cout << endl;
//        if (this->getType() == TokenType::T_INT)
//            cout << std::get<int>(this->getValue()) << endl;
//        else if (this->getType() == TokenType::T_FLOAT)
//            cout << std::get<float>(this->getValue()) << endl;
//        else if (this->getType() == TokenType::T_STRING)
//            cout << std::get<std::string>(this->getValue()) << endl;
    }
};

#endif //_TKOM__INTERPRETER_TOKEN_H
