#include <iostream>

#include "Lexer.h"
#include "Token.h"

using namespace std;

const char* tokenTypeNames[] = {
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

void printToken(Token * token) {
    cout << token->getRow() << '\t'
         << token->getColumn() << '\t'
         << tokenTypeNames[token->getType()] << '\t';
    if (token->getType() == TokenType::T_INT)
        cout << token->getIntValue() << endl;
    else
        cout << token->getStringValue() << endl;
}

int main()
{
    Source source("test2.txt");
    Lexer lexer(source);
    Token * token;
    TokenType type;
    while (type != TokenType::T_END) {
        token = lexer.getNextToken();
        type = token->getType();
        printToken(token);
    }
    return 0;
}
