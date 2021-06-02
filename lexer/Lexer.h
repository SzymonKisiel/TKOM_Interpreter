#ifndef _TKOM__INTERPRETER_LEXER_H
#define _TKOM__INTERPRETER_LEXER_H



#include <map>
#include <memory>
#include <cmath>

#include "Token.h"
#include "Source.h"

using namespace std;

class Lexer {
    inline static const std::map<string, TokenType> keywords = {
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
            {"N", TokenType::T_GEO_DIRECTION_N},
            {"S", TokenType::T_GEO_DIRECTION_S},
            {"W", TokenType::T_GEO_DIRECTION_W},
            {"E", TokenType::T_GEO_DIRECTION_E}
    };
    Source & source;

    char character;

    int row = 0;
    int column = 0;

public:
    Lexer(Source & s) : source(s) {
        character = source.getNextChar();
    }
    std::unique_ptr<Token> getNextToken() {
        while (isspace(character)) {
            character = source.getNextChar();
        }

        skipComments();

        row = source.getRow();
        column = source.getColumn();

        if (character == EOF)
            return std::make_unique<Token>(TokenType::T_END, row, column);

        std::unique_ptr<Token> token;
        token = buildNumber();
        if (token != nullptr)
            return token;
        token = buildString();
        if (token != nullptr)
            return token;
        token = buildId();
        if (token != nullptr)
            return token;

        switch (character) {
            case '=': //==
                character = source.getNextChar();
                if (character != '=')
                    return std::make_unique<Token>(TokenType::T_ASSIGN, row, column);
                token = std::make_unique<Token>(TokenType::T_EQUAL, row, column);
                break;
            case '(':
                token = std::make_unique<Token>(TokenType::T_OPEN, row, column);
                break;
            case ')':
                token = std::make_unique<Token>(TokenType::T_CLOSE, row, column);
                break;
            case '{':
                token = std::make_unique<Token>(TokenType::T_OPEN_BRACKET, row, column);
                break;
            case '}':
                token = std::make_unique<Token>(TokenType::T_CLOSE_BRACKET, row, column);
                break;
            case ';':
                token = std::make_unique<Token>(TokenType::T_SEMICOLON, row, column);
                break;
            case ',':
                token = std::make_unique<Token>(TokenType::T_COMMA, row, column);
                break;
            case '<': // <=
                character = source.getNextChar();
                if (character != '=')
                    return std::make_unique<Token>(TokenType::T_LESS, row, column);
                token = std::make_unique<Token>(TokenType::T_LESS_OR_EQUAL, row, column);
                break;
            case '>': // >=
                character = source.getNextChar();
                if (character != '=')
                    return std::make_unique<Token>(TokenType::T_GREATER, row, column);
                token = std::make_unique<Token>(TokenType::T_GREATER_OR_EQUAL, row, column);
                break;
            case '!': // !=
                character = source.getNextChar();
                if (character != '=')
                    return std::make_unique<Token>(TokenType::T_UNKNOWN, row, column);
                token = std::make_unique<Token>(TokenType::T_NOT_EQUAL, row, column);
                break;
            case '+':
                token = std::make_unique<Token>(TokenType::T_PLUS, row, column);
                break;
            case '-':
                token = std::make_unique<Token>(TokenType::T_MINUS, row, column);
                break;
            case '*':
                token = std::make_unique<Token>(TokenType::T_MUL, row, column);
                break;
            case '/': //division or multiline comment
                character = source.getNextChar();
                if (character != '*')
                    return std::make_unique<Token>(TokenType::T_DIV, row, column);
                character = source.getNextChar();
                {
                    bool commentEnd = false;
                    while (!commentEnd) {
                        if (character == EOF)
                            throw "Niezakończony komentarz";
                        if (character == '*') {
                            character = source.getNextChar();
                            if (character == '/')
                                commentEnd = true;
                        }
                        character = source.getNextChar();
                    }
                    return std::make_unique<Token>(TokenType::T_MULTICOMMENT, row, column);
                }
                break;
            case '^':
                token = std::make_unique<Token>(TokenType::T_GEO_DEGREE, row, column);
                break;
            case '\'':
                character = source.getNextChar();
                if (character != '\'')
                    return std::make_unique<Token>(TokenType::T_GEO_MINUTE, row, column);
                token = std::make_unique<Token>(TokenType::T_GEO_SECOND, row, column);
                break;
        }
        if (token == nullptr) {
            token = std::make_unique<Token>(TokenType::T_UNKNOWN, row, column);
        }

        character = source.getNextChar();
        return token;
    }
    void skipComments() {
        if (character == '#') {
            while (character != '\n' && character != EOF)
                character = source.getNextChar();
            character = source.getNextChar();
        }
    }
    std::unique_ptr<Token> buildNumber() {
        if (isdigit(character)) {
            int value = 0;
            while (isdigit(character)) {
                value = 10 * value + character - '0';
                character = source.getNextChar();
            }
            if (character != '.')
                return std::make_unique<Token>(TokenType::T_INT, row, column, value);

            // float
            float floatValue = static_cast<float>(value);
            character = source.getNextChar();
            for (int i = 1; isdigit(character); ++i) { //nieskończone liczby!!
                floatValue += (character - '0')/pow(10,i);
                character = source.getNextChar();
            }
            return std::make_unique<Token>(TokenType::T_FLOAT, row, column , floatValue);
        }
        return nullptr;
    }
    std::unique_ptr<Token> buildString() {
        if (character == '"') {
            string value = "";
            character = source.getNextChar();
            while (character != '"') {
                if (character == EOF)
                    throw "Niezakończony string";
                if (character == '\\') {
                    character = source.getNextChar();
                }
                value.push_back(character);
                character = source.getNextChar();
            }
            character = source.getNextChar();
            return std::make_unique<Token>(TokenType::T_STRING, row, column, value);
        }
        return nullptr;
    }
    std::unique_ptr<Token> buildId() {
        if (isalpha(character)) {
            string value = "";
            while (isalpha(character)) {
                value.push_back(character);
                character = source.getNextChar();
            }
            if (const auto itr = keywords.find(value); itr != keywords.end()) {
                return std::make_unique<Token>(itr->second, row, column);
            }
            return std::make_unique<Token>(TokenType::T_ID, row, column, value);
        }
        return nullptr;
    }
};


#endif //_TKOM__INTERPRETER_LEXER_H
