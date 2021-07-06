// #define CATCH_CONFIG_MAIN - don't need to repeat this include in more than one cpp file
#include "catch.hpp"
#include "../lexer/StringSource.h"
#include "../lexer/Lexer.h"
#include "../parser/Parser.h"

#include <fstream>
#include <string>

void checkOutput(const std::string str) {
    fstream output;
    string val;
    output.open("output.txt", ios::in);
    output >> val;
    output.close();
    CHECK(val == str);
}

TEST_CASE("Print", "[Execution tests]") {
    SECTION("Int") {
        StringSource source("print(365);");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkOutput("365");
    }
    SECTION("Float") {
        StringSource source("print(3.65);");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkOutput("3.65");
    }
    SECTION("String") {
        StringSource source("print(\"test\");");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkOutput("test");
    }
}

TEST_CASE("Expressions", "[Execution tests]") {
    SECTION("Addition") {
        SECTION("int + int") {
            StringSource source("print(3 + 4);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("7");
        }
        SECTION("int + float") {
            StringSource source("print(3 + 4.2);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("7.2");
        }
        SECTION("float + int") {
            StringSource source("print(4.2 + 3);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("7.2");
        }
        SECTION("float + float") {
            StringSource source("print(3.5 + 4.2);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("7.7");
        }
        SECTION("string + string") {
            StringSource source("print(\"abc\" + \"123\");");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("abc123");
        }
        SECTION("Addition exception") {
            StringSource source("print(\"abc\" + 123);");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
    }
    SECTION("Subtraction") {
        SECTION("int - int") {
            StringSource source("print(5 - 3);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("2");
        }
        SECTION("int - float") {
            StringSource source("print(6 - 4.2);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("1.8");
        }
        SECTION("float - int") {
            StringSource source("print(6.2 - 4);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("2.2");
        }
        SECTION("float - float") {
            StringSource source("print(6.8 - 4.2);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("2.6");
        }
        SECTION("Subtraction exception") {
            StringSource source("print(\"abc\" - \"123\");");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
    }
    SECTION("Multiplication") {
        SECTION("int * int") {
            StringSource source("print(25 * 7);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("175");
        }
        SECTION("int * float") {
            StringSource source("print(7 * 12.5);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("87.5");
        }
        SECTION("float * int") {
            StringSource source("print(12.5 * 7);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("87.5");
        }
        SECTION("float * float") {
            StringSource source("print(12.5 * 7.5);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("93.75");
        }
        SECTION("Multiplication exception") {
            StringSource source("print(\"abc\" * \"123\");");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
    }
    SECTION("Division") {
        SECTION("int / int") {
            StringSource source("print(20 / 4);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("5");
        }
        SECTION("int / float") {
            StringSource source("print(10 / 0.8);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("12.5");
        }
        SECTION("float / int") {
            StringSource source("print(20.5 / 2);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("10.25");
        }
        SECTION("float / float") {
            StringSource source("print(20.5 / 2.5);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("8.2");
        }
        SECTION("Division exception") {
            StringSource source("print(\"abc\" / \"123\");");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
    }
    SECTION("Logical and") {
        SECTION("true and true") {
            StringSource source("print(1 and 1);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("1");
        }
        SECTION("true and false") {
            StringSource source("print(1 and 0);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("0");
        }
        SECTION("false and true") {
            StringSource source("print(0 and 1);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("0");
        }
        SECTION("false and false") {
            StringSource source("print(0 and 0);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("0");
        }
    }
    SECTION("Logical or") {
        SECTION("true or true") {
            StringSource source("print(1 or 1);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("1");
        }
        SECTION("true or false") {
            StringSource source("print(1 or 0);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("1");
        }
        SECTION("false or true") {
            StringSource source("print(0 or 1);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("1");
        }
        SECTION("false or false") {
            StringSource source("print(0 or 0);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("0");
        }
    }
    SECTION("Comparison <") {
        SECTION("int < int") {
            SECTION("lesser") {
                StringSource source("print(45 < 54);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(45 < 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(54 < 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
        SECTION("int < float") {
            SECTION("lesser") {
                StringSource source("print(1 < 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(1 < 1.0);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(2 < 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
        SECTION("float < int") {
            SECTION("lesser") {
                StringSource source("print(1.7 < 2);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(1.0 < 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(1.7 < 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
        SECTION("float < float") {
            SECTION("lesser") {
                StringSource source("print(0.3 < 0.6);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(0.3 < 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(0.6 < 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
    }
    SECTION("Comparison >") {
        SECTION("int > int") {
            SECTION("lesser") {
                StringSource source("print(45 > 54);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(45 > 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(54 > 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
        SECTION("int > float") {
            SECTION("lesser") {
                StringSource source("print(1 > 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(1 > 1.0);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(2 > 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
        SECTION("float > int") {
            SECTION("lesser") {
                StringSource source("print(1.7 > 2);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(1.0 > 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(1.7 > 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
        SECTION("float > float") {
            SECTION("lesser") {
                StringSource source("print(0.3 > 0.6);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(0.3 > 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(0.6 > 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
    }
    SECTION("Comparison <=") {
        SECTION("int <= int") {
            SECTION("lesser") {
                StringSource source("print(45 <= 54);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(45 <= 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(54 <= 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
        SECTION("int <= float") {
            SECTION("lesser") {
                StringSource source("print(1 <= 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(1 <= 1.0);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(2 <= 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
        SECTION("float <= int") {
            SECTION("lesser") {
                StringSource source("print(1.7 <= 2);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(1.0 <= 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(1.7 <= 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
        SECTION("float <= float") {
            SECTION("lesser") {
                StringSource source("print(0.3 <= 0.6);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(0.3 <= 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(0.6 <= 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
    }
    SECTION("Comparison >=") {
        SECTION("int >= int") {
            SECTION("lesser") {
                StringSource source("print(45 >= 54);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(45 >= 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(54 >= 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
        SECTION("int >= float") {
            SECTION("lesser") {
                StringSource source("print(1 >= 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(1 >= 1.0);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(2 >= 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
        SECTION("float >= int") {
            SECTION("lesser") {
                StringSource source("print(1.7 >= 2);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(1.0 >= 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(1.7 >= 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
        SECTION("float >= float") {
            SECTION("lesser") {
                StringSource source("print(0.3 >= 0.6);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(0.3 >= 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(0.6 >= 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
    }
    SECTION("Comparison ==") {
        SECTION("int == int") {
            SECTION("lesser") {
                StringSource source("print(45 == 54);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(45 == 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(54 == 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
        SECTION("int == float") {
            SECTION("lesser") {
                StringSource source("print(1 == 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(1 == 1.0);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(2 == 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
        SECTION("float == int") {
            SECTION("lesser") {
                StringSource source("print(1.7 == 2);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(1.0 == 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(1.7 == 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
        SECTION("float == float") {
            SECTION("lesser") {
                StringSource source("print(0.3 == 0.6);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("equal") {
                StringSource source("print(0.3 == 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("greater") {
                StringSource source("print(0.6 == 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
        }
    }
    SECTION("Comparison !=") {
        SECTION("int != int") {
            SECTION("lesser") {
                StringSource source("print(45 != 54);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(45 != 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(54 != 45);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
        SECTION("int != float") {
            SECTION("lesser") {
                StringSource source("print(1 != 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(1 != 1.0);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(2 != 1.7);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
        SECTION("float != int") {
            SECTION("lesser") {
                StringSource source("print(1.7 != 2);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(1.0 != 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(1.7 != 1);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
        SECTION("float != float") {
            SECTION("lesser") {
                StringSource source("print(0.3 != 0.6);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
            SECTION("equal") {
                StringSource source("print(0.3 != 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("0");
            }
            SECTION("greater") {
                StringSource source("print(0.6 != 0.3);");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput("1");
            }
        }
    }
}

TEST_CASE("Variables", "[Execution tests]") {
    SECTION("Integer") {
        SECTION("Declaration") {
            StringSource source("int x = 26;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("26");
        }
        SECTION("Assignment") {
            StringSource source("int x = 26;\n"
                                "x = 27;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("27");
        }
        SECTION("Declaration type exception") {
            StringSource source("float x = 26;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
        SECTION("Declaration value exception") {
            StringSource source("int x = 26.5;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
        SECTION("Assignment value exception") {
            StringSource source("int x = 26;\n"
                                "x = 26.5;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
    }
    SECTION("Float") {
        SECTION("Declaration") {
            StringSource source("float x = 3.6;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("3.6");
        }
        SECTION("Assignment") {
            StringSource source("float x = 3.6;\n"
                                "x = 2.7;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("2.7");
        }
        SECTION("Declaration type exception") {
            StringSource source("string x = 3.6;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
        SECTION("Declaration value exception") {
            StringSource source("float x = \"abc\";\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
        SECTION("Assignment value exception") {
            StringSource source("float x = 3.6;\n"
                                "x = \"abc\";\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
    }
    SECTION("String") {
        SECTION("Declaration") {
            StringSource source("string x = \"abc\";\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("abc");
        }
        SECTION("Assignment") {
            StringSource source("string x = \"abc\";\n"
                                "x = \"def\";\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("def");
        }
        SECTION("Declaration type exception") {
            StringSource source("int x = \"abc\";\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
        SECTION("Declaration value exception") {
            StringSource source("string x = 0;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
        SECTION("Assignment value exception") {
            StringSource source("float x = \"abc\";\n"
                                "x = 0;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
        }
    }
}

TEST_CASE("While", "[Execution tests]") {
    // TODO: More tests
    StringSource source(    "int i = 0;\n"
                            "while (i < 5) {\n"
                            "    print(i);\n"
                            "    i = i + 1;\n"
                            "}");
    Lexer lexer(source);
    Parser parser(lexer);
    parser.parse()->execute();

    fstream output;
    string val;
    output.open("output.txt", ios::in);
    output >> val;
    REQUIRE(val == "0");
    output >> val;
    REQUIRE(val == "1");
    output >> val;
    REQUIRE(val == "2");
    output >> val;
    REQUIRE(val == "3");
    output >> val;
    REQUIRE(val == "4");

    output.close();
}

TEST_CASE("If statement", "[Execution tests]") {
    // TODO
    SECTION("if") {
        SECTION("if true") {
            StringSource source("if (1)\n"
                                "   print(\"if\");");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("if");
        }
        SECTION("if false") {
            StringSource source("if (0)\n"
                                "   print(\"if\");");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("");
        }
    }
    SECTION("if else") {
        SECTION("if true") {
            StringSource source("if (1)\n"
                                "    print(\"if\");\n"
                                "else\n"
                                "    print(\"else\");");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("if");
        }
        SECTION("if false") {
            StringSource source("if (0)\n"
                                "    print(\"if\");\n"
                                "else\n"
                                "    print(\"else\");");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("else");
        }
    }
}

TEST_CASE("Functions", "[Execution tests]") {
    // TODO
}