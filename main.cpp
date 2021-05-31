#include <iostream>

#include "Lexer.h"
#include "Token.h"
#include "Parser.h"

using namespace std;


int main()
{
    Source source("test_parser.txt");
    Lexer lexer(source);
    Parser parser(lexer);
    parser.parse()->print();

    return 0;
}
