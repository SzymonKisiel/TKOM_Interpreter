// #define CATCH_CONFIG_MAIN - don't need to repeat this include in more than one cpp file
#include "catch.hpp"
#include "../lexer/StringSource.h"
#include "../lexer/Lexer.h"
#include "../parser/Parser.h"

#include <fstream>
#include <string>

void checkOutput(const std::string str) {
    fstream output;
    std::string val;
    output.open("output.txt", ios::in);
    getline(output, val);
    output.close();
    CHECK(val == str);
}

void checkFloatOutput(const std::string str) {
    fstream output;
    std::string val;
    output.open("output.txt", ios::in);
    getline(output, val);
    output.close();
    float lhs = std::stof(val);
    float rhs = std::stof(str);
    CHECK(lhs == Approx(rhs));
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
        checkFloatOutput("3.65");
    }
    SECTION("String") {
        StringSource source("print(\"test\");");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkOutput("test");
    }
    SECTION("Geocoord") {
        StringSource source("print(22^ 50' 50'' E);");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkOutput(GeographicCoordinate(22, 50, 50, Direction::E).toString());
    }
    SECTION("Geo") {
        StringSource source("print(66^ 30' S, 33^ 5' 30'' W);");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkOutput(
            GeographicPosition(
                    GeographicCoordinate(66, 30, 0, Direction::S),
                    GeographicCoordinate(33, 5, 30, Direction::W)
            ).toString()
        );
    }
    SECTION("Geodist") {
        StringSource source("print(-50^ 0' 59'', 120^ 59' 0'');");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkOutput(
            GeographicDistance(
                GeographicCoordinate(50, 0, 59, Direction::NONE), true,
                GeographicCoordinate(120, 59, 0, Direction::NONE), false
            ).toString()
        );
    }
}

