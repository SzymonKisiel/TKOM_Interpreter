#ifndef _TKOM__INTERPRETER_PARSER_H
#define _TKOM__INTERPRETER_PARSER_H


#include "../lexer/Token.h"
#include "../lexer/Lexer.h"
#include <memory>

#include <iostream>
#include <ProgramNode.h>
#include <SimpleStatementNode.h>
#include <DeclarationNode.h>
#include <ArgumentsNode.h>

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
                        .append(tokenTypeToString(expectedTokenType))
                        .append("\n");
        //throw;
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
            std::unique_ptr<SimpleStatementNode> simpleStatement = parseSimpleStatement();
            if (simpleStatement != nullptr) {
                result->setSimpleStatement(std::move(simpleStatement));
                return result;
            }
        }
        //throw "Expected statement";
        return nullptr;
    }

    // if_statement     = "if" , "(" , expression, ")" , statement
    //                  , {"elsif" , "(" , expression, ")" , statement}
    //                  , ["else" , statement] ;
    std::unique_ptr<IfStatementNode> parseIf() {
        std::unique_ptr<IfStatementNode> result = std::make_unique<IfStatementNode>();
        std::unique_ptr<TestNode> node;
        std::unique_ptr<StatementNode> statement;
        std::unique_ptr<ExpressionNode> expression;

        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            unexpectedToken(TokenType::T_OPEN);
            return nullptr;
        }
        nextToken();
        expression = parseExpression();
        result->setIfCondition(std::move(expression));
        if (currentToken->getType() != TokenType::T_CLOSE) {
            unexpectedToken(TokenType::T_CLOSE);
            return nullptr;
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
                return nullptr;
            }
            nextToken();
            expression = parseExpression();
            result->addElsifCondition(std::move(expression));
            if (currentToken->getType() != TokenType::T_CLOSE) {
                unexpectedToken(TokenType::T_CLOSE);
                return nullptr;
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
        std::unique_ptr<WhileStatementNode> result = std::make_unique<WhileStatementNode>("WHILE_STATEMENT");
        std::unique_ptr<TestNode> node;
        std::unique_ptr<ExpressionNode> expression;


        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            return nullptr;
        }
        nextToken();

        expression = parseExpression();
        result->setCondition(std::move(expression));

        if (currentToken->getType() != TokenType::T_CLOSE) {
            return nullptr;
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
                unexpectedToken(TokenType::T_SEMICOLON);
            nextToken();
            return result;
        }

        std::unique_ptr<ReturnStatementNode> returnStatement = parseReturnStatement();
        if (returnStatement != nullptr) {
            result->setReturnStatement(std::move(returnStatement));
            if (currentToken->getType() != TokenType::T_SEMICOLON)
                unexpectedToken(TokenType::T_SEMICOLON);
            nextToken();
            return result;
        }

        if (currentToken->getType() != TokenType::T_ID) {
            throw; //Nie udalo sie sparsowac statement
        }
        nextToken();

        std::unique_ptr<AssignmentNode> assignment = parseAssignment();
        if (assignment != nullptr) {
            result->setAssignment(std::move(assignment));
            if (currentToken->getType() != TokenType::T_SEMICOLON)
                unexpectedToken(TokenType::T_SEMICOLON);
            nextToken();
            return result;
        }

        std::unique_ptr<FunctionCallNode> functionCall = parseFunctionCall();
        if (functionCall != nullptr) {
            result->setFunctionCall(std::move(functionCall));
            if (currentToken->getType() != TokenType::T_SEMICOLON)
                unexpectedToken(TokenType::T_SEMICOLON);
            nextToken();
            return result;
        }
        throw; //Nie udalo sie sparsowac statement
    }

    // var_declaration  = type , id, "=", expression ;
    std::unique_ptr<DeclarationNode> parseDeclaration() {
        std::unique_ptr<DeclarationNode> result = std::make_unique<DeclarationNode>();
        std::unique_ptr<ExpressionNode> expression;
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
        expression = parseExpression();
        result->setExpression(std::move(expression));
        return result;
    }

    // assignment       = id, "=", expression ;
    std::unique_ptr<AssignmentNode> parseAssignment() {
        std::unique_ptr<AssignmentNode> result = std::make_unique<AssignmentNode>();
        std::unique_ptr<ExpressionNode> expression;
        if (currentToken->getType() == TokenType::T_ASSIGN) {
            nextToken();

            expression = parseExpression();
            result->setExpression(std::move(expression));

            return result;
        }
        else
            return nullptr;
    }

    // function_call    = id ,  "(" , [arguments] , ")" ;
    std::unique_ptr<FunctionCallNode> parseFunctionCall() {
        std::unique_ptr<FunctionCallNode> result = std::make_unique<FunctionCallNode>();
        if (currentToken->getType() == TokenType::T_OPEN) {
            nextToken();
            if (currentToken->getType() == TokenType::T_CLOSE) {
                nextToken();
                return result;
            }

            std::unique_ptr<ArgumentsNode> arguments = parseArguments();
            result->setArguments(std::move(arguments));

            if (currentToken->getType() != TokenType::T_CLOSE)
                return nullptr;
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

    //expression = add_expression , {comp_operator, add_expression } ;
    std::unique_ptr<ExpressionNode> parseExpression() {
        std::unique_ptr<ExpressionNode> result = std::make_unique<ExpressionNode>();
        std::unique_ptr<AddExpresionNode> node;

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

    //add_expression = mult_expression , {add_operator, mult_expression }
    std::unique_ptr<AddExpresionNode> parseAddExpression() {
        std::unique_ptr<AddExpresionNode> result = std::make_unique<AddExpresionNode>();
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

    //mult_expression = factor , { mult_operator , factor} ;
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

    //factor = integer | id | function_call | "(" , expression , ")" ;
    std::unique_ptr<FactorNode> parseFactor() {
        std::unique_ptr<FactorNode> factor = std::make_unique<FactorNode>();
        if (!currentToken->getType() == TokenType::T_ID)
            return nullptr;
        if (!currentToken->getType() == TokenType::T_INT)
            return nullptr;
        if (!currentToken->getType() == TokenType::T_FLOAT)
            return nullptr;
        if (!currentToken->getType() == TokenType::T_STRING)
            return nullptr;
//        if (!currentToken->isExpressionPart())
//            return nullptr;
        factor->setType(currentToken->getType());
        nextToken();
        return factor;
    }
};



#endif //_TKOM__INTERPRETER_PARSER_H
