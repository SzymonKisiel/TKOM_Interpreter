// #define CATCH_CONFIG_MAIN - don't need to repeat this include in more than one cpp file
#include "catch.hpp"
#include "../lexer/StringSource.h"
#include "../lexer/Lexer.h"
#include "../parser/Parser.h"

std::unique_ptr<ExpressionNode> makeSimpleCondition(std::string variableId, TokenType comp, Value value) {
    std::unique_ptr<FactorNode> factorNode = std::make_unique<FactorNode>();
    factorNode->setId(variableId);
    std::unique_ptr<MultExpressionNode> multExpressionNode = std::make_unique<MultExpressionNode>();
    multExpressionNode->addOperand(std::move(factorNode));
    std::unique_ptr<AddExpressionNode> addExpressionNode = std::make_unique<AddExpressionNode>();
    addExpressionNode->addOperand((std::move(multExpressionNode)));

    std::unique_ptr<FactorNode> factorNode2 = std::make_unique<FactorNode>();
    factorNode2->setValue(value);
    std::unique_ptr<MultExpressionNode> multExpressionNode2 = std::make_unique<MultExpressionNode>();
    multExpressionNode2->addOperand(std::move(factorNode2));
    std::unique_ptr<AddExpressionNode> addExpressionNode2 = std::make_unique<AddExpressionNode>();
    addExpressionNode2->addOperand((std::move(multExpressionNode2)));

    std::unique_ptr<ExpressionNode> expressionNode = std::make_unique<ExpressionNode>();
    expressionNode->addOperand(std::move(addExpressionNode));
    expressionNode->addOperation(comp);
    expressionNode->addOperand(std::move(addExpressionNode2));

    return std::move(expressionNode);
}

std::unique_ptr<StatementNode> makeSimpleAssignment(std::string variableId, Value value) {
    // Expected AST
    std::unique_ptr<FactorNode> factorNode = std::make_unique<FactorNode>();
    factorNode->setValue(value);
    std::unique_ptr<MultExpressionNode> multExpressionNode = std::make_unique<MultExpressionNode>();
    multExpressionNode->addOperand(std::move(factorNode));
    std::unique_ptr<AddExpressionNode> addExpressionNode = std::make_unique<AddExpressionNode>();
    addExpressionNode->addOperand((std::move(multExpressionNode)));
    std::unique_ptr<ExpressionNode> expressionNode = std::make_unique<ExpressionNode>();
    expressionNode->addOperand(std::move(addExpressionNode));
    std::unique_ptr<AssignmentNode> assignmentNode = std::make_unique<AssignmentNode>();
    assignmentNode->setId(variableId);
    assignmentNode->setExpression(std::move(expressionNode));
    std::unique_ptr<SimpleStatementNode> simpleStatementNode = std::make_unique<SimpleStatementNode>();
    simpleStatementNode->setAssignment(std::move(assignmentNode));
    std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
    statementNode->setSimpleStatement(std::move(simpleStatementNode));

    return std::move(statementNode);
}

std::unique_ptr<StatementNode> makeSimpleDeclaration(TokenType variableType, std::string variableId, Value value) {
    // Expected AST
    std::unique_ptr<FactorNode> factorNode = std::make_unique<FactorNode>();
    factorNode->setValue(value);
    std::unique_ptr<MultExpressionNode> multExpressionNode = std::make_unique<MultExpressionNode>();
    multExpressionNode->addOperand(std::move(factorNode));
    std::unique_ptr<AddExpressionNode> addExpressionNode = std::make_unique<AddExpressionNode>();
    addExpressionNode->addOperand((std::move(multExpressionNode)));
    std::unique_ptr<ExpressionNode> expressionNode = std::make_unique<ExpressionNode>();
    expressionNode->addOperand(std::move(addExpressionNode));
    std::unique_ptr<DeclarationNode> declarationNode = std::make_unique<DeclarationNode>();
    declarationNode->setExpression(std::move(expressionNode));
    declarationNode->setId(variableId);
    declarationNode->setType(variableType);
    std::unique_ptr<SimpleStatementNode> simpleStatementNode = std::make_unique<SimpleStatementNode>();
    simpleStatementNode->setDeclaration(std::move(declarationNode));
    std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
    statementNode->setSimpleStatement(std::move(simpleStatementNode));

    return std::move(statementNode);
}

