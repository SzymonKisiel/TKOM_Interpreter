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
    GeographicDirection();
    GeographicDirection(Direction direction);
    GeographicDirection(TokenType directionToken);
    const bool isNorth() const;
    const bool isSouth() const;
    const bool isWest() const;
    const bool isEast() const;
    const bool isDirection();
    const bool isLatitudeDirection();
    const bool isLongitudeDirection();
    const std::string toString() const;
};

#endif //_TKOM__INTERPRETER_GEOGRAPHICDIRECTION_H
