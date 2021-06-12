//
// Created by kislu on 10.06.2021.
//

#ifndef _TKOM__INTERPRETER_EXECUTIONEXCEPTION_H
#define _TKOM__INTERPRETER_EXECUTIONEXCEPTION_H

#include "Exception.h"

class ExecutionException : public Exception {
public:
    ExecutionException(std::string msg) : Exception(std::move(msg)) {}
};

#endif //_TKOM__INTERPRETER_EXECUTIONEXCEPTION_H
