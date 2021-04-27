#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>

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

class Token {
    TokenType type;
    int row;
    int column;
    variant<string, int> value;
public:
    Token(TokenType type, int row, int column, variant<string, int> value) :
        type(type), row(row), column(column), value(value) {
    }
    Token(TokenType type, int row, int column) :
        type(type), row(row), column(column), value(""){
    }
    Token(TokenType type) : type(type) {
        Token(type, 0, 0);
    }
    TokenType getType() {
        return this->type;
    }
    string getStringValue() {
        return std::get<string>(this->value);
    }
    int getIntValue() {
        return std::get<int>(this->value);
    }
    int getRow() {
        return this->row;
    }
    int getColumn() {
        return this->column;
    }
};


#endif // TOKEN_H
