#include <iostream>
#include "lexer/Token.h"
#include "lexer/Source.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "lexer/FileSource.h"
#include "lexer/StringSource.h"
#include "exception/Exception.h"

using namespace std;


int main() {
//    StringSource source("int x = 10;\n"
//                               "while (x > 5) x = x - 2;");
    FileSource source("test_parser.txt");


    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    //ast->print();
    ast->execute();

    return 0;
}
