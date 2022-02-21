#include "Token.h"

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

const TokenType Token::getType() const {
    return this->type;
}

const std::variant<std::monostate, std::string, int, float> Token::getValue() const {
    return value;
}

const string* Token::getStringValue() const {
    return std::get_if<string>(&this->value);
}

const int* Token::getIntValue() const {
    return std::get_if<int>(&this->value);
}

const float* Token::getFloatValue() const {
    return std::get_if<float>(&this->value);
}

const int Token::getRow() const {
    return this->row;
}

const int Token::getColumn() const {
    return this->column;
}

const bool Token::isValue() const {
    if (this->getType() == TokenType::T_ID ||
        this->getType() == TokenType::T_INT ||
        this->getType() == TokenType::T_FLOAT ||
        this->getType() == TokenType::T_STRING
        )
        return true;
    return false;
}

const bool Token::isType() const {
    if (this->type >= TokenType::T_TYPE_VOID && this->type <= TokenType::T_TYPE_GEODIST)
        return true;
    return false;
}

const bool Token::isCompOperator() const {
    if (this->type >= TokenType::T_LESS && this->type <= TokenType::T_NOT_EQUAL)
        return true;
    return false;
}

const bool Token::isMultOperator() const {
    if (this->type == TokenType::T_MUL ||
        this->type == TokenType::T_DIV ||
        this->type == TokenType::T_AND)
        return true;
    return false;
}

const bool Token::isAddOperator() const {
    if (this->type == TokenType::T_PLUS ||
        this->type == TokenType::T_MINUS ||
        this->type == TokenType::T_OR)
        return true;
    return false;
}

const bool Token::isOperator() const {
    if (this->type >= TokenType::T_LESS && this->type <= TokenType::T_AND)
        return true;
    return false;
}

const bool Token::isGeoDirection() const {
    if (this->type == TokenType::T_GEO_DIRECTION_N ||
        this->type == TokenType::T_GEO_DIRECTION_S ||
        this->type == TokenType::T_GEO_DIRECTION_W ||
        this->type == TokenType::T_GEO_DIRECTION_E)
        return true;
    return false;
}

const bool Token::isGeoUnit() const {
    if (this->type == TokenType::T_GEO_DEGREE ||
        this->type == TokenType::T_GEO_MINUTE ||
        this->type == TokenType::T_GEO_SECOND)
        return true;
    return false;
}

const string Token::getTypeString() const {
    return tokenTypeNames[this->getType()];
}

struct VisitToString {
    std::string operator()(const int& x) const { return to_string(x); }
    std::string operator()(const float& x) const { return to_string(x); }
    std::string operator()(const std::string& x) const { return x; }
    std::string operator()(const auto) const { return {}; }
};

void Token::print() const {
    std::string valueString = std::visit(VisitToString(), this->getValue());
    cout << this->getRow() << '\t'
         << this->getColumn() << '\t'
         << this->getTypeString() << '\t'
         << valueString << '\n';
}