TEST_CASE("Negation", "[Execution tests]") {
    SECTION("Int negation") {
        StringSource source("print(-1800);");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkOutput("-1800");
    }
    SECTION("Float negation") {
        StringSource source("print(-2.6);");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkFloatOutput("-2.6");
    }
    SECTION("Geodist negation") {
        StringSource source("print(-(10^, -5^));");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkOutput(
                GeographicDistance(
                        GeographicCoordinate(10, 0, 0, Direction::NONE), true,
                        GeographicCoordinate(5, 0, 0, Direction::NONE), false
                ).toString()
        );
    }
    SECTION("String negation exception") {
        StringSource source("print(-\"test\");");
        Lexer lexer(source);
        Parser parser(lexer);
        CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
    }
    SECTION("Geocoord negation exception") {
        StringSource source("print(-10^ N);");
        Lexer lexer(source);
        Parser parser(lexer);
        CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
    }
    SECTION("Geo negation exception") {
        StringSource source("print(-10^ N 20^ W);");
        Lexer lexer(source);
        Parser parser(lexer);
        CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
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
            checkFloatOutput("7.2");
        }
        SECTION("float + int") {
            StringSource source("print(4.2 + 3);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkFloatOutput("7.2");
        }
        SECTION("float + float") {
            StringSource source("print(3.5 + 4.2);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkFloatOutput("7.7");
        }
        SECTION("string + string") {
            StringSource source("print(\"abc\" + \"123\");");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("abc123");
        }
        SECTION("geodist + geodist") {
            SECTION("Simple addition") {
                StringSource source("print(5^ 10', 10^ 5'' + 1^ 2' 3'', 4^ 5' 6'');");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput(
                        GeographicDistance(
                                GeographicCoordinate(6, 12, 3, Direction::NONE),
                                GeographicCoordinate(14, 5, 11, Direction::NONE)
                        ).toString()
                );
            }
            SECTION("Minutes/seconds overflow") {
                StringSource source("print(50^ 15' 20'', 100^ 20' 40'' + 10^ 50' 20'', 20^ 10' 30'');");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput(
                        GeographicDistance(
                                GeographicCoordinate(61, 5, 40, Direction::NONE),
                                GeographicCoordinate(120, 31, 10, Direction::NONE)
                        ).toString()
                );
            }
            SECTION("Negative geodist") {
                StringSource source("print(-50^ 15' 40'', 100^ 20' 40'' + 10^ 50' 20'', -20^ 10' 30'');");
                Lexer lexer(source);
                Parser parser(lexer);
                parser.parse()->execute();
                checkOutput(
                        GeographicDistance(
                                GeographicCoordinate(39, 25, 20, Direction::NONE), true,
                                GeographicCoordinate(80, 10, 10, Direction::NONE), false
                        ).toString()
                );
            }
            SECTION("Max vertical distance") {
                SECTION("Max vertical distance 1") {
                    StringSource source("print(100^, 0^ + 90^, 0^);");
                    Lexer lexer(source);
                    Parser parser(lexer);
                    parser.parse()->execute();
                    checkOutput(
                            GeographicDistance(
                                    GeographicCoordinate(180, 0, 0, Direction::NONE), false,
                                    GeographicCoordinate(0, 0, 0, Direction::NONE), false
                            ).toString()
                    );
                }
                SECTION("Max vertical distance 2") {
                    StringSource source("print(-179^ 30', 0^ + -30' 30'', 0^);");
                    Lexer lexer(source);
                    Parser parser(lexer);
                    parser.parse()->execute();
                    checkOutput(
                            GeographicDistance(
                                    GeographicCoordinate(180, 0, 0, Direction::NONE), true,
                                    GeographicCoordinate(0, 0, 0, Direction::NONE), false
                            ).toString()
                    );
                }
            }
            SECTION("Max horizontal distance") {
                SECTION("Max horizontal distance 1") {
                    StringSource source("print(0^, 300^+ 0^, 120^);");
                    Lexer lexer(source);
                    Parser parser(lexer);
                    parser.parse()->execute();
                    checkOutput(
                            GeographicDistance(
                                    GeographicCoordinate(0, 0, 0, Direction::NONE), false,
                                    GeographicCoordinate(60, 0, 0, Direction::NONE), false
                            ).toString()
                    );
                }
                SECTION("Max horizontal distance 2") {
                    StringSource source("print(0^, -350^ + 0^, -10^ 30' 30'');");
                    Lexer lexer(source);
                    Parser parser(lexer);
                    parser.parse()->execute();
                    checkOutput(
                            GeographicDistance(
                                    GeographicCoordinate(0, 0, 0, Direction::NONE), false,
                                    GeographicCoordinate(0, 30, 30, Direction::NONE), true
                            ).toString()
                    );
                }
            }
        }
        SECTION("geo + geodist") {
            StringSource source("print(30^ 40' N 60^ 40'' E + 50^ 30' 15'', 45^ 15' 30''); ");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput(
                    GeographicPosition(
                            GeographicCoordinate(81, 10, 15, Direction::N),
                            GeographicCoordinate(105, 16, 10, Direction::E)
                    ).toString()
            );
        }
        SECTION("Addition exception") {
            SECTION("Addition exception 1") {
                StringSource source("print(\"abc\" + 123);");
                Lexer lexer(source);
                Parser parser(lexer);
                CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
            }
            SECTION("Addition exception 2") {
                StringSource source("print(5^ N + 10^ S);");
                Lexer lexer(source);
                Parser parser(lexer);
                CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
            }
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
            checkFloatOutput("1.8");
        }
        SECTION("float - int") {
            StringSource source("print(6.2 - 4);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkFloatOutput("2.2");
        }
        SECTION("float - float") {
            StringSource source("print(6.8 - 4.2);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkFloatOutput("2.6");
        }
        SECTION("geo - geo") {
            StringSource source("print(45^ 20' 30'' N 70^ 40' 30'' E - 60^ 30' 10'' S 45^ 15' 45'' W);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput(
                    GeographicDistance(
                            GeographicCoordinate(105, 50, 40, Direction::NONE),
                            GeographicCoordinate(115, 56, 15, Direction::NONE)
                    ).toString()
            );
        }
        SECTION("geo - geodist") {
            StringSource source("print(30^ 40' N 60^ 40'' E - 50^ 30' 15'', 45^ 15' 30'');");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput(
                    GeographicPosition(
                            GeographicCoordinate(19, 50, 15, Direction::S),
                            GeographicCoordinate(14, 45, 10, Direction::E)
                    ).toString()
            );
        }
        SECTION("geodist - geodist") {
            StringSource source("print(50^ 15' 20'', 100^ 20' 40'' - 10^ 50' 20'', 20^ 10' 30'');");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput(
                    GeographicDistance(
                            GeographicCoordinate(39, 25, 0, Direction::NONE),
                            GeographicCoordinate(80, 10, 10, Direction::NONE)
                    ).toString()
            );
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
            checkFloatOutput("87.5");
        }
        SECTION("float * int") {
            StringSource source("print(12.5 * 7);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkFloatOutput("87.5");
        }
        SECTION("float * float") {
            StringSource source("print(12.5 * 7.5);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkFloatOutput("93.75");
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
            checkFloatOutput("12.5");
        }
        SECTION("float / int") {
            StringSource source("print(20.5 / 2);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkFloatOutput("10.25");
        }
        SECTION("float / float") {
            StringSource source("print(20.5 / 2.5);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkFloatOutput("8.2");
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
            checkFloatOutput("3.6");
        }
        SECTION("Assignment") {
            StringSource source("float x = 3.6;\n"
                                "x = 2.7;\n"
                                "print(x);");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkFloatOutput("2.7");
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

TEST_CASE("Execute while statement", "[Execution tests]") {
    StringSource source(    "int i = 0;\n"
                            "while (i < 5) {\n"
                            "    print(i);\n"
                            "    i = i + 1;\n"
                            "}");
    Lexer lexer(source);
    Parser parser(lexer);
    parser.parse()->execute();

    fstream output;
    std::string val;
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

TEST_CASE("Execute if statement", "[Execution tests]") {
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
    SECTION("else") {
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
    SECTION("elsif") {
        SECTION("test1") {
            StringSource source("if (0)\n"
                                "    print(\"if\");\n"
                                "elsif (0)\n"
                                "    print(\"elsif 1\");\n"
                                "elsif (1)\n"
                                "    print(\"elsif 2\");\n"
                                "elsif (1)\n"
                                "    print(\"elsif 3\");\n"
                                "else\n"
                                "    print(\"else\");");
            Lexer lexer(source);
            Parser parser(lexer);
            parser.parse()->execute();
            checkOutput("elsif 2");
        }
    }
}

TEST_CASE("Functions", "[Execution tests]") {
    SECTION("Simple function") {
        StringSource source("int add(int x, int y) {"
                            "    return x + y;"
                            "}"
                            "print(add(1, 2));"
                            "print(add(24, 24));");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();

        fstream output;
        std::string val;
        output.open("output.txt", ios::in);
        output >> val;
        CHECK(val == "3");
        output >> val;
        CHECK(val == "48");
        output.close();
    }
    SECTION("Argument type exception") {
        StringSource source("string printString(string output) {"
                            "    print(output);"
                            "    return output;"
                            "}"
                            "printString(5);");
        Lexer lexer(source);
        Parser parser(lexer);
        CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
    }
    SECTION("Return type exception") {
        StringSource source("int test() {"
                            "    return 5^ W;"
                            "}"
                            "test();");
        Lexer lexer(source);
        Parser parser(lexer);
        CHECK_THROWS_AS(parser.parse()->execute(), ExecutionException);
    }

    SECTION("Simple function 2") {
        StringSource source("string concatenate(string text1, string text2) {\n"
                            "    return text1 + \" \" + text2;\n"
                            "}"
                            "print(concatenate(\"abc\", \"def\"));");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();
        checkOutput("abc def");
    }
    SECTION("Recursive function") {
        StringSource source("int factorial(int x) {\n"
                            "    if (x <= 1)\n"
                            "        return 1;\n"
                            "    return x * factorial(x-1);\n"
                            "}"
                            "print(factorial(0));"
                            "print(factorial(2));"
                            "print(factorial(6));");
        Lexer lexer(source);
        Parser parser(lexer);
        parser.parse()->execute();

        fstream output;
        std::string val;
        output.open("output.txt", ios::in);
        output >> val;
        CHECK(val == "1");
        output >> val;
        CHECK(val == "2");
        output >> val;
        CHECK(val == "720");
        output.close();
    }
}