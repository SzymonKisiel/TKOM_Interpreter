#include <iostream>
#include "lexer/Token.h"
#include "lexer/Source.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "lexer/FileSource.h"
#include "lexer/StringSource.h"
#include "exception/Exception.h"

using namespace std;

//int main() {
//    StringSource testSource("print(5*5-2*5);");
//    FileSource source("test4.txt");
//
//    Lexer lexer(source);
//
//    Parser parser(lexer);
//    auto ast = parser.parse();
//    ast->print();
//    ast->execute();
//
//    return 0;
//}

int main() {
    FileSource source("test_tokens.txt");
    Lexer lexer(source);
    auto token = lexer.getNextToken();
    while (token->getType() != TokenType::T_END) {
        token->print();
        if (token->getType() == TokenType::T_STRING) {
            std::cout << "StringValue = " << token->getStringValue() << std::endl << "StringEnd" << std::endl;
        }
        token = lexer.getNextToken();
    }
    return 0;
}