#include <iostream>
#include "lexer/Token.h"
#include "lexer/Source.h"
#include "lexer/Lexer.h"
#include "lexer/FileSource.h"
#include "lexer/StringSource.h"
#include "exception/Exception.h"

using namespace std;


int main() {
    FileSource source("test_lexer.txt");
    Lexer lexer(source);
    auto token = lexer.getNextToken();
    while (token->getType() != TokenType::T_END) {
        token->print();
        token = lexer.getNextToken();
    }
    return 0;
}