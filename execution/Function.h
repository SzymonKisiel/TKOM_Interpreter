#ifndef _TKOM__INTERPRETER_FUNCTION_H
#define _TKOM__INTERPRETER_FUNCTION_H

#include <memory>
#include <variant>
#include <string>
#include "Context.h"
#include "../structures/GeographicCoordinate.h"
#include "../structures/GeographicDistance.h"
#include "../structures/GeographicPosition.h"

using Value = std::variant<std::monostate, std::string, int, float,
        GeographicCoordinate, GeographicDistance, GeographicPosition>;

class Context;
class ParametersNode;

class Function {
public:
    virtual Value execute(Context & context) = 0;
    virtual std::shared_ptr<ParametersNode> getParameters() {
        return nullptr;
    };
};


#endif //_TKOM__INTERPRETER_FUNCTION_H
