#ifndef _TKOM__INTERPRETER_PARSER_H
#define _TKOM__INTERPRETER_PARSER_H


#include "../lexer/Token.h"
#include "../lexer/Lexer.h"
#include "../exception/Exception.h"
#include "../exception/ParserException.h"
#include "../structures/GeographicCoordinate.h"
#include <memory>
#include <optional>
#include <iostream>
#include <queue>

#include "ast/Node.h"

class Parser
{
private:
    Lexer & lexer;
    std::unique_ptr<Token> currentToken;
    std::queue<std::unique_ptr<Token>> tokensBuffer;
public:
    Parser(Lexer & lexer) : lexer(lexer) {
        nextToken();
    }

    void nextToken() {
        if (tokensBuffer.empty()) {
            currentToken = std::move(lexer.getNextToken());
            while (currentToken->getType() == TokenType::T_MULTICOMMENT)
                currentToken = std::move(lexer.getNextToken());
        }
        else {
            currentToken = std::move(tokensBuffer.front());
            tokensBuffer.pop();
        }
    }

    void bufferToken() {
        tokensBuffer.push(std::move(currentToken));

        currentToken = std::move(lexer.getNextToken());
        while (currentToken->getType() == TokenType::T_MULTICOMMENT)
            currentToken = std::move(lexer.getNextToken());
    }

    void bufferTokenAndGetNextFromBuffer() {
        tokensBuffer.push(std::move(currentToken));
        currentToken = std::move(tokensBuffer.front());
        tokensBuffer.pop();
    }

    void clearBuffer() {
        std::queue<std::unique_ptr<Token>> emptyBuffer;
        std::swap(tokensBuffer, emptyBuffer);
    }

    void test() {
        std::cerr << std::string("Current token: ")
                .append(tokenTypeToString(currentToken->getType()))
                .append("\tRow: ")
                .append(std::to_string(currentToken->getRow()))
                .append(", Col: ")
                .append(std::to_string(currentToken->getColumn()))
                .append("\n");
    }

    // program = {statement | function} ;
    std::unique_ptr<ProgramNode> parse() {
        std::unique_ptr<ProgramNode> result = std::make_unique<ProgramNode>();
        while (currentToken->getType() != TokenType::T_END) {
            std::unique_ptr<FunctionNode> function = parseFunction();
            if (function != nullptr) {
                result->addFunction(std::move(function));
            }
            else {
                std::unique_ptr<StatementNode> statement = parseStatement();
                if (statement != nullptr) {
                    result->addStatement(std::move(statement));
                }
            }
        }
        return result;
    }

