#ifndef _TKOM__INTERPRETER_PARSEREXCEPTION_H
#define _TKOM__INTERPRETER_PARSEREXCEPTION_H

#include "Exception.h"
#include "GeoException.h"

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

    ParserException(GeoException e, int row, int col) : Exception() {
        this->msg = std::string(e.what())
                .append(" at row ")
                .append(std::to_string(row))
                .append(", column ")
                .append(std::to_string(col));
    }

    ParserException(std::string msg, int row, int col) : Exception() {
        this->msg = std::string(msg)
                .append(" at row ")
                .append(std::to_string(row))
                .append(", column ")
                .append(std::to_string(col));
    }
};


#endif //_TKOM__INTERPRETER_PARSEREXCEPTION_H
