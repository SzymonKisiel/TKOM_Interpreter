//
// Created by kislu on 06.06.2021.
//

#ifndef _TKOM__INTERPRETER_PARSEREXCEPTION_H
#define _TKOM__INTERPRETER_PARSEREXCEPTION_H

#include "Exception.h"

class ParserException : public Exception {
    std::unique_ptr<Token> unexpectedToken;
    TokenType expectedTokenType;
public:
    ParserException(std::string msg) : Exception(std::move(msg)) {}

    ParserException(std::unique_ptr<Token> unexpectedToken, std::string msg) : Exception() {
        this->msg = std::string("Unexpected token: ")
                .append(tokenTypeToString(unexpectedToken->getType()))
                .append("\t(")
                .append(msg)
                .append(")\tRow: ")
                .append(std::to_string(unexpectedToken->getRow()))
                .append(", Col: ")
                .append(std::to_string(unexpectedToken->getColumn()));

        this->unexpectedToken = std::move(unexpectedToken);
    }

    ParserException(std::unique_ptr<Token> unexpectedToken, TokenType expectedTokenType) : Exception() {
        this->msg = std::string("Unexpected token: ")
                .append(tokenTypeToString(unexpectedToken->getType()))
                .append("\t(Expected: ")
                .append(tokenTypeToString(expectedTokenType))
                .append(")\tRow: ")
                .append(std::to_string(unexpectedToken->getRow()))
                .append(", Col: ")
                .append(std::to_string(unexpectedToken->getColumn()));

        this->unexpectedToken = std::move(unexpectedToken);
        this->expectedTokenType = expectedTokenType;
    }
};


#endif //_TKOM__INTERPRETER_PARSEREXCEPTION_H
