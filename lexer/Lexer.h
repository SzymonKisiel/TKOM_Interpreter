#ifndef _TKOM__INTERPRETER_LEXER_H
#define _TKOM__INTERPRETER_LEXER_H



#include <map>
#include <memory>
#include <cmath>

#include "Token.h"
#include "TokenType.h"
#include "Source.h"
#include "../exception/LexerException.h"

using namespace std;

class Lexer {
    inline const static std::map<string, TokenType> keywords = {
            {"while", TokenType::T_WHILE},
            {"if", TokenType::T_IF},
            {"elsif", TokenType::T_ELSIF},
            {"else", TokenType::T_ELSE},
            {"return", TokenType::T_RETURN},
            {"and", TokenType::T_AND},
            {"or", TokenType::T_OR},
            {"void", TokenType::T_TYPE_VOID},
            {"int", TokenType::T_TYPE_INT},
            {"float", TokenType::T_TYPE_FLOAT},
            {"string", TokenType::T_TYPE_STRING},
            {"geo", TokenType::T_TYPE_GEO},
            {"geocoord", TokenType::T_TYPE_GEOCOORD},
            {"geodist", TokenType::T_TYPE_GEODIST},
            {"N", TokenType::T_GEO_DIRECTION_N},
            {"S", TokenType::T_GEO_DIRECTION_S},
            {"W", TokenType::T_GEO_DIRECTION_W},
            {"E", TokenType::T_GEO_DIRECTION_E}
    };
    const int MAX_ID_LENGTH = 50;
    const int MAX_STRING_LENGTH = 1000;

    Source & source;
    char character {};
    int row = 0;
    int column = 0;

public:
    Lexer(Source & s);
    std::unique_ptr<Token> getNextToken();
    void skipComments();
    std::unique_ptr<Token> buildNumber();
    std::unique_ptr<Token> buildString();
    std::unique_ptr<Token> buildId();
};


#endif //_TKOM__INTERPRETER_LEXER_H
