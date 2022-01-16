#include "GeographicDirection.h"

GeographicDirection::GeographicDirection() : direction(Direction::NONE) {}

GeographicDirection::GeographicDirection(Direction direction) : direction(direction) {}

GeographicDirection::GeographicDirection(TokenType directionToken) {
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

const bool GeographicDirection::isDirection() {
    if (direction == Direction::NONE) {
        return false;
    }
    return true;
}

const bool GeographicDirection::isLatitudeDirection() {
    if (direction == Direction::N || direction == Direction::S) {
        return true;
    }
    return false;
}

const bool GeographicDirection::isLongitudeDirection() {
    if (direction == Direction::W || direction == Direction::E) {
        return true;
    }
    return false;
}

const std::string GeographicDirection::toString() const {
    return directionNames[direction];
}