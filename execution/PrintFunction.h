#ifndef _TKOM__INTERPRETER_PRINTFUNCTION_H
#define _TKOM__INTERPRETER_PRINTFUNCTION_H


#include <iostream>
#include "Function.h"
#include "VisitPrint.h" //debug

class PrintFunction : public Function {
    void execute(Context & context) {
        std::cout << "test\n";

        //debug print
        auto variables = context.getVariables();
        for (auto variable: variables) {
            std::cout << variable.first << " = ";
            std::visit(VisitPrintValue(), variable.second);
            std::cout << std::endl;
        }
    }
};


#endif //_TKOM__INTERPRETER_PRINTFUNCTION_H
