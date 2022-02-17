#include "Token.h"
#include "../execution/VisitPrint.h"

std::string tokenTypeToString(TokenType tokenType) {
    return Token::tokenTypeNames[tokenType];
}

Token::Token(TokenType type, int row, int column, variant<std::monostate, string, int, float> value) :
        type(type), row(row), column(column), value(std::move(value)) {
}

Token::Token(TokenType type, int row, int column) :
        type(type), row(row), column(column), value(std::monostate{}) {
}

Token::Token(TokenType type) : type(type) {
    Token(type, 0, 0);
}

const TokenType Token::getType() {
    return this->type;
}

std::variant<std::monostate, std::string, int, float> Token::getValue() {
    return value;
}

const string* Token::getStringValue() {
    return std::get_if<string>(&this->value);
}

const int* Token::getIntValue() {
    return std::get_if<int>(&this->value);
}

const float* Token::getFloatValue() {
    return std::get_if<float>(&this->value);
}

const int Token::getRow() {
    return this->row;
}

const int Token::getColumn() {
    return this->column;
}

const bool Token::isType() {
    if (this->type >= TokenType::T_TYPE_VOID && this->type <= TokenType::T_TYPE_GEOCOORD)
        return true;
    return false;
}

const bool Token::isCompOperator() {
    if (this->type >= TokenType::T_LESS && this->type <= TokenType::T_NOT_EQUAL)
        return true;
    return false;
}

const bool Token::isMultOperator() {
    if (this->type == TokenType::T_MUL ||
        this->type == TokenType::T_DIV ||
        this->type == TokenType::T_AND)
        return true;
    return false;
}

const bool Token::isAddOperator() {
    if (this->type == TokenType::T_PLUS ||
        this->type == TokenType::T_MINUS ||
        this->type == TokenType::T_OR)
        return true;
    return false;
}

const bool Token::isOperator() {
    if (this->type >= TokenType::T_LESS && this->type <= TokenType::T_AND)
        return true;
    return false;
}

const bool Token::isGeoDirection() {
    if (this->type == TokenType::T_GEO_DIRECTION_N ||
        this->type == TokenType::T_GEO_DIRECTION_S ||
        this->type == TokenType::T_GEO_DIRECTION_W ||
        this->type == TokenType::T_GEO_DIRECTION_E
            )
        return true;
    return false;
}

const string Token::getTypeString() {
    return tokenTypeNames[this->getType()];
}

void Token::print() {
    cout << this->getRow() << '\t'
         << this->getColumn() << '\t'
         << tokenTypeNames[this->getType()] << '\t';
    if (auto val = this->getIntValue() != nullptr) {
        cout << val << '\n';
    }
    else if (auto val = this->getFloatValue() != nullptr) {
        cout << val << '\n';
    }
    else if (auto val = this->getStringValue() != nullptr) {
        cout << val << '\n';
    }
}
