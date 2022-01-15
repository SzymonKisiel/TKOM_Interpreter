#ifndef _TKOM__INTERPRETER_GEOGRAPHICDIRECTION_H
#define _TKOM__INTERPRETER_GEOGRAPHICDIRECTION_H

#include "../lexer/Token.h"
#include "../exception/GeoException.h"

enum Direction {
    NONE, N, W, S, E
};
class GeographicDirection {
private:
    Direction direction;
    inline static const std::string directionNames[5] = {
        "",
        "N",
        "W",
        "S",
        "E"
    };
public:
    GeographicDirection() : direction(Direction::NONE) {}
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
                throw GeoException(std::string("GeographicDirection can't be converted from ")
                                        .append(tokenTypeToString(directionToken)));
        }
    }

    const bool isDirection() {
        if (direction == Direction::NONE) {
            return false;
        }
        return true;
    }

    const bool isLatitudeDirection() {
        if (direction == Direction::N || direction == Direction::S) {
            return true;
        }
        return false;
    }

    const bool isLongitudeDirection() {
        if (direction == Direction::W || direction == Direction::E) {
            return true;
        }
        return false;
    }

    const std::string toString() const {
        return directionNames[direction];
    }
};

#endif //_TKOM__INTERPRETER_GEOGRAPHICDIRECTION_H