TEST_CASE("Empty program", "[Parser tests]") {
    StringSource source("");

    // Expected AST
    ProgramNode programNode;

    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    CHECK(ast->toString() == programNode.toString());
}

TEST_CASE("Variable declaration", "[Parser tests]") {
    SECTION("Int") {
        StringSource source("int x = 5;");

        // Expected AST
        ProgramNode programNode;
        programNode.addStatement(makeSimpleDeclaration(TokenType::T_TYPE_INT, "x", 5));

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("Float") {
        StringSource source("float f1 = 14.1;");

        // Expected AST
        ProgramNode programNode;
        programNode.addStatement(makeSimpleDeclaration(TokenType::T_TYPE_FLOAT, "f1", 14.1f));

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("String") {
        StringSource source("string s = \"test123\";");

        // Expected AST
        ProgramNode programNode;
        programNode.addStatement(makeSimpleDeclaration(TokenType::T_TYPE_STRING, "s", "test123"));

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("Geocoord") {
        SECTION("Geocoord 1") {
            StringSource source("geocoord gc1 = 5^ N;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEOCOORD,
                            "gc1",
                            GeographicCoordinate(5, 0, 0, Direction::N)
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geocoord 2") {
            StringSource source("geocoord gc2 = 50' S;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEOCOORD,
                            "gc2",
                            GeographicCoordinate(0, 50, 0, Direction::S)
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geocoord 3") {
            StringSource source("geocoord gc3 = 33'' W;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEOCOORD,
                            "gc3",
                            GeographicCoordinate(0, 0, 33, Direction::W)
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geocoord 4") {
            StringSource source("geocoord gc4 = 59^ 5' E;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEOCOORD,
                            "gc4",
                            GeographicCoordinate(59, 5, 0, Direction::E)
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geocoord 5") {
            StringSource source("geocoord gc5 = 110^ 30'' W;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEOCOORD,
                            "gc5",
                            GeographicCoordinate(110, 0, 30, Direction::W)
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geocoord 6") {
            StringSource source("geocoord gc6 = 40' 45'' E;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEOCOORD,
                            "gc6",
                            GeographicCoordinate(0, 40, 45, Direction::E)
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geocoord 7") {
            StringSource source("geocoord gc7 = 78^ 10' 30'' N;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEOCOORD,
                            "gc7",
                            GeographicCoordinate(78, 10, 30, Direction::N)
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geocoord exception - no specified direction") {
            StringSource source("geocoord gc11 = 1^ 2' 3'';");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
        SECTION("Geocoord exception - exceed max seconds value") {
            StringSource source("geocoord gc12 = 1^ 2' 73'' N;");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
        SECTION("Geocoord exception - exceed max minutes value") {
            StringSource source("geocoord gc13 = 1^ 82' 3'' N;");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
        SECTION("Geocoord exception - exceed max latitude value") {
            StringSource source("geocoord gc14 = 91^ N;");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
        SECTION("Geocoord exception - exceed max latitude valu") {
            StringSource source("geocoord gc15 = 90^ 20'' S;");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
        SECTION("Geocoord exception - exceed max longitude value") {
            StringSource source("geocoord gc16 = 192^ E;");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
        SECTION("Geocoord exception - exceed max longitude value") {
            StringSource source("geocoord gc17 = 180^ 9' W;");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
        SECTION("Geocoord exception - wrong units order") {
            StringSource source("geocoord gc18 = 1' 1^ N;");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
    }
    SECTION("Geo") {
        SECTION("Geo 1") {
            StringSource source("geo g1 = 60^ S  135^ W;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEO,
                            "g1",
                            GeographicPosition(
                                    GeographicCoordinate(60, 0, 0, Direction::S),
                                    GeographicCoordinate(135, 0, 0, Direction::W)
                            )
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geo 2") {
            StringSource source("geo g2 = 0^ 30' N  170^ 30' W;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEO,
                            "g2",
                            GeographicPosition(
                                    GeographicCoordinate(0, 30, 0, Direction::N),
                                    GeographicCoordinate(170, 30, 0, Direction::W)
                            )
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geo 3") {
            StringSource source("geo g3 = 10^ 20' 30'' N  95^ 40' 50'' E;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEO,
                            "g3",
                            GeographicPosition(
                                    GeographicCoordinate(10, 20, 30, Direction::N),
                                    GeographicCoordinate(95, 40, 50, Direction::E)
                            )
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geo exception - no latitude direction") {
            StringSource source("geo g11 = 60^ N  30^;");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
        SECTION("Geo exception - no longitude direction") {
            StringSource source("geo g12 = 60^  30^ W;");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
        SECTION("Geo exception - wrong coordinates order") {
            StringSource source("geo g13 = 60^ W 30^ N;");
            Lexer lexer(source);
            Parser parser(lexer);
            CHECK_THROWS_AS(parser.parse(), ParserException);
        }
    }
    SECTION("Geodist") {
        SECTION("Geodist 1") {
            StringSource source("geodist gd1 = 10^ 0' 30'', 20^ 30' 0'';");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEODIST,
                            "gd1",
                            GeographicDistance(
                                    GeographicCoordinate(10, 0, 30, Direction::NONE),
                                    GeographicCoordinate(20, 30, 0, Direction::NONE)
                            )
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geodist 2") {
            StringSource source("geodist gd2 = -90^, 180^;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEODIST,
                            "gd2",
                            GeographicDistance(
                                    GeographicCoordinate(90, 0, 0, Direction::NONE),
                                    true,
                                    GeographicCoordinate(180, 0, 0, Direction::NONE),
                                    false
                            )
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geodist 3") {
            StringSource source("geodist gd3 = 45^, -90^;");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEODIST,
                            "gd3",
                            GeographicDistance(
                                    GeographicCoordinate(45, 0, 0, Direction::NONE),
                                    false,
                                    GeographicCoordinate(90, 0, 0, Direction::NONE),
                                    true
                            )
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
        SECTION("Geodist 4") {
            StringSource source("geodist gd4 = -50^ 0' 30'', -20^ 30' 0'';");

            // Expected AST
            ProgramNode programNode;
            programNode.addStatement(
                    makeSimpleDeclaration(
                            TokenType::T_TYPE_GEODIST,
                            "gd4",
                            GeographicDistance(
                                    GeographicCoordinate(50, 0, 30, Direction::NONE),
                                    true,
                                    GeographicCoordinate(20, 30, 0, Direction::NONE),
                                    true
                            )
                    )
            );

            Lexer lexer(source);
            Parser parser(lexer);
            auto ast = parser.parse();
            CHECK(ast->toString() == programNode.toString());
        }
    }
}

TEST_CASE("Assignment", "[Parser tests]") {
    StringSource source("var = 100;");

    // Expected AST
    std::unique_ptr<FactorNode> factorNode = std::make_unique<FactorNode>();
    factorNode->setValue(100);
    std::unique_ptr<MultExpressionNode> multExpressionNode = std::make_unique<MultExpressionNode>();
    multExpressionNode->addOperand(std::move(factorNode));
    std::unique_ptr<AddExpressionNode> addExpressionNode = std::make_unique<AddExpressionNode>();
    addExpressionNode->addOperand((std::move(multExpressionNode)));
    std::unique_ptr<ExpressionNode> expressionNode = std::make_unique<ExpressionNode>();
    expressionNode->addOperand(std::move(addExpressionNode));
    std::unique_ptr<AssignmentNode> assignmentNode = std::make_unique<AssignmentNode>();
    assignmentNode->setId("var");
    assignmentNode->setExpression(std::move(expressionNode));
    std::unique_ptr<SimpleStatementNode> simpleStatementNode = std::make_unique<SimpleStatementNode>();
    simpleStatementNode->setAssignment(std::move(assignmentNode));
    std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
    statementNode->setSimpleStatement(std::move(simpleStatementNode));
    ProgramNode programNode;
    programNode.addStatement(std::move(statementNode));

    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();

    CHECK(ast->toString() == programNode.toString());
}
TEST_CASE("Function call", "[Parser tests]") {
    StringSource source("func(5, y, \"abc\");");

    // Expected AST
    // Argument 1
    std::unique_ptr<FactorNode> factorNode = std::make_unique<FactorNode>();
    factorNode->setValue(5);
    std::unique_ptr<MultExpressionNode> multExpressionNode = std::make_unique<MultExpressionNode>();
    multExpressionNode->addOperand(std::move(factorNode));
    std::unique_ptr<AddExpressionNode> addExpressionNode = std::make_unique<AddExpressionNode>();
    addExpressionNode->addOperand((std::move(multExpressionNode)));
    std::unique_ptr<ExpressionNode> expressionNode = std::make_unique<ExpressionNode>();
    expressionNode->addOperand(std::move(addExpressionNode));
    // Argument 2
    std::unique_ptr<FactorNode> factorNode2 = std::make_unique<FactorNode>();
    factorNode2->setId("y");
    std::unique_ptr<MultExpressionNode> multExpressionNode2 = std::make_unique<MultExpressionNode>();
    multExpressionNode2->addOperand(std::move(factorNode2));
    std::unique_ptr<AddExpressionNode> addExpressionNode2 = std::make_unique<AddExpressionNode>();
    addExpressionNode2->addOperand((std::move(multExpressionNode2)));
    std::unique_ptr<ExpressionNode> expressionNode2 = std::make_unique<ExpressionNode>();
    expressionNode2->addOperand(std::move(addExpressionNode2));
    // Argument 3
    std::unique_ptr<FactorNode> factorNode3 = std::make_unique<FactorNode>();
    factorNode3->setValue("abc");
    std::unique_ptr<MultExpressionNode> multExpressionNode3 = std::make_unique<MultExpressionNode>();
    multExpressionNode3->addOperand(std::move(factorNode3));
    std::unique_ptr<AddExpressionNode> addExpressionNode3 = std::make_unique<AddExpressionNode>();
    addExpressionNode3->addOperand((std::move(multExpressionNode3)));
    std::unique_ptr<ExpressionNode> expressionNode3 = std::make_unique<ExpressionNode>();
    expressionNode3->addOperand(std::move(addExpressionNode3));

    std::unique_ptr<ArgumentsNode> argumentsNode = std::make_unique<ArgumentsNode>();
    argumentsNode->addArgument(std::move(expressionNode));
    argumentsNode->addArgument(std::move(expressionNode2));
    argumentsNode->addArgument(std::move(expressionNode3));
    std::unique_ptr<FunctionCallNode> functionCallNode = std::make_unique<FunctionCallNode>();
    functionCallNode->setId("func");
    functionCallNode->setArguments(std::move(argumentsNode));
    std::unique_ptr<SimpleStatementNode> simpleStatementNode = std::make_unique<SimpleStatementNode>();
    simpleStatementNode->setFunctionCall(std::move(functionCallNode));
    std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
    statementNode->setSimpleStatement(std::move(simpleStatementNode));
    ProgramNode programNode;
    programNode.addStatement(std::move(statementNode));

    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    CHECK(ast->toString() == programNode.toString());
}
TEST_CASE("Return statement", "[Parser tests]") {
    StringSource source("return x/2;");

    // Expected AST
    std::unique_ptr<FactorNode> factorNode = std::make_unique<FactorNode>();
    factorNode->setId("x");
    std::unique_ptr<FactorNode> factorNode2 = std::make_unique<FactorNode>();
    factorNode2->setValue(2);
    std::unique_ptr<MultExpressionNode> multExpressionNode = std::make_unique<MultExpressionNode>();
    multExpressionNode->addOperand(std::move(factorNode));
    multExpressionNode->addOperation(TokenType::T_DIV);
    multExpressionNode->addOperand(std::move(factorNode2));
    std::unique_ptr<AddExpressionNode> addExpressionNode = std::make_unique<AddExpressionNode>();
    addExpressionNode->addOperand((std::move(multExpressionNode)));
    std::unique_ptr<ExpressionNode> expressionNode = std::make_unique<ExpressionNode>();
    expressionNode->addOperand(std::move(addExpressionNode));
    std::unique_ptr<ReturnStatementNode> returnStatementNode = std::make_unique<ReturnStatementNode>();
    returnStatementNode->setReturnExpression(std::move(expressionNode));
    std::unique_ptr<SimpleStatementNode> simpleStatementNode = std::make_unique<SimpleStatementNode>();
    simpleStatementNode->setReturnStatement(std::move(returnStatementNode));
    std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
    statementNode->setSimpleStatement(std::move(simpleStatementNode));
    ProgramNode programNode;
    programNode.addStatement(std::move(statementNode));

    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    CHECK(ast->toString() == programNode.toString());
}

TEST_CASE("If statement", "[Parser tests]") {
    SECTION("if") {
        StringSource source("if (x == 1) x = 2;");

        // Expected AST
        std::unique_ptr<IfStatementNode> ifStatementNode = std::make_unique<IfStatementNode>();
        ifStatementNode->setIfCondition(makeSimpleCondition("x", TokenType::T_EQUAL, 1));
        ifStatementNode->setIfStatement(makeSimpleAssignment("x", 2));

        std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
        statementNode->setIfStatement(std::move(ifStatementNode));

        ProgramNode programNode;
        programNode.addStatement(std::move(statementNode));

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("if elsif") {
        StringSource source("if (x == 1) x = 2; elsif (x <= 3) x = 4; elsif (x > 5) x = 6;");

        // Expected AST
        std::unique_ptr<IfStatementNode> ifStatementNode = std::make_unique<IfStatementNode>();
        ifStatementNode->setIfCondition(makeSimpleCondition("x", TokenType::T_EQUAL, 1));
        ifStatementNode->setIfStatement(makeSimpleAssignment("x", 2));
        ifStatementNode->addElsifCondition(makeSimpleCondition("x", TokenType::T_LESS_OR_EQUAL, 3));
        ifStatementNode->addElsifStatement(makeSimpleAssignment("x", 4));
        ifStatementNode->addElsifCondition(makeSimpleCondition("x", TokenType::T_GREATER, 5));
        ifStatementNode->addElsifStatement(makeSimpleAssignment("x", 6));

        std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
        statementNode->setIfStatement(std::move(ifStatementNode));

        ProgramNode programNode;
        programNode.addStatement(std::move(statementNode));

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("if else") {
        StringSource source("if (x == 1) x = 2; else x = 3;");

        // Expected AST
        std::unique_ptr<IfStatementNode> ifStatementNode = std::make_unique<IfStatementNode>();
        ifStatementNode->setIfCondition(makeSimpleCondition("x", TokenType::T_EQUAL, 1));
        ifStatementNode->setIfStatement(makeSimpleAssignment("x", 2));
        ifStatementNode->setElseStatement(makeSimpleAssignment("x", 3));

        std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
        statementNode->setIfStatement(std::move(ifStatementNode));

        ProgramNode programNode;
        programNode.addStatement(std::move(statementNode));

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("if elsif else") {
        StringSource source("if (x == 1) x = 2; elsif (x != 3) x = 4; else x = 5;");

        // Expected AST
        std::unique_ptr<IfStatementNode> ifStatementNode = std::make_unique<IfStatementNode>();
        ifStatementNode->setIfCondition(makeSimpleCondition("x", TokenType::T_EQUAL, 1));
        ifStatementNode->setIfStatement(makeSimpleAssignment("x", 2));
        ifStatementNode->addElsifCondition(makeSimpleCondition("x", TokenType::T_NOT_EQUAL, 3));
        ifStatementNode->addElsifStatement(makeSimpleAssignment("x", 4));
        ifStatementNode->setElseStatement(makeSimpleAssignment("x", 5));

        std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
        statementNode->setIfStatement(std::move(ifStatementNode));

        ProgramNode programNode;
        programNode.addStatement(std::move(statementNode));

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
}
TEST_CASE("While statement", "[Parser tests]") {
    StringSource source("while (x < 100) x = x + 1;");

    // Expected AST
    // Statement
    std::unique_ptr<FactorNode> factorNode = std::make_unique<FactorNode>();
    factorNode->setId("x");
    std::unique_ptr<MultExpressionNode> multExpressionNode = std::make_unique<MultExpressionNode>();
    multExpressionNode->addOperand(std::move(factorNode));

    std::unique_ptr<FactorNode> factorNode2 = std::make_unique<FactorNode>();
    factorNode2->setValue(1);
    std::unique_ptr<MultExpressionNode> multExpressionNode2 = std::make_unique<MultExpressionNode>();
    multExpressionNode2->addOperand(std::move(factorNode2));

    std::unique_ptr<AddExpressionNode> addExpressionNode3 = std::make_unique<AddExpressionNode>();
    addExpressionNode3->addOperand(std::move(multExpressionNode));
    addExpressionNode3->addOperation(TokenType::T_PLUS);
    addExpressionNode3->addOperand(std::move(multExpressionNode2));
    std::unique_ptr<ExpressionNode> expressionNode = std::make_unique<ExpressionNode>();
    expressionNode->addOperand(std::move(addExpressionNode3));
    std::unique_ptr<AssignmentNode> assignmentNode = std::make_unique<AssignmentNode>();
    assignmentNode->setId("x");
    assignmentNode->setExpression(std::move(expressionNode));
    std::unique_ptr<SimpleStatementNode> simpleStatementNode = std::make_unique<SimpleStatementNode>();
    simpleStatementNode->setAssignment(std::move(assignmentNode));
    std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
    statementNode->setSimpleStatement(std::move(simpleStatementNode));

    // If statement
    std::unique_ptr<WhileStatementNode> whileStatementNode = std::make_unique<WhileStatementNode>();
    whileStatementNode->setCondition(makeSimpleCondition("x", TokenType::T_LESS, 100));
    whileStatementNode->setStatement(std::move(statementNode));
    std::unique_ptr<StatementNode> statementNode2 = std::make_unique<StatementNode>();
    statementNode2->setWhileStatement(std::move(whileStatementNode));
    ProgramNode programNode;
    programNode.addStatement(std::move(statementNode2));

    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    CHECK(ast->toString() == programNode.toString());
}
TEST_CASE("Block statement", "[Parser tests]") {
    StringSource source("{ int x = 1; float y = 2.5; }");

    // Expected AST
    std::unique_ptr<StatementNode> statementsBlockNode = std::make_unique<StatementNode>();
    statementsBlockNode->addStatement(makeSimpleDeclaration(TokenType::T_TYPE_INT, "x", 1));
    statementsBlockNode->addStatement(makeSimpleDeclaration(TokenType::T_TYPE_FLOAT, "y", 2.5f));

    ProgramNode programNode;
    programNode.addStatement(std::move(statementsBlockNode));

    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    CHECK(ast->toString() == programNode.toString());
}

TEST_CASE("Function declaration", "[Parser tests]") {
    StringSource source("int func(int a, float b, geo c) {}");

    // Expected AST
    std::unique_ptr<ParametersNode> parametersNode = std::make_unique<ParametersNode>();
    parametersNode->addType(TokenType::T_TYPE_INT);
    parametersNode->addIdentifier("a");

    parametersNode->addType(TokenType::T_TYPE_FLOAT);
    parametersNode->addIdentifier("b");

    parametersNode->addType(TokenType::T_TYPE_GEO);
    parametersNode->addIdentifier("c");


    std::unique_ptr<FunctionNode> functionNode = std::make_unique<FunctionNode>();
    functionNode->setId("func");
    functionNode->setParameters(std::move(parametersNode));
    functionNode->setReturnType(TokenType::T_TYPE_INT);

    ProgramNode programNode;
    programNode.addFunction(std::move(functionNode));

    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    CHECK(ast->toString() == programNode.toString());
}

