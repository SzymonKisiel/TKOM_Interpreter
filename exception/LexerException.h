//
// Created by kislu on 07.06.2021.
//

#ifndef _TKOM__INTERPRETER_LEXEREXCEPTION_H
#define _TKOM__INTERPRETER_LEXEREXCEPTION_H

#include "Exception.h"

class LexerException : public Exception {
    std::unique_ptr<Token> unknownToken;
public:
    LexerException(std::string msg) : Exception(std::move(msg)) {}

    LexerException(std::string msg, int row, int col) : Exception() {
        this->msg =  msg.append(" \tRow: ")
                        .append(std::to_string(row))
                        .append(", Col: ")
                        .append(std::to_string(col));
    }

    LexerException(std::unique_ptr<Token> unknownToken) : Exception() {
        this->msg = std::string("Unknown token: ")
                .append("\tRow: ")
                .append(std::to_string(unknownToken->getRow()))
                .append(", Col: ")
                .append(std::to_string(unknownToken->getColumn()));
        this->unknownToken = std::move(unknownToken);
    }
};


#endif //_TKOM__INTERPRETER_LEXEREXCEPTION_H
