#ifndef LEXER_H
#define LEXER_H

#include <map>

#include "Token.h"
#include "Source.h"

using namespace std;

class Lexer {
    std::map<string, TokenType> keywords = {
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
        //this->source = s;
        character = source.getNextChar();
    }
    Token * getNextToken() {
        while (isspace(character)) {
            if (character == '\n')
                ++row;
            character = source.getNextChar();
        }

        skipComments();

        row = source.getRow();
        column = source.getColumn();

        if (character == EOF)
            return new Token(TokenType::T_END, row, column);

        Token * token;
        token = buildNumber();
        if (token != NULL)
            return token;
        token = buildString();
        if (token != NULL)
            return token;
        token = buildId();
        if (token != NULL)
            return token;

        switch (character) {
            case '=': //==
                character = source.getNextChar();
                if (character != '=')
                    return new Token(TokenType::T_ASSIGN, row, column);
                token = new Token(TokenType::T_EQUAL, row, column);
                break;
            case '(':
                token = new Token(TokenType::T_OPEN, row, column);
                break;
            case ')':
                token = new Token(TokenType::T_CLOSE, row, column);
                break;
            case '{':
                token = new Token(TokenType::T_OPEN_BRACKET, row, column);
                break;
            case '}':
                token = new Token(TokenType::T_CLOSE_BRACKET, row, column);
                break;
            case ';':
                token = new Token(TokenType::T_SEMICOLON, row, column);
                break;
            case ',':
                token = new Token(TokenType::T_COMMA, row, column);
                break;
            case '<': // <=
                character = source.getNextChar();
                if (character != '=')
                    return new Token(TokenType::T_LESS, row, column);
                token = new Token(TokenType::T_LESS_OR_EQUAL, row, column);
                break;
            case '>': // >=
                character = source.getNextChar();
                if (character != '=')
                    return new Token(TokenType::T_GREATER, row, column);
                token = new Token(TokenType::T_GREATER_OR_EQUAL, row, column);
                break;
            case '!': // !=
                character = source.getNextChar();
                if (character != '=')
                    return new Token(TokenType::T_UNKNOWN, row, column);
                token = new Token(TokenType::T_NOT_EQUAL, row, column);
                break;
            case '+':
                token = new Token(TokenType::T_PLUS, row, column);
                break;
            case '-':
                token = new Token(TokenType::T_MINUS, row, column);
                break;
            case '*':
                token = new Token(TokenType::T_MUL, row, column);
                break;
            case '/': //division or multiline comment
                character = source.getNextChar();
                if (character != '*')
                    return new Token(TokenType::T_DIV, row, column);
                character = source.getNextChar();
                {
                bool commentEnd = false;
                while (!commentEnd) {
                    if (character == '*') {
                        character = source.getNextChar();
                        if (character == '/')
                            commentEnd = true;
                    }
                    character = source.getNextChar();
                }
                return new Token(TokenType::T_MULTICOMMENT, row, column);
                }
                break;
            case '^':
                token = new Token(TokenType::T_GEO_DEGREE, row, column);
                break;
            case '\'':
                character = source.getNextChar();
                if (character != '\'')
                    return new Token(TokenType::T_GEO_MINUTE, row, column);
                token = new Token(TokenType::T_GEO_SECOND, row, column);
                break;
        }
        if (token == NULL) {
            token = new Token(TokenType::T_UNKNOWN, row, column);
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
    Token * buildNumber() {
        if (isdigit(character)) {
            int value = 0;
            while (isdigit(character)) {
                value = 10 * value + character - '0';
                character = source.getNextChar();
            }
            if (character != '.')
                return new Token(TokenType::T_INT, row, column, value);

            // float
            character = source.getNextChar();
            while (isdigit(character)) {
                //value += ...;
                character = source.getNextChar();
            }
            return new Token(TokenType::T_FLOAT, row, column/*, value*/);
        }
        return NULL;
    }
    Token * buildString() {
        if (character == '"') {
            string value = "";
            character = source.getNextChar();
            while (character != '"') {
                value.push_back(character);
                character = source.getNextChar();
            }
            character = source.getNextChar();
            return new Token(TokenType::T_STRING, row, column, value);
        }
        return NULL;
    }
    Token * buildId() {
        if (isalpha(character)) {
            string value = "";
            while (isalpha(character)) {
                value.push_back(character);
                character = source.getNextChar();
            }
            for (auto itr = keywords.begin(); itr != keywords.end(); ++itr) {
                if (value == itr->first) {
                    return new Token(itr->second, row, column);
                }
            }
            return new Token(TokenType::T_ID, row, column, value);
        }
        return NULL;
    }
};

#endif // LEXER_H
