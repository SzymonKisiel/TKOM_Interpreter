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

TEST_CASE("Variable declaration", "[Parser tests]") {
    SECTION("Int") {
        StringSource source("int x = 5;");

        // Expected AST
        std::unique_ptr<FactorNode> factorNode = std::make_unique<FactorNode>();
        factorNode->setValue(5);
        std::unique_ptr<MultExpressionNode> multExpressionNode = std::make_unique<MultExpressionNode>();
        multExpressionNode->addOperand(std::move(factorNode));
        std::unique_ptr<AddExpressionNode> addExpressionNode = std::make_unique<AddExpressionNode>();
        addExpressionNode->addOperand((std::move(multExpressionNode)));
        std::unique_ptr<ExpressionNode> expressionNode = std::make_unique<ExpressionNode>();
        expressionNode->addOperand(std::move(addExpressionNode));
        std::unique_ptr<DeclarationNode> declarationNode = std::make_unique<DeclarationNode>();
        declarationNode->setExpression(std::move(expressionNode));
        declarationNode->setId("x");
        declarationNode->setType(TokenType::T_TYPE_INT);
        std::unique_ptr<SimpleStatementNode> simpleStatementNode = std::make_unique<SimpleStatementNode>();
        simpleStatementNode->setDeclaration(std::move(declarationNode));
        std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
        statementNode->setSimpleStatement(std::move(simpleStatementNode));
        ProgramNode programNode;
        programNode.addStatement(std::move(statementNode));

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("Float") {
        StringSource source("geocoord gc1 = 5^ N;"); // TODO: Source

        // TODO: Expected AST
        ProgramNode programNode;

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("String") {
        StringSource source("geocoord gc1 = 5^ N;"); // TODO: Source

        // TODO: Expected AST
        ProgramNode programNode;

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("Geocoord") {
        StringSource source("geocoord gc1 = 5^ N;"); // TODO: Source

        // TODO: Expected AST
        ProgramNode programNode;

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("Geo") {
        StringSource source("geocoord gc1 = 5^ N;"); // TODO: Source

        // TODO: Expected AST
        ProgramNode programNode;

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
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

    cout << programNode.toString() << endl;

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
        // Condition
        std::unique_ptr<FactorNode> factorNode = std::make_unique<FactorNode>();
        factorNode->setId("x");
        std::unique_ptr<MultExpressionNode> multExpressionNode = std::make_unique<MultExpressionNode>();
        multExpressionNode->addOperand(std::move(factorNode));
        std::unique_ptr<AddExpressionNode> addExpressionNode = std::make_unique<AddExpressionNode>();
        addExpressionNode->addOperand((std::move(multExpressionNode)));

        std::unique_ptr<FactorNode> factorNode2 = std::make_unique<FactorNode>();
        factorNode2->setValue(1);
        std::unique_ptr<MultExpressionNode> multExpressionNode2 = std::make_unique<MultExpressionNode>();
        multExpressionNode2->addOperand(std::move(factorNode2));
        std::unique_ptr<AddExpressionNode> addExpressionNode2 = std::make_unique<AddExpressionNode>();
        addExpressionNode2->addOperand((std::move(multExpressionNode2)));

        std::unique_ptr<ExpressionNode> expressionNode = std::make_unique<ExpressionNode>();
        expressionNode->addOperand(std::move(addExpressionNode));
        expressionNode->addOperation(TokenType::T_EQUAL);
        expressionNode->addOperand(std::move(addExpressionNode2));

        // Statement
        std::unique_ptr<FactorNode> factorNode3 = std::make_unique<FactorNode>();
        factorNode3->setValue(2);
        std::unique_ptr<MultExpressionNode> multExpressionNode3 = std::make_unique<MultExpressionNode>();
        multExpressionNode3->addOperand(std::move(factorNode3));
        std::unique_ptr<AddExpressionNode> addExpressionNode3 = std::make_unique<AddExpressionNode>();
        addExpressionNode3->addOperand((std::move(multExpressionNode3)));
        std::unique_ptr<ExpressionNode> expressionNode3 = std::make_unique<ExpressionNode>();
        expressionNode3->addOperand(std::move(addExpressionNode3));
        std::unique_ptr<AssignmentNode> assignmentNode = std::make_unique<AssignmentNode>();
        assignmentNode->setId("x");
        assignmentNode->setExpression(std::move(expressionNode3));
        std::unique_ptr<SimpleStatementNode> simpleStatementNode = std::make_unique<SimpleStatementNode>();
        simpleStatementNode->setAssignment(std::move(assignmentNode));
        std::unique_ptr<StatementNode> statementNode2 = std::make_unique<StatementNode>();
        statementNode2->setSimpleStatement(std::move(simpleStatementNode));

        // If statement
        std::unique_ptr<IfStatementNode> ifStatementNode = std::make_unique<IfStatementNode>();
        ifStatementNode->setIfCondition(std::move(expressionNode));
        ifStatementNode->setIfStatement(std::move(statementNode2));
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

        // TODO: Expected AST
        ProgramNode programNode;

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("if else") {
        StringSource source("if (x == 1) x = 2; else x = 3;");

        // TODO: Expected AST
        ProgramNode programNode;

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
    SECTION("if elsif else") {
        StringSource source("if (x == 1) x = 2; elsif (x == 3) x = 4; else x = 6;");

        // TODO: Expected AST
        ProgramNode programNode;

        Lexer lexer(source);
        Parser parser(lexer);
        auto ast = parser.parse();
        CHECK(ast->toString() == programNode.toString());
    }
}
TEST_CASE("While statement", "[Parser tests]") {
    StringSource source("while (x < 100) x = x + 1;");

    // Expected AST
    // Condition
    std::unique_ptr<FactorNode> factorNode = std::make_unique<FactorNode>();
    factorNode->setId("x");
    std::unique_ptr<MultExpressionNode> multExpressionNode = std::make_unique<MultExpressionNode>();
    multExpressionNode->addOperand(std::move(factorNode));
    std::unique_ptr<AddExpressionNode> addExpressionNode = std::make_unique<AddExpressionNode>();
    addExpressionNode->addOperand((std::move(multExpressionNode)));

    std::unique_ptr<FactorNode> factorNode2 = std::make_unique<FactorNode>();
    factorNode2->setValue(100);
    std::unique_ptr<MultExpressionNode> multExpressionNode2 = std::make_unique<MultExpressionNode>();
    multExpressionNode2->addOperand(std::move(factorNode2));
    std::unique_ptr<AddExpressionNode> addExpressionNode2 = std::make_unique<AddExpressionNode>();
    addExpressionNode2->addOperand((std::move(multExpressionNode2)));

    std::unique_ptr<ExpressionNode> expressionNode = std::make_unique<ExpressionNode>();
    expressionNode->addOperand(std::move(addExpressionNode));
    expressionNode->addOperation(TokenType::T_LESS);
    expressionNode->addOperand(std::move(addExpressionNode2));

    // Statement
    std::unique_ptr<FactorNode> factorNode3 = std::make_unique<FactorNode>();
    factorNode3->setId("x");
    std::unique_ptr<MultExpressionNode> multExpressionNode3 = std::make_unique<MultExpressionNode>();
    multExpressionNode3->addOperand(std::move(factorNode3));

    std::unique_ptr<FactorNode> factorNode4 = std::make_unique<FactorNode>();
    factorNode4->setValue(1);
    std::unique_ptr<MultExpressionNode> multExpressionNode4 = std::make_unique<MultExpressionNode>();
    multExpressionNode4->addOperand(std::move(factorNode4));

    std::unique_ptr<AddExpressionNode> addExpressionNode3 = std::make_unique<AddExpressionNode>();
    addExpressionNode3->addOperand(std::move(multExpressionNode3));
    addExpressionNode3->addOperation(TokenType::T_PLUS);
    addExpressionNode3->addOperand(std::move(multExpressionNode4));
    std::unique_ptr<ExpressionNode> expressionNode3 = std::make_unique<ExpressionNode>();
    expressionNode3->addOperand(std::move(addExpressionNode3));
    std::unique_ptr<AssignmentNode> assignmentNode = std::make_unique<AssignmentNode>();
    assignmentNode->setId("x");
    assignmentNode->setExpression(std::move(expressionNode3));
    std::unique_ptr<SimpleStatementNode> simpleStatementNode = std::make_unique<SimpleStatementNode>();
    simpleStatementNode->setAssignment(std::move(assignmentNode));
    std::unique_ptr<StatementNode> statementNode2 = std::make_unique<StatementNode>();
    statementNode2->setSimpleStatement(std::move(simpleStatementNode));

    // If statement
    std::unique_ptr<WhileStatementNode> whileStatementNode = std::make_unique<WhileStatementNode>();
    whileStatementNode->setCondition(std::move(expressionNode));
    whileStatementNode->setStatement(std::move(statementNode2));
    std::unique_ptr<StatementNode> statementNode = std::make_unique<StatementNode>();
    statementNode->setWhileStatement(std::move(whileStatementNode));
    ProgramNode programNode;
    programNode.addStatement(std::move(statementNode));

    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    CHECK(ast->toString() == programNode.toString());
}
TEST_CASE("Block statement", "[Parser tests]") {
    StringSource source("{ int x = 1; float y = 2; }");

    // TODO: Expected AST
    ProgramNode programNode;

    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    CHECK(ast->toString() == programNode.toString());
}

TEST_CASE("Function declaration", "[Parser tests]") {
    StringSource source("int func(int a, float b, geo c) {}");

    // TODO: Expected AST
    ProgramNode programNode;

    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    CHECK(ast->toString() == programNode.toString());
}

