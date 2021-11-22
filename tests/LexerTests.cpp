// #define CATCH_CONFIG_MAIN - don't need to repeat this include in more than one cpp file
#include "catch.hpp"
#include "../lexer/StringSource.h"
#include "../lexer/Lexer.h"

TEST_CASE("While token", "[Lexer tests]") {
    StringSource source("while");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_WHILE);
}

TEST_CASE("If token", "[Lexer tests]") {
    StringSource source("if");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_IF);
}

TEST_CASE("Elsif token", "[Lexer tests]") {
    StringSource source("elsif");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_ELSIF);
}

TEST_CASE("Else token", "[Lexer tests]") {
    StringSource source("else");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_ELSE);
}

TEST_CASE("Return token", "[Lexer tests]") {
    StringSource source("return");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_RETURN);
}

TEST_CASE("Assign token", "[Lexer tests]") {
    StringSource source("=");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_ASSIGN);
}

TEST_CASE("Open token", "[Lexer tests]") {
    StringSource source("(");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_OPEN);
}

TEST_CASE("Close token", "[Lexer tests]") {
    StringSource source(")");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_CLOSE);
}

TEST_CASE("OpenBracket token", "[Lexer tests]") {
    StringSource source("{");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_OPEN_BRACKET);
}

TEST_CASE("CloseBracket token", "[Lexer tests]") {
    StringSource source("}");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_CLOSE_BRACKET);
}

TEST_CASE("Semicolon token", "[Lexer tests]") {
    StringSource source(";");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_SEMICOLON);
}

TEST_CASE("Comma token", "[Lexer tests]") {
    StringSource source(",");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_COMMA);
}

TEST_CASE("Id token", "[Lexer tests]") {
    SECTION("Id 1") {
        StringSource source("test");
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_ID);
        REQUIRE(token->getStringValue() != nullptr);
        CHECK(*token->getStringValue() == "test");
    }
    SECTION("Id 2") {
        StringSource source("test5");
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_ID);
        REQUIRE(token->getStringValue() != nullptr);
        CHECK(*token->getStringValue() == "test5");
    }
}

TEST_CASE("Less token", "[Lexer tests]") {
    StringSource source("<");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_LESS);
}

TEST_CASE("Greater token", "[Lexer tests]") {
    StringSource source(">");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_GREATER);
}

TEST_CASE("LessOrEqual token", "[Lexer tests]") {
    StringSource source("<=");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_LESS_OR_EQUAL);
}

TEST_CASE("GreaterOrEqual token", "[Lexer tests]") {
    StringSource source(">=");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_GREATER_OR_EQUAL);
}

TEST_CASE("Equal token", "[Lexer tests]") {
    StringSource source("==");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_EQUAL);
}

TEST_CASE("NotEqual token", "[Lexer tests]") {
    StringSource source("!=");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_NOT_EQUAL);
}

TEST_CASE("Plus token", "[Lexer tests]") {
    StringSource source("+");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_PLUS);
}

TEST_CASE("Minus token", "[Lexer tests]") {
    StringSource source("-");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_MINUS);
}

TEST_CASE("Or token", "[Lexer tests]") {
    StringSource source("or");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_OR);
}

TEST_CASE("Mul token", "[Lexer tests]") {
    StringSource source("*");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_MUL);
}

TEST_CASE("Div token", "[Lexer tests]") {
    StringSource source("/");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_DIV);
}

TEST_CASE("And token", "[Lexer tests]") {
    StringSource source("and");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_AND);
}

TEST_CASE("TypeVoid token", "[Lexer tests]") {
    StringSource source("void");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_TYPE_VOID);
}

TEST_CASE("TypeInt token", "[Lexer tests]") {
    StringSource source("int");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_TYPE_INT);
}

TEST_CASE("TypeFloat token", "[Lexer tests]") {
    StringSource source("float");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_TYPE_FLOAT);
}

TEST_CASE("TypeString token", "[Lexer tests]") {
    StringSource source("string");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_TYPE_STRING);
}

TEST_CASE("TypeGeo token", "[Lexer tests]") {
    StringSource source("geo");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_TYPE_GEO);
}

TEST_CASE("TypeGeocoord token", "[Lexer tests]") {
    StringSource source("geocoord");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_TYPE_GEOCOORD);
}

TEST_CASE("TypeGeodist token", "[Lexer tests]") {
    StringSource source("geodist");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_TYPE_GEODIST);
}

TEST_CASE("Int token", "[Lexer tests]") {
    SECTION("0") {
        StringSource source("0");
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_INT);
        REQUIRE(token->getIntValue() != nullptr);
        CHECK(*token->getIntValue() == 0);
    }
    SECTION("4") {
        StringSource source("4");
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_INT);
        REQUIRE(token->getIntValue() != nullptr);
        CHECK(*token->getIntValue() == 4);
    }
    SECTION("12345") {
        StringSource source("12345");
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_INT);
        REQUIRE(token->getIntValue() != nullptr);
        CHECK(*token->getIntValue() == 12345);
    }
    SECTION("Largest integer") {
        StringSource source("2147483647");
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_INT);
        REQUIRE(token->getIntValue() != nullptr);
        CHECK(*token->getIntValue() == 2147483647);
    }
    SECTION("Overflow") {
        StringSource source("2147483648");
        Lexer lexer(source);
        CHECK_THROWS_AS(lexer.getNextToken(), LexerException);
    }
}

