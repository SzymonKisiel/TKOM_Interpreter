#ifndef _TKOM__INTERPRETER_PARSER_H
#define _TKOM__INTERPRETER_PARSER_H


#include "Node.h"
#include "../lexer/Token.h"
#include "../lexer/Lexer.h"
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

    // program = {statement | function} ;
    std::unique_ptr<Node> parse() {
        std::unique_ptr<Node> result = std::make_unique<Node>("PROGRAM");
        std::unique_ptr<Node> node;
        while (currentToken->getType() != TokenType::T_END) {
            node = parseFunction();
            if (node == nullptr)
                node = parseStatement();
            result->addChild(node);
        }
        return result;
    }

    // function = type , id ,  "(" , [parameters] , ")" , "{" , {statement} , "}" ;
    // var_declaration  = type , id, "=", expression ;
    std::unique_ptr<Node> parseFunction() {
        std::unique_ptr<Node> result = std::make_unique<Node>("FUNCTION");
        std::unique_ptr<Node> node;

        if (!currentToken->isType()) {
            return nullptr;
        }
        nextToken();
        if (currentToken->getType() != TokenType::T_ID) {
            return nullptr;
        }
        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            return nullptr;
        }
        nextToken();
        node = parseParameters();
        result->addChild(node);
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
            node = parseStatement();
            result->addChild(node);
        }
        nextToken();
        return result;
    }

    // statement        = if_statement | while_statement | simple_statement | "{" , {statement} , "}" ;
    std::unique_ptr<Node> parseStatement() {
        std::unique_ptr<Node> result = std::make_unique<Node>("STATEMENT");
        std::unique_ptr<Node> node = std::make_unique<Node>();
        if (currentToken->getType() == TokenType::T_WHILE) {
            node = parseWhile();
            return node;
            //result->addChild(node);
        }
        else if (currentToken->getType() == TokenType::T_IF) {
            node = parseIf();
            return node;
        }
        else if (currentToken->getType() == TokenType::T_OPEN_BRACKET) {
            nextToken();
            while (currentToken->getType() != TokenType::T_CLOSE_BRACKET) {
                node = parseStatement();
                result->addChild(node);
            }
            nextToken();
            return result;
        }
        else {
            node = parseSimpleStatement();
            return node;
        }
        return nullptr;
    }

    // if_statement     = "if" , "(" , expression, ")" , statement
    //                  , {"elsif" , "(" , expression, ")" , statement}
    //                  , ["else" , statement] ;
    std::unique_ptr<Node> parseIf() {
        std::unique_ptr<Node> result = std::make_unique<Node>("IF");
        std::unique_ptr<Node> node;

        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            return nullptr;
        }
        nextToken();
        node = parseExpression();
        result->addChild(node);
        node = parseStatement();
        result->addChild(node);

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
            result->addChild(node);
            node = parseStatement();
            result->addChild(node);
        }
        if (currentToken->getType() == TokenType::T_ELSE) {
            nextToken();
            node = parseStatement();
            result->addChild(node);
        }
        return result;
    }

    // while_statement  = "while" , "(" , expression, ")", statement ;
    std::unique_ptr<Node> parseWhile() {
        std::unique_ptr<Node> result = std::make_unique<Node>("WHILE");
        std::unique_ptr<Node> node;
        //result->addChild(node);

        nextToken();
        if (currentToken->getType() != TokenType::T_OPEN) {
            return nullptr;
        }
        nextToken();

        node = parseExpression();
        result->addChild(node);

        node = parseStatement();
        result->addChild(node);

        return result;
    }

    // simple_statement = (var_declaration | assignment | function_call | return_statement) , ";" ;
    std::unique_ptr<Node> parseSimpleStatement() {
        std::unique_ptr<Node> node;
        node = parseDeclaration();
        if (node == nullptr)
            node = parseAssignmentOrFunCall();
        if (node == nullptr)
            node = parseReturnStatement();

        if (currentToken->getType() != TokenType::T_SEMICOLON) {
            return nullptr;
        }
        nextToken();
        return node;
    }

    // var_declaration  = type , id, "=", expression ;
    std::unique_ptr<Node> parseDeclaration() {
        std::unique_ptr<Node> result = std::make_unique<Node>("DECLARATION");
        std::unique_ptr<Node> node;
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
        result->addChild(node);
        return result;
    }

    // assignment       = id, "=", expression ;
    // function_call    = id ,  "(" , [arguments] , ")" ;
    std::unique_ptr<Node> parseAssignmentOrFunCall() {
        std::unique_ptr<Node> result;
        std::unique_ptr<Node> node;
        if (currentToken->getType() != TokenType::T_ID) {
            return nullptr;
        }
        nextToken();
        if (currentToken->getType() == TokenType::T_ASSIGN) {
            nextToken();
            result = std::make_unique<Node>("ASSIGNMENT");

            node = parseExpression();
            result->addChild(node);

            return result;
        }
        else if (currentToken->getType() == TokenType::T_OPEN) {
            nextToken();
            result = std::make_unique<Node>("FUNCTION_CALL");

            node = parseArguments();
            result->addChild(node);
            return result;
        }
        else
            return nullptr;
    }

    // return_statement = "return" , [expression] ;
    std::unique_ptr<Node> parseReturnStatement() {
        std::unique_ptr<Node> result = std::make_unique<Node>("RETURN");
        std::unique_ptr<Node> node;
        if (currentToken->getType() != TokenType::T_RETURN) {
            return nullptr;
        }
        nextToken();
        node = parseExpression();
        result->addChild(node);
        return result;
    }

    // parameters = parameter , {"," , parameter} ;
    // parameter  = type , id ;
    std::unique_ptr<Node> parseParameters() {
        std::unique_ptr<Node> result = std::make_unique<Node>("PARAMETERS");
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
    std::unique_ptr<Node> parseArguments() {
        std::unique_ptr<Node> result = std::make_unique<Node>("ARGUMENTS");
        std::unique_ptr<Node> node;

        node = parseExpression();
        result->addChild(node);
        while (currentToken->getType() == TokenType::T_COMMA) {
            nextToken();
            node = parseExpression();
            result->addChild(node);
        }
        return result;
    }

    // expression      = add_expression , {comp_operator, add_expression } ;
    // add_expression  = mult_expression , {add_operator, mult_expression } ;
    // mult_expression = factor , { mult_operator , factor} ;
    // factor          = integer | float | geo | string | (["-"] , id) | function_call | "(" , expression , ")"  ;
    std::unique_ptr<Node> parseExpression() {
        std::unique_ptr<Node> result = std::make_unique<Node>("EXPRESSION");
        std::unique_ptr<Node> node;

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
                result->addChild(node);
            }
        }
        return result;
    }

    //expression = add_expression , {comp_operator, add_expression } ;
    std::unique_ptr<Node> parseCompExpression() {
        std::unique_ptr<Node> result = std::make_unique<Node>("COMP_EXPRESSION");
        std::unique_ptr<Node> node;

        node = parseAddExpression();
        result->addChild(node);

        while (currentToken->isCompOperator()) {
            nextToken();

            node = parseAddExpression();
            result->addChild(node);
        }
        return result;
    }

    //add_expression = mult_expression , {add_operator, mult_expression }
    std::unique_ptr<Node> parseAddExpression() {
        std::unique_ptr<Node> result = std::make_unique<Node>("ADD_EXPRESSION");
        std::unique_ptr<Node> node;

        node = parseMultExpression();
        result->addChild(node);

        while (currentToken->isAddOperator()) {
            nextToken();

            node = parseMultExpression();
            result->addChild(node);
        }
        return result;
    }

    //mult_expression = factor , { mult_operator , factor} ;
    std::unique_ptr<Node> parseMultExpression() {
        std::unique_ptr<Node> result = std::make_unique<Node>("MULT_EXPRESSION");
        std::unique_ptr<Node> node;

        node = parseFactor();
        result->addChild(node);

        while (currentToken->isMultOperator()) {
            nextToken();

            node = parseFactor();
            result->addChild(node);
        }
        return result;
    }

    //factor = integer | id | function_call | "(" , expression , ")" ;
    std::unique_ptr<Node> parseFactor() {
        if (!currentToken->isExpressionPart())
            return nullptr;
        nextToken();
        return std::make_unique<Node>("FACTOR");
    }
};



#endif //_TKOM__INTERPRETER_PARSER_H
