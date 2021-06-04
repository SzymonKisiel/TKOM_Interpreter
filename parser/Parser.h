#ifndef _TKOM__INTERPRETER_PARSER_H
#define _TKOM__INTERPRETER_PARSER_H


#include "../lexer/Token.h"
#include "../lexer/Lexer.h"
#include "ast/ProgramNode.h"
#include <memory>

#include <iostream>

class Parser
{
private:
    Lexer & lexer;
    std::unique_ptr<Token> currentToken;
public:
    Parser(Lexer & lexer) : lexer(lexer) {
        nextToken();
    }

    //std::unique_ptr<Token>?
    void nextToken() {
        currentToken = std::move(lexer.getNextToken());
        while (currentToken->getType() == TokenType::T_MULTICOMMENT)
            currentToken = std::move(lexer.getNextToken());
        return; //currentToken?
    }


    void unexpectedToken(TokenType expectedTokenType = TokenType::T_UNKNOWN) {
        std::cerr << std::string("Unexpected token: ")
                        .append(tokenTypeToString(currentToken->getType()))
                        .append("\tRow: ")
                        .append(std::to_string(currentToken->getRow()))
                        .append(", Col: ")
                        .append(std::to_string(currentToken->getColumn()))
                        .append("\tExpected: ")
                        .append(tokenTypeToString(expectedTokenType));
        throw;
    }


    // program = {statement | function} ;
    std::unique_ptr<ProgramNode> parse() {
        std::unique_ptr<ProgramNode> result = std::make_unique<ProgramNode>();
        std::unique_ptr<TestNode> node;
        while (currentToken->getType() != TokenType::T_END) {
            std::unique_ptr<FunctionNode> node1 = parseFunction(); //FunctionNode
            if (node1 != nullptr) {
                result->addFunction(std::move(node1));
            }
            else {
                std::unique_ptr<StatementNode> node2 = parseStatement(); //StatementNode
                if (node2 != nullptr) {
                    result->addStatement(std::move(node2));
                }
            }
        }
        return result;
    }