    // function = type , id ,  "(" , [parameters] , ")" , "{" , {statement} , "}" ;
    std::unique_ptr<FunctionNode> parseFunction() {
        std::unique_ptr<FunctionNode> result = std::make_unique<FunctionNode>();
        if (!currentToken->isType()) {
            return nullptr;
        }
        result->setReturnType(currentToken->getType());
        bufferToken();
        if (currentToken->getType() != TokenType::T_ID) {
            throw ParserException(std::move(currentToken), TokenType::T_ID);
        }
        result->setId(*currentToken->getStringValue()); //check if nullptr
        bufferToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            bufferTokenAndGetNextFromBuffer();
            return nullptr;
        }
        clearBuffer();
        nextToken();
        std::unique_ptr<ParametersNode> parameters = parseParameters();
        result->setParameters(std::move(parameters));
        if (currentToken->getType() != TokenType::T_CLOSE) {
            throw ParserException(std::move(currentToken), TokenType::T_CLOSE);
        }
        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN_BRACKET) {
            throw ParserException(std::move(currentToken), TokenType::T_OPEN_BRACKET);

        }
        nextToken();
        while (currentToken->getType() != TokenType::T_CLOSE_BRACKET) {
            if (currentToken->getType() == TokenType::T_END) {
                throw ParserException("Expected function end '}'");
            }
            std::unique_ptr<StatementNode> statement = parseStatement();
            result->addStatement(std::move(statement));
        }
        nextToken();
        return result;
    }

    // statement        = if_statement | while_statement | simple_statement | "{" , {statement} , "}" ;
    std::unique_ptr<StatementNode> parseStatement() {
        std::unique_ptr<StatementNode> result = std::make_unique<StatementNode>();
        if (currentToken->getType() == TokenType::T_WHILE) {
            std::unique_ptr<WhileStatementNode> whileStatement = parseWhile();
            result->setWhileStatement(std::move(whileStatement));
            return result;
        }
        else if (currentToken->getType() == TokenType::T_IF) {
            std::unique_ptr<IfStatementNode> ifStatement = parseIf();
            result->setIfStatement(std::move(ifStatement));
            return result;
        }
        else if (currentToken->getType() == TokenType::T_OPEN_BRACKET) {
            nextToken();
            while (currentToken->getType() != TokenType::T_CLOSE_BRACKET) {
                if (currentToken->getType() == TokenType::T_END) {
                    throw ParserException("Expected block end '}'");
                }
                std::unique_ptr<StatementNode> statementNode = parseStatement();
                result->addStatement(std::move(statementNode));
            }
            nextToken();
            return result;
        }
        else {
            std::unique_ptr<SimpleStatementNode> simpleStatement = parseSimpleStatement();
            if (simpleStatement != nullptr) {
                result->setSimpleStatement(std::move(simpleStatement));
                return result;
            }
        }
        throw ParserException(std::move(currentToken), "Expected statement");
    }

    // if_statement     = "if" , "(" , expression, ")" , statement
    //                  , {"elsif" , "(" , expression, ")" , statement}
    //                  , ["else" , statement] ;
    std::unique_ptr<IfStatementNode> parseIf() {
        std::unique_ptr<IfStatementNode> result = std::make_unique<IfStatementNode>();
        std::unique_ptr<StatementNode> statement;
        std::unique_ptr<ExpressionNode> expression;

        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            throw ParserException(std::move(currentToken), TokenType::T_OPEN);
        }
        nextToken();
        expression = parseExpression();
        result->setIfCondition(std::move(expression));
        if (currentToken->getType() != TokenType::T_CLOSE) {
            throw ParserException(std::move(currentToken), TokenType::T_CLOSE);
        }
        nextToken();
        statement = parseStatement();
        result->setIfStatement(std::move(statement));

        if (currentToken->getType() != TokenType::T_ELSIF && currentToken->getType() != TokenType::T_ELSE) {
            return result;
        }
        while (currentToken->getType() == TokenType::T_ELSIF) {
            nextToken();
            if (currentToken->getType() != TokenType::T_OPEN) {
                throw ParserException(std::move(currentToken), TokenType::T_OPEN);
            }
            nextToken();
            expression = parseExpression();
            result->addElsifCondition(std::move(expression));
            if (currentToken->getType() != TokenType::T_CLOSE) {
                throw ParserException(std::move(currentToken), TokenType::T_CLOSE);
            }
            nextToken();
            statement = parseStatement();
            result->addElsifStatement(std::move(statement));
        }
        if (currentToken->getType() == TokenType::T_ELSE) {
            nextToken();
            statement = parseStatement();
            result->setElseStatement(std::move(statement));
        }
        return result;
    }

    // while_statement  = "while" , "(" , expression, ")", statement ;
    std::unique_ptr<WhileStatementNode> parseWhile() {
        std::unique_ptr<WhileStatementNode> result = std::make_unique<WhileStatementNode>();
        std::unique_ptr<ExpressionNode> expression;


        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            throw ParserException(std::move(currentToken), TokenType::T_OPEN);
        }
        nextToken();

        expression = parseExpression();
        result->setCondition(std::move(expression));

        if (currentToken->getType() != TokenType::T_CLOSE) {
            throw ParserException(std::move(currentToken), TokenType::T_CLOSE);
        }
        nextToken();

        std::unique_ptr<StatementNode> statement = parseStatement();
        result->setStatement(std::move(statement));

        return result;
    }

    // simple_statement = (var_declaration | assignment | function_call | return_statement) , ";" ;
    std::unique_ptr<SimpleStatementNode> parseSimpleStatement() {
        std::unique_ptr<SimpleStatementNode> result = std::make_unique<SimpleStatementNode>();

        std::unique_ptr<DeclarationNode> declaration = parseDeclaration();
        if (declaration != nullptr) {
            result->setDeclaration(std::move(declaration));
            if (currentToken->getType() != TokenType::T_SEMICOLON)
                throw ParserException(std::move(currentToken), TokenType::T_SEMICOLON);
            nextToken();
            return result;
        }

        std::unique_ptr<ReturnStatementNode> returnStatement = parseReturnStatement();
        if (returnStatement != nullptr) {
            result->setReturnStatement(std::move(returnStatement));
            if (currentToken->getType() != TokenType::T_SEMICOLON)
                throw ParserException(std::move(currentToken), TokenType::T_SEMICOLON);
            nextToken();
            return result;
        }

        if (currentToken->getType() != TokenType::T_ID) {
            return nullptr;
        }
        std::string tempId = *currentToken->getStringValue(); //check if nullptr
        nextToken();

        std::unique_ptr<AssignmentNode> assignment = parseAssignment(tempId);
        if (assignment != nullptr) {
            result->setAssignment(std::move(assignment));
            if (currentToken->getType() != TokenType::T_SEMICOLON)
                throw ParserException(std::move(currentToken), TokenType::T_SEMICOLON);
            nextToken();
            return result;
        }

        std::unique_ptr<FunctionCallNode> functionCall = parseFunctionCall(tempId);
        if (functionCall != nullptr) {
            result->setFunctionCall(std::move(functionCall));
            if (currentToken->getType() != TokenType::T_SEMICOLON)
                throw ParserException(std::move(currentToken), TokenType::T_SEMICOLON);
            nextToken();
            return result;
        }
        return nullptr;
    }

    // var_declaration  = type , id, "=", expression ;
    std::unique_ptr<DeclarationNode> parseDeclaration() {
        std::unique_ptr<DeclarationNode> result = std::make_unique<DeclarationNode>();
        if (!currentToken->isType()) {
            return nullptr;
        }
        result->setType(currentToken->getType());
        nextToken();
        if (currentToken->getType() != TokenType::T_ID) {
            throw ParserException(std::move(currentToken), TokenType::T_ID);
        }
        result->setId(*currentToken->getStringValue()); //check if nullptr
        nextToken();
        if (currentToken->getType() != TokenType::T_ASSIGN) {
            throw ParserException(std::move(currentToken), TokenType::T_ASSIGN);
        }
        nextToken();
        std::unique_ptr<ExpressionNode> expression = parseExpression();
        result->setExpression(std::move(expression));
        return result;
    }

    // assignment       = id, "=", expression ;
    std::unique_ptr<AssignmentNode> parseAssignment(std::string id) {
        std::unique_ptr<AssignmentNode> result = std::make_unique<AssignmentNode>();
        if (currentToken->getType() == TokenType::T_ASSIGN) {
            nextToken();

            std::unique_ptr<ExpressionNode> expression = parseExpression();
            result->setExpression(std::move(expression));
            result->setId(id);
            return result;
        }
        else
            return nullptr;
    }

    // function_call    = id ,  "(" , [arguments] , ")" ;
    std::unique_ptr<FunctionCallNode> parseFunctionCall(std::string id) {
        std::unique_ptr<FunctionCallNode> result = std::make_unique<FunctionCallNode>();
        result->setId(id);
        if (currentToken->getType() == TokenType::T_OPEN) {
            nextToken();
            if (currentToken->getType() == TokenType::T_CLOSE) {
                nextToken();
                return result;
            }
            std::unique_ptr<ArgumentsNode> arguments = parseArguments();
            result->setArguments(std::move(arguments));
            if (currentToken->getType() != TokenType::T_CLOSE) {
                throw ParserException(std::move(currentToken), TokenType::T_CLOSE);
            }
            nextToken();
            return result;
        }
        else
            return nullptr;
    }

    // return_statement = "return" , [expression] ;
    std::unique_ptr<ReturnStatementNode> parseReturnStatement() {
        std::unique_ptr<ReturnStatementNode> result = std::make_unique<ReturnStatementNode>();
        std::unique_ptr<ExpressionNode> expression;
        if (currentToken->getType() != TokenType::T_RETURN) {
            return nullptr;
        }
        nextToken();
        expression = parseExpression();
        result->setReturnExpression(std::move(expression));
        return result;
    }

    // parameters = parameter , {"," , parameter} ;
    // parameter  = type , id ;
    std::unique_ptr<ParametersNode> parseParameters() {
        std::unique_ptr<ParametersNode> result = std::make_unique<ParametersNode>();
        if (!currentToken->isType())
            return nullptr;
        result->addType(currentToken->getType());
        nextToken();
        if (currentToken->getType() != TokenType::T_ID)
            return nullptr;
        result->addIdentifier(*currentToken->getStringValue()); //check if nullptr
        nextToken();
        if (currentToken->getType() != TokenType::T_COMMA)
            return result;

        while (currentToken->getType() == TokenType::T_COMMA) {
            nextToken();
            if (!currentToken->isType())
                throw ParserException(std::move(currentToken), "Expected type");
            result->addType(currentToken->getType());
            nextToken();
            if (currentToken->getType() != TokenType::T_ID)
                throw ParserException(std::move(currentToken), TokenType::T_ID);
            result->addIdentifier(*currentToken->getStringValue()); //check if nullptr
            nextToken();
        }
        return result;
    }

    // arguments  = argument , {"," , argument} ;
    // argument   = expression ;
    std::unique_ptr<ArgumentsNode> parseArguments() {
        std::unique_ptr<ArgumentsNode> result = std::make_unique<ArgumentsNode>();
        std::unique_ptr<ExpressionNode> expression;

        expression = parseExpression();
        result->addArgument(std::move(expression));
        while (currentToken->getType() == TokenType::T_COMMA) {
            nextToken();
            expression = parseExpression();
            result->addArgument(std::move(expression));
        }
        return result;
    }

    // expression = add_expression , {comp_operator, add_expression } ;
    std::unique_ptr<ExpressionNode> parseExpression() {
        std::unique_ptr<ExpressionNode> result = std::make_unique<ExpressionNode>();
        std::unique_ptr<AddExpressionNode> node;

        node = parseAddExpression();
        result->addOperand(std::move(node));

        while (currentToken->isCompOperator()) {
            result->addOperation(currentToken->getType());
            nextToken();

            node = parseAddExpression();
            result->addOperand(std::move(node));
        }
        return result;
    }

    // add_expression = mult_expression , {add_operator, mult_expression }
    std::unique_ptr<AddExpressionNode> parseAddExpression() {
        std::unique_ptr<AddExpressionNode> result = std::make_unique<AddExpressionNode>();
        std::unique_ptr<MultExpressionNode> node;

        node = parseMultExpression();
        result->addOperand(std::move(node));

        while (currentToken->isAddOperator()) {
            result->addOperation(currentToken->getType());
            nextToken();

            node = parseMultExpression();
            result->addOperand(std::move(node));
        }
        return result;
    }

    // mult_expression = factor , { mult_operator , factor} ;
    std::unique_ptr<MultExpressionNode> parseMultExpression() {
        std::unique_ptr<MultExpressionNode> result = std::make_unique<MultExpressionNode>();
        std::unique_ptr<FactorNode> node;

        node = parseFactor();
        result->addOperand(std::move(node));

        while (currentToken->isMultOperator()) {
            result->addOperation(currentToken->getType());
            nextToken();

            node = parseFactor();
            result->addOperand(std::move(node));
        }
        return result;
    }

    // factor          = integer | float | geo | string | (["-"] , id) | function_call | "(" , expression , ")"  ;
    std::unique_ptr<FactorNode> parseFactor() {
        bool isXNegative = false, isYNegative = false; // for geodist
        bool parsingGeoDist = false; // for geodist (to make sure negation is not used for geo and geocoord types)
        std::unique_ptr<FactorNode> factor = std::make_unique<FactorNode>();
        if (currentToken->getType() == TokenType::T_MINUS) {
            isXNegative = true;
            parsingGeoDist = true;

            factor->setNegative();
            nextToken();
        }
        if (currentToken->getType() == TokenType::T_OPEN) {
            nextToken();
            auto expression = parseExpression();
            factor->setExpression(std::move(expression));
            if (currentToken->getType() != TokenType::T_CLOSE)
                throw ParserException(std::move(currentToken), TokenType::T_CLOSE);
            nextToken();
            return factor;
        }
        if (!currentToken->isValue())
            throw ParserException(std::move(currentToken), "Expected expression");
        if (currentToken->getType() == TokenType::T_ID) {
            std::string id = *currentToken->getStringValue(); //check if nullptr
            nextToken();
            auto functionCall = parseFunctionCall(id);
            if (functionCall == nullptr) {
                factor->setId(id);
            }
            else {
                factor->setFunction(std::move(functionCall));
            }
            return factor;
        }
        // Geographic types parsing
        int geoParseRow = currentToken->getRow();
        int geoParseCol = currentToken->getColumn();
        if (auto geoCoord = parseCoordinate()) {
            if (currentToken->getType() == TokenType::T_COMMA)
                nextToken();
            if (currentToken->getType() == TokenType::T_MINUS) {
                isYNegative = true;
                parsingGeoDist = true;
                nextToken();
            }
            if (auto geoCoord2 = parseCoordinate()) {
                // GeographicPosition
                if (geoCoord->hasDirection() || geoCoord2->hasDirection()) {
                    if (parsingGeoDist)
                        throw ParserException("Can not negate GeographicCoordinate", geoParseRow, geoParseCol);
                    GeographicPosition geoPos = GeographicPosition(*geoCoord, *geoCoord2);
                    try {
                        geoPos.validate();
                    }
                    catch (GeoException e) {
                        throw ParserException(e, geoParseRow, geoParseCol);
                    }
                    factor->setValue(geoPos);
                }
                // GeographicDistance
                else {
                    GeographicDistance geoDist = GeographicDistance(*geoCoord, isXNegative,
                                                                    *geoCoord2, isYNegative);
                    try {
                        geoDist.validate();
                    }
                    catch (GeoException e) {
                        throw ParserException(e, geoParseRow, geoParseCol);
                    }
                    factor->setValue(geoDist);
                }
            }
            // GeographicCoordinate
            else {
                if (parsingGeoDist)
                    throw ParserException("Can not negate GeographicCoordinate", geoParseRow, geoParseCol);
                try {
                    geoCoord->validate();
                }
                catch (GeoException e) {
                    throw ParserException(e, geoParseRow, geoParseCol);
                }
                factor->setValue(*geoCoord);
            }
            return factor;
        }
        factor->setValue(std::visit([](auto v) -> Value { return v; }, currentToken->getValue())); //convert to other variant
        nextToken();
        return factor;
    }

    std::optional<GeographicCoordinate> parseCoordinate() {
        std::optional<GeographicCoordinate> result;
        if (currentToken->getType() != TokenType::T_INT) {
            return result;
        }
        std::variant<std::monostate, std::string, int, float> value = currentToken->getValue();
        bufferToken();
        if (!currentToken->isGeoUnit()) {
            bufferTokenAndGetNextFromBuffer();
            return result;
        }
        clearBuffer();

        result = GeographicCoordinate();
        if (currentToken->getType() == TokenType::T_GEO_DEGREE) {
            result->setDegree(std::visit(VisitGetInt(), value));
            nextToken();
            if (currentToken->getType() == TokenType::T_INT) {
                value = currentToken->getValue();
                nextToken();
            }
        }
        if (currentToken->getType() == TokenType::T_GEO_MINUTE) {
            result->setMinute(std::visit(VisitGetInt(), value));
            nextToken();
            if (currentToken->getType() == TokenType::T_INT) {
                value = currentToken->getValue();
                nextToken();
            }
        }
        if (currentToken->getType() == TokenType::T_GEO_SECOND) {
            result->setSecond(std::visit(VisitGetInt(), value));
            nextToken();
        }
        if (currentToken->isGeoDirection()) {
            result->setDirection(currentToken->getType());
            nextToken();
        }
        return result;
    }
    struct VisitGetInt {
        int operator()(int& x)  { return x; }
        int operator()(auto&)   { throw ParserException("Wrong value type, expected int"); }
    };
};



#endif //_TKOM__INTERPRETER_PARSER_H
