#ifndef _TKOM__INTERPRETER_EXCEPTION_H
#define _TKOM__INTERPRETER_EXCEPTION_H

class Exception : public std::exception {
protected:
    std::string msg;
public:
    Exception() : msg() {}
    Exception(std::string msg) : msg(std::move(msg)) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};


#endif //_TKOM__INTERPRETER_EXCEPTION_H