    // function = type , id ,  "(" , [parameters] , ")" , "{" , {statement} , "}" ;
    // var_declaration  = type , id, "=", expression ;
    std::unique_ptr<FunctionNode> parseFunction() {
        std::unique_ptr<FunctionNode> result = std::make_unique<FunctionNode>("FUNCTION");
        std::unique_ptr<TestNode> node;

        if (!currentToken->isType()) {
            return nullptr;
        }
        result->setReturnType(currentToken->getType());
        nextToken();
        if (currentToken->getType() != TokenType::T_ID) {
            unexpectedToken(TokenType::T_ID);
            return nullptr;
        }
        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            return nullptr;
        }
        nextToken();
        node = parseParameters();
        result->addChild(std::move(node));
        if (currentToken->getType() != TokenType::T_CLOSE) {
            return nullptr;
        }
        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN_BRACKET) {
            return nullptr;
        }
        nextToken();
        while (currentToken->getType() != TokenType::T_CLOSE_BRACKET) {
            // co jesli T_END
            std::unique_ptr<StatementNode> statement = parseStatement();
            result->setStatement(std::move(statement));
        }
        nextToken();
        return result;
    }

    // statement        = if_statement | while_statement | simple_statement | "{" , {statement} , "}" ;
    std::unique_ptr<StatementNode> parseStatement() {
        std::unique_ptr<StatementNode> result = std::make_unique<StatementNode>();
        std::unique_ptr<TestNode> node = std::make_unique<TestNode>();
        if (currentToken->getType() == TokenType::T_WHILE) {
            std::unique_ptr<WhileStatementNode> whileStatement = parseWhile();
            result->setWhileStatement(std::move(whileStatement));
            return result;
            //result->addChild(node);
        }
        else if (currentToken->getType() == TokenType::T_IF) {
            std::unique_ptr<IfStatementNode> ifStatement = parseIf();
            result->setIfStatement(std::move(ifStatement));
            return result;
        }
        else if (currentToken->getType() == TokenType::T_OPEN_BRACKET) {
            nextToken();
            while (currentToken->getType() != TokenType::T_CLOSE_BRACKET) {
                std::unique_ptr<StatementNode> statementNode = parseStatement();
                result->addStatement(std::move(statementNode));
            }
            nextToken();
            return result;
        }
        else {
            node = parseSimpleStatement();
            if (node != nullptr) {
                result->addChild(std::move(node));
                return result;
            }
        }
        throw "Expected statement";
        return nullptr;
    }

    // if_statement     = "if" , "(" , expression, ")" , statement
    //                  , {"elsif" , "(" , expression, ")" , statement}
    //                  , ["else" , statement] ;
    std::unique_ptr<IfStatementNode> parseIf() {
        std::unique_ptr<IfStatementNode> result = std::make_unique<IfStatementNode>();
        std::unique_ptr<TestNode> node;
        std::unique_ptr<StatementNode> statement;

        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            return nullptr;
        }
        nextToken();
        node = parseExpression();
        result->setIfCondition(std::move(node));
        statement = parseStatement();
        result->setIfStatement(std::move(statement));

        if (currentToken->getType() != TokenType::T_ELSIF && currentToken->getType() != TokenType::T_ELSE) {
            return result;
        }
        while (currentToken->getType() == TokenType::T_ELSIF) {
            nextToken();
            if (currentToken->getType() != TokenType::T_OPEN) {
                return nullptr;
            }
            nextToken();
            node = parseExpression();
            result->addElsifCondition(std::move(node));
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
        std::unique_ptr<WhileStatementNode> result = std::make_unique<WhileStatementNode>("WHILE_STATEMENT");
        std::unique_ptr<TestNode> node;
        //result->addChild(node);

        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            return nullptr;
        }
        nextToken();

        node = parseExpression();
        result->setCondition(std::move(node));

        std::unique_ptr<StatementNode> statement = parseStatement();
        result->setStatement(std::move(statement));

        return result;

    }

    // simple_statement = (var_declaration | assignment | function_call | return_statement) , ";" ;
    std::unique_ptr<TestNode> parseSimpleStatement() {
        std::unique_ptr<TestNode> node;
        node = parseDeclaration();
        if (node == nullptr)
            node = parseAssignmentOrFunCall();
        if (node == nullptr)
            node = parseReturnStatement();
        if (currentToken->getType() != TokenType::T_SEMICOLON) {
            unexpectedToken(TokenType::T_SEMICOLON);
            return nullptr;
        }
        nextToken();
        return node;
    }

    // var_declaration  = type , id, "=", expression ;
    std::unique_ptr<TestNode> parseDeclaration() {
        std::unique_ptr<TestNode> result = std::make_unique<TestNode>("DECLARATION");
        std::unique_ptr<TestNode> node;
        if (!currentToken->isType()) {
            return nullptr;
        }
        nextToken();
        if (currentToken->getType() != TokenType::T_ID) {
            return nullptr;
        }
        nextToken();
        if (currentToken->getType() != TokenType::T_ASSIGN) {
            return nullptr;
        }
        nextToken();
        node = parseExpression();
        result->addChild(std::move(node));
        return result;
    }

    // assignment       = id, "=", expression ;
    // function_call    = id ,  "(" , [arguments] , ")" ;
    std::unique_ptr<TestNode> parseAssignmentOrFunCall() {
        std::unique_ptr<TestNode> result;
        std::unique_ptr<TestNode> node;
        if (currentToken->getType() != TokenType::T_ID) {
            return nullptr;
        }
        nextToken();
        if (currentToken->getType() == TokenType::T_ASSIGN) {
            nextToken();
            result = std::make_unique<TestNode>("ASSIGNMENT");

            node = parseExpression();
            result->addChild(std::move(node));

            return result;
        }
        else if (currentToken->getType() == TokenType::T_OPEN) {
            nextToken();
            result = std::make_unique<TestNode>("FUNCTION_CALL");

            node = parseArguments();
            result->addChild(std::move(node));
            return result;
        }
        else
            return nullptr;
    }

    // return_statement = "return" , [expression] ;
    std::unique_ptr<TestNode> parseReturnStatement() {
        std::unique_ptr<TestNode> result = std::make_unique<TestNode>("RETURN");
        std::unique_ptr<TestNode> node;
        if (currentToken->getType() != TokenType::T_RETURN) {
            return nullptr;
        }
        nextToken();
        node = parseExpression();
        result->addChild(std::move(node));
        return result;
    }

    // parameters = parameter , {"," , parameter} ;
    // parameter  = type , id ;
    std::unique_ptr<TestNode> parseParameters() {
        std::unique_ptr<TestNode> result = std::make_unique<TestNode>("PARAMETERS");
        if (!currentToken->isType())
            return nullptr;
        nextToken();
        if (currentToken->getType() != TokenType::T_ID)
            return nullptr;
        nextToken();
        if (currentToken->getType() != TokenType::T_COMMA)
            return result;

        while (currentToken->getType() == TokenType::T_COMMA) {
            nextToken();
            if (!currentToken->isType())
                return nullptr;
            nextToken();
            if (currentToken->getType() != TokenType::T_ID)
                return nullptr;
            nextToken();
        }

        return result;
    }

    // arguments  = argument , {"," , argument} ;
    // argument   = expression ;
    std::unique_ptr<TestNode> parseArguments() {
        std::unique_ptr<TestNode> result = std::make_unique<TestNode>("ARGUMENTS");
        std::unique_ptr<TestNode> node;

        node = parseExpression();
        result->addChild(std::move(node));
        while (currentToken->getType() == TokenType::T_COMMA) {
            nextToken();
            node = parseExpression();
            result->addChild(std::move(node));
        }
        return result;
    }

    // expression      = add_expression , {comp_operator, add_expression } ;
    // add_expression  = mult_expression , {add_operator, mult_expression } ;
    // mult_expression = factor , { mult_operator , factor} ;
    // factor          = integer | float | geo | string | (["-"] , id) | function_call | "(" , expression , ")"  ;
    std::unique_ptr<TestNode> parseExpression() {
        std::unique_ptr<TestNode> result = std::make_unique<TestNode>("EXPRESSION");
        std::unique_ptr<TestNode> node;

        int parenCount = 0;
        while (parenCount >= 0 && currentToken->isExpressionPart()) {
            if (currentToken->getType() == TokenType::T_CLOSE) {
                --parenCount;
                nextToken();
            }
            else if (currentToken->getType() == TokenType::T_OPEN) {
                ++parenCount;
                nextToken();
            }
            else {
                node = parseCompExpression(); //budowa expression
                result->addChild(std::move(node));
            }
        }
        return result;
    }

    //expression = add_expression , {comp_operator, add_expression } ;
    std::unique_ptr<TestNode> parseCompExpression() {
        std::unique_ptr<TestNode> result = std::make_unique<TestNode>("COMP_EXPRESSION");
        std::unique_ptr<TestNode> node;

        node = parseAddExpression();
        result->addChild(std::move(node));

        while (currentToken->isCompOperator()) {
            nextToken();

            node = parseAddExpression();
            result->addChild(std::move(node));
        }
        return result;
    }

    //add_expression = mult_expression , {add_operator, mult_expression }
    std::unique_ptr<TestNode> parseAddExpression() {
        std::unique_ptr<TestNode> result = std::make_unique<TestNode>("ADD_EXPRESSION");
        std::unique_ptr<TestNode> node;

        node = parseMultExpression();
        result->addChild(std::move(node));

        while (currentToken->isAddOperator()) {
            nextToken();

            node = parseMultExpression();
            result->addChild(std::move(node));
        }
        return result;
    }

    //mult_expression = factor , { mult_operator , factor} ;
    std::unique_ptr<TestNode> parseMultExpression() {
        std::unique_ptr<TestNode> result = std::make_unique<TestNode>("MULT_EXPRESSION");
        std::unique_ptr<TestNode> node;

        node = parseFactor();
        result->addChild(std::move(node));

        while (currentToken->isMultOperator()) {
            nextToken();

            node = parseFactor();
            result->addChild(std::move(node));
        }
        return result;
    }

    //factor = integer | id | function_call | "(" , expression , ")" ;
    std::unique_ptr<TestNode> parseFactor() {
        if (!currentToken->isExpressionPart())
            return nullptr;
        nextToken();
        return std::make_unique<TestNode>("FACTOR");
    }
};



#endif //_TKOM__INTERPRETER_PARSER_H
