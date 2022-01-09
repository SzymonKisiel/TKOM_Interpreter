#ifndef _TKOM__INTERPRETER_PRINTFUNCTION_H
#define _TKOM__INTERPRETER_PRINTFUNCTION_H

#include <iostream>
#include <fstream>

#include "Function.h"
#include "VisitPrint.h"

class PrintFunction : public Function {
    std::shared_ptr<ParametersNode> parameters;
    const std::string PRINT_VAR_ID = "var";
    fstream output;
    void print(Value & value) {
        output.open("output.txt", ios::out | ios::app);
        if (auto int_val = get_if<int>(&value))
            output << *int_val << '\n';
        else if (auto float_val = get_if<float>(&value))
            output << *float_val << '\n';
        else if (auto string_val = get_if<string>(&value))
            output << *string_val << '\n';
        else
            throw ExecutionException(""); // TODO: Exception message
        output.close();

    }
public:
    PrintFunction() {
        parameters = std::make_unique<ParametersNode>();
        parameters->addIdentifier(PRINT_VAR_ID);
        // clear output file
        output.open("output.txt", ios::out | ios::trunc);
        output.close();
    }

    std::shared_ptr<ParametersNode> getParameters() {
        return parameters;
    };

    Value execute(Context & context) {
        auto value = context.getVariableValue(PRINT_VAR_ID);
        print(value); // print to output file
        std::visit(VisitPrintValue(), value); // debug print
        std::cout << '\n';
        return monostate();
    }
};


#endif //_TKOM__INTERPRETER_PRINTFUNCTION_H
