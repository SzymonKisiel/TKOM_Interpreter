#include "Lexer.h"

Lexer::Lexer(Source &s) : source(s) {
    character = source.getNextChar();
}

std::unique_ptr<Token> Lexer::getNextToken() {
    while (isspace(character)) {
        character = source.getNextChar();
    }
    skipComments();

    row = source.getRow();
    column = source.getColumn();

    if (character == EOF)
        return std::make_unique<Token>(TokenType::T_END, row, column);

    std::unique_ptr<Token> token;
    token = buildNumber();
    if (token != nullptr)
        return token;
    token = buildString();
    if (token != nullptr)
        return token;
    token = buildId();
    if (token != nullptr)
        return token;

    switch (character) {
        case '=': //==
            character = source.getNextChar();
            if (character != '=')
                return std::make_unique<Token>(TokenType::T_ASSIGN, row, column);
            token = std::make_unique<Token>(TokenType::T_EQUAL, row, column);
            break;
        case '(':
            token = std::make_unique<Token>(TokenType::T_OPEN, row, column);
            break;
        case ')':
            token = std::make_unique<Token>(TokenType::T_CLOSE, row, column);
            break;
        case '{':
            token = std::make_unique<Token>(TokenType::T_OPEN_BRACKET, row, column);
            break;
        case '}':
            token = std::make_unique<Token>(TokenType::T_CLOSE_BRACKET, row, column);
            break;
        case ';':
            token = std::make_unique<Token>(TokenType::T_SEMICOLON, row, column);
            break;
        case ',':
            token = std::make_unique<Token>(TokenType::T_COMMA, row, column);
            break;
        case '<': // <=
            character = source.getNextChar();
            if (character != '=')
                return std::make_unique<Token>(TokenType::T_LESS, row, column);
            token = std::make_unique<Token>(TokenType::T_LESS_OR_EQUAL, row, column);
            break;
        case '>': // >=
            character = source.getNextChar();
            if (character != '=')
                return std::make_unique<Token>(TokenType::T_GREATER, row, column);
            token = std::make_unique<Token>(TokenType::T_GREATER_OR_EQUAL, row, column);
            break;
        case '!': // !=
            character = source.getNextChar();
            if (character != '=')
                return std::make_unique<Token>(TokenType::T_UNKNOWN, row, column);
            token = std::make_unique<Token>(TokenType::T_NOT_EQUAL, row, column);
            break;
        case '+':
            token = std::make_unique<Token>(TokenType::T_PLUS, row, column);
            break;
        case '-':
            token = std::make_unique<Token>(TokenType::T_MINUS, row, column);
            break;
        case '*':
            token = std::make_unique<Token>(TokenType::T_MUL, row, column);
            break;
        case '/': //division or multiline comment
            character = source.getNextChar();
            if (character != '*')
                return std::make_unique<Token>(TokenType::T_DIV, row, column);
            character = source.getNextChar();
            {
                bool commentEnd = false;
                while (!commentEnd) {
                    if (character == EOF)
                        throw LexerException("Excepted comment end");
                    if (character == '*') {
                        character = source.getNextChar();
                        if (character == '/')
                            commentEnd = true;
                    }
                    character = source.getNextChar();
                }
                return std::make_unique<Token>(TokenType::T_MULTICOMMENT, row, column);
            }
            break;
        case '^':
            token = std::make_unique<Token>(TokenType::T_GEO_DEGREE, row, column);
            break;
        case '\'':
            character = source.getNextChar();
            if (character != '\'')
                return std::make_unique<Token>(TokenType::T_GEO_MINUTE, row, column);
            token = std::make_unique<Token>(TokenType::T_GEO_SECOND, row, column);
            break;
    }
    if (token == nullptr) {
        token = std::make_unique<Token>(TokenType::T_UNKNOWN, row, column);
        throw LexerException(std::move(token));
    }

    character = source.getNextChar();
    return token;
}
void Lexer::skipComments() {
    if (character == '#') {
        while (character != '\n' && character != EOF)
            character = source.getNextChar();
    }
    while (isspace(character)) {
        character = source.getNextChar();
    }
}

std::unique_ptr<Token> Lexer::buildNumber() {
    if (isdigit(character)) {
        int value = 0;
        while (isdigit(character)) {
            value = 10 * value + character - '0';
            if (value < 0)
                throw LexerException("Int overflow", row, column);
            character = source.getNextChar();
        }
        if (character != '.')
            return std::make_unique<Token>(TokenType::T_INT, row, column, value);

        // float
        float floatValue = static_cast<float>(value);
        character = source.getNextChar();
        for (int i = 1; isdigit(character); ++i) {
            floatValue += (character - '0')/pow(10,i);
            character = source.getNextChar();
        }
        return std::make_unique<Token>(TokenType::T_FLOAT, row, column , floatValue);
    }
    return nullptr;
}

std::unique_ptr<Token> Lexer::buildString() {
    if (character == '"') {
        string value = "";
        character = source.getNextChar();
        int length = 0;
        while (character != '"') {
            if (character == EOF)
                throw LexerException("Expected string end");
            if (length >= MAX_STRING_LENGTH)
                throw LexerException("String is too long");
            if (character == '\\') {
                character = source.getNextChar();
                switch (character) {
                    case 'n':
                        value.push_back('\n');
                        break;
                    case 't':
                        value.push_back('\t');
                        break;
                    case '"':
                    case '\\':
                        value.push_back(character);
                        break;
                    default:
                        //LexerException("Test");
                        throw LexerException(std::string("Unknown escape sequence \\") + character);
                }
            }
            else
                value.push_back(character);
            character = source.getNextChar();
            ++length;
        }
        character = source.getNextChar();
        return std::make_unique<Token>(TokenType::T_STRING, row, column, value);
    }
    return nullptr;
}

std::unique_ptr<Token> Lexer::buildId() {
    if (isalpha(character)) {
        string value = "";
        int length = 0;
        while (isalnum(character) || character == '_') {
            if (length >= MAX_ID_LENGTH)
                throw LexerException("Identifier is too long");
            value.push_back(character);
            character = source.getNextChar();
            ++length;
        }
        if (const auto itr = keywords.find(value); itr != keywords.end()) {
            return std::make_unique<Token>(itr->second, row, column);
        }
        return std::make_unique<Token>(TokenType::T_ID, row, column, value);
    }
    return nullptr;
}
