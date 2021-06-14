#ifndef _TKOM__INTERPRETER_PRINTFUNCTION_H
#define _TKOM__INTERPRETER_PRINTFUNCTION_H


#include <iostream>
#include "Function.h"
#include "VisitPrint.h" //debug

class PrintFunction : public Function {
    variant<std::monostate, string, int, float> execute(Context & context) {
        std::cout << "test\n";

        //debug print
        auto variables = context.getVariables();
        for (auto variable: variables) {
            std::cout << variable.first << " = ";
            std::visit(VisitPrintValue(), variable.second);
            std::cout << std::endl;
        }
        return std::monostate();
    }
};


#endif //_TKOM__INTERPRETER_PRINTFUNCTION_H
