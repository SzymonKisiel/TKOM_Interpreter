#ifndef _TKOM__INTERPRETER_GEOGRAPHICDIRECTION_H
#define _TKOM__INTERPRETER_GEOGRAPHICDIRECTION_H

#include "../lexer/Token.h"

enum Direction {
    N, W, S, E
};
class GeographicDirection {
private:
    Direction direction;
    inline static const std::string directionNames[4] = {
        "N",
        "W",
        "S",
        "E"
    };
public:
    GeographicDirection() : direction(Direction::N) {}
    GeographicDirection(Direction direction) : direction(direction) {}
    GeographicDirection(TokenType directionToken) {
        switch (directionToken) {
            case TokenType::T_GEO_DIRECTION_N:
                this->direction = Direction::N;
                break;
            case TokenType::T_GEO_DIRECTION_W:
                this->direction = Direction::W;
                break;
            case TokenType::T_GEO_DIRECTION_S:
                this->direction = Direction::S;
                break;
            case TokenType::T_GEO_DIRECTION_E:
                this->direction = Direction::E;
                break;
            default:
                throw; //TODO: Exception
        }
    }
    const std::string toString() const {
        return directionNames[direction];
    }
};

#endif //_TKOM__INTERPRETER_GEOGRAPHICDIRECTION_H
