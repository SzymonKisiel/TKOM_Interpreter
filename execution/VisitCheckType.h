#ifndef _TKOM__INTERPRETER_VISITCHECKTYPE_H
#define _TKOM__INTERPRETER_VISITCHECKTYPE_H

#include "../lexer/Token.h"

struct VisitCheckType {
    bool operator()(const int&, const TokenType& type) const { return type == TokenType::T_TYPE_INT; }
    bool operator()(const float&, const TokenType& type) const { return type == TokenType::T_TYPE_FLOAT; }
    bool operator()(const std::string&, const TokenType& type) const { return type == TokenType::T_TYPE_STRING; }
    bool operator()(const GeographicCoordinate&, const TokenType& type) const { return type == TokenType::T_TYPE_GEOCOORD; }
    bool operator()(const GeographicPosition&, const TokenType& type) const { return type == TokenType::T_TYPE_GEO; }
    bool operator()(const GeographicDistance&, const TokenType& type) const { return type == TokenType::T_TYPE_GEODIST; }
    bool operator()(const auto&, const auto&) const { return false; }
};

struct VisitGetType {
    TokenType operator()(const int&) const { return TokenType::T_TYPE_INT; }
    TokenType operator()(const float&) const { return TokenType::T_TYPE_FLOAT; }
    TokenType operator()(const std::string&) const { return TokenType::T_TYPE_STRING; }
    TokenType operator()(const GeographicCoordinate&) const { return TokenType::T_TYPE_GEOCOORD; }
    TokenType operator()(const GeographicPosition&) const { return TokenType::T_TYPE_GEO; }
    TokenType operator()(const GeographicDistance&) const { return TokenType::T_TYPE_GEODIST; }
    TokenType operator()(const auto&) const { return TokenType::T_UNKNOWN; }
};

struct VisitCompareType {
    bool operator()(const int&, const int&) const { return true; }
    bool operator()(const float&, const float&) const { return true; }
    bool operator()(const std::string&, const std::string&) const { return true; }
    bool operator()(const GeographicCoordinate&, const GeographicCoordinate&) const { return true; }
    bool operator()(const GeographicPosition&, const GeographicPosition&) const { return true; }
    bool operator()(const GeographicDistance&, const GeographicDistance&) const { return true; }
    bool operator()(const auto&, const auto&) const { return false; }
};


#endif //_TKOM__INTERPRETER_VISITCHECKTYPE_H
