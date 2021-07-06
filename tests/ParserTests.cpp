// #define CATCH_CONFIG_MAIN - don't need to repeat this include in more than one cpp file
#include "catch.hpp"
#include "../lexer/StringSource.h"
#include "../lexer/Lexer.h"
#include "../parser/Parser.h"


TEST_CASE("Empty program", "[Parser tests]") {
    StringSource source("");
    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    CHECK(ast != nullptr);
}