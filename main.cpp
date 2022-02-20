#include "lexer/Lexer.h"
#include "lexer/FileSource.h"
#include "lexer/StringSource.h"
#include "parser/Parser.h"

using namespace std;

int main() {
    FileSource source("input.txt");
    Lexer lexer(source);
    Parser parser(lexer);
    auto ast = parser.parse();
    ast->execute();

    return 0;
}