TEST_CASE("Float token", "[Lexer tests]") {
    SECTION("Test") {
        StringSource source("5.2");
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_FLOAT);
        REQUIRE(token->getFloatValue() != nullptr);
        CHECK(*token->getFloatValue() == Approx(5.2));
    }
}

TEST_CASE("String token", "[Lexer tests]") {
    SECTION("Empty string") {
        StringSource source("\"\"");
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_STRING);
        REQUIRE(token->getStringValue() != nullptr);
        CHECK(*token->getStringValue() == "");

    }
    SECTION("Not empty string") {
        StringSource source("\"test\"");
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_STRING);
        REQUIRE(token->getStringValue() != nullptr);
        CHECK(*token->getStringValue() == "test");
    }
    SECTION("Unexpected string end") {
        StringSource source("\"");
        Lexer lexer(source);
        CHECK_THROWS_AS(lexer.getNextToken(), LexerException);
    }
    SECTION("Escape sequence \\\\") {
        StringSource source("\"\\\\\""); // "\\"
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_STRING);
        REQUIRE(token->getStringValue() != nullptr);
        CHECK(*token->getStringValue() == "\\");
    }
    SECTION("Escape sequence \\\"") {
        StringSource source("\"\\\"\""); // "\""
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_STRING);
        REQUIRE(token->getStringValue() != nullptr);
        CHECK(*token->getStringValue() == "\"");
    }
    SECTION("Escape sequence \\n") {
        StringSource source("\"\\n\""); // "\n"
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_STRING);
        REQUIRE(token->getStringValue() != nullptr);
        CHECK(*token->getStringValue() == "\n");
    }
    SECTION("Escape sequence \\t") {
        StringSource source("\"\\t\""); // "\t"
        Lexer lexer(source);
        auto token = lexer.getNextToken();
        CHECK(token->getType() == TokenType::T_STRING);
        REQUIRE(token->getStringValue() != nullptr);
        CHECK(*token->getStringValue() == "\t");
    }
    SECTION("Unknown escape sequence") {
        StringSource source("\"\\c\""); // "\c"
        Lexer lexer(source);
        CHECK_THROWS_AS(lexer.getNextToken(), LexerException);
    }
}

TEST_CASE("GeoDegree token", "[Lexer tests]") {
    StringSource source("^");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_GEO_DEGREE);
}

TEST_CASE("GeoMinute token", "[Lexer tests]") {
    StringSource source("'");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_GEO_MINUTE);
}

TEST_CASE("GeoSecond token", "[Lexer tests]") {
    StringSource source("''");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_GEO_SECOND);
}

TEST_CASE("GeoDirectionN token", "[Lexer tests]") {
    StringSource source("N");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_GEO_DIRECTION_N);
}

TEST_CASE("GeoDirectionS token", "[Lexer tests]") {
    StringSource source("S");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_GEO_DIRECTION_S);
}

TEST_CASE("GeoDirectionW token", "[Lexer tests]") {
    StringSource source("W");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_GEO_DIRECTION_W);
}

TEST_CASE("GeoDirectionE token", "[Lexer tests]") {
    StringSource source("E");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_GEO_DIRECTION_E);
}

TEST_CASE("Comment", "[Lexer tests]") {
    SECTION("Empty comment") {
        StringSource source("#");
        Lexer lexer(source);
        CHECK(lexer.getNextToken()->getType() == TokenType::T_END);
    }
    SECTION("Comment") {
        StringSource source("#abc123\n");
        Lexer lexer(source);
        CHECK(lexer.getNextToken()->getType() == TokenType::T_END);
    }
    SECTION("Comment and token in next line") {
        StringSource source("#abc123\nwhile");
        Lexer lexer(source);
        CHECK(lexer.getNextToken()->getType() == TokenType::T_WHILE);
    }
}

TEST_CASE("Multicomment token", "[Lexer tests]") {
    SECTION("Empty comment") {
        StringSource source("/**/");
        Lexer lexer(source);
        CHECK(lexer.getNextToken()->getType() == TokenType::T_MULTICOMMENT);
    }
    SECTION("Comment") {
        StringSource source("/*test\nabc\n135790\n*/");
        Lexer lexer(source);
        CHECK(lexer.getNextToken()->getType() == TokenType::T_MULTICOMMENT);
    }
    SECTION("Unexpected comment end") {
        StringSource source("/*test\n");
        Lexer lexer(source);
        CHECK_THROWS_AS(lexer.getNextToken(), LexerException);
    }
}

TEST_CASE("End token", "[Lexer tests]") {
    StringSource source("");
    Lexer lexer(source);
    CHECK(lexer.getNextToken()->getType() == TokenType::T_END);
}

TEST_CASE("Unknown token", "[Lexer tests]") {
    StringSource source("$");
    Lexer lexer(source);
    CHECK_THROWS_AS(lexer.getNextToken(), LexerException);
}