#ifndef _TKOM__INTERPRETER_PRINTFUNCTION_H
#define _TKOM__INTERPRETER_PRINTFUNCTION_H

#include <iostream>
#include <fstream>

#include "Function.h"
#include "VisitPrint.h"

class PrintFunction : public Function {
    std::shared_ptr<ParametersNode> parameters;
    const std::string PRINT_VAR_ID = "var";
    inline static const std::string DEFAULT_OUTPUT_FILENAME = "output.txt";
    std::string output_filename;

    void print(Value & value) const {
        fstream output;
        output.open(output_filename, ios::out | ios::app);

        std::string valueString = std::visit(VisitToString(), value);
        output << valueString << '\n';
        output.close();
    }
public:
    PrintFunction(std::string filename) {
        parameters = std::make_unique<ParametersNode>();
        parameters->addIdentifier(PRINT_VAR_ID);
        output_filename = std::move(filename);

        // clear output file
        fstream output;
        output.open(output_filename, ios::out | ios::trunc);
        output.close();
    }

    PrintFunction() : PrintFunction(DEFAULT_OUTPUT_FILENAME) {}

    std::shared_ptr<ParametersNode> getParameters() const {
        return parameters;
    };

    Value execute(Context & context) const {
        auto value = context.getVariableValue(PRINT_VAR_ID);
        print(value); // print to output file
//        std::visit(VisitPrintValue(), value); // debug print
//        std::cout << '\n';
        return std::monostate();
    }
};


#endif //_TKOM__INTERPRETER_PRINTFUNCTION_H
