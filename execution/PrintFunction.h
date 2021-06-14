#ifndef _TKOM__INTERPRETER_PRINTFUNCTION_H
#define _TKOM__INTERPRETER_PRINTFUNCTION_H


#include <iostream>
#include "Function.h"
#include "VisitPrint.h" //debug

class PrintFunction : public Function {
    std::shared_ptr<ParametersNode> parameters;
    const std::string PRINT_VAR_ID = "var";
public:
    PrintFunction() {
        parameters = std::make_unique<ParametersNode>();
        parameters->addIdentifier(PRINT_VAR_ID);
    }
    virtual std::shared_ptr<ParametersNode> getParameters() {
        return parameters;
    };
    variant<std::monostate, string, int, float> execute(Context & context) {
        std::cout << "print: ";
        auto variables = context.getVariables();
        if (auto variable = variables.find(PRINT_VAR_ID); variable != variables.end()) {
            std::visit(VisitPrintValue(), variable->second);
        }
        cout << endl;

        return monostate();
    }
};


#endif //_TKOM__INTERPRETER_PRINTFUNCTION_H
