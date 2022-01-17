#include "GeographicCoordinate.h"

GeographicCoordinate::GeographicCoordinate() : degree(0), minute(0), second(0) {};

GeographicCoordinate::GeographicCoordinate(int degree, int minute, int second, TokenType direction) :
        degree(degree), minute(minute), second(second), direction(direction) {};

GeographicCoordinate::GeographicCoordinate(int degree, int minute, int second, Direction direction) :
        degree(degree), minute(minute), second(second), direction(direction) {};

const int GeographicCoordinate::getDegree() const {
    return GeographicCoordinate::degree;
}

const int GeographicCoordinate::getMinute() const {
    return GeographicCoordinate::minute;
}

const int GeographicCoordinate::getSecond() const {
    return GeographicCoordinate::second;
}

const GeographicDirection GeographicCoordinate::getDirection() const {
    return GeographicCoordinate::direction;
}

void GeographicCoordinate::setDegree(int degree) {
    GeographicCoordinate::degree = degree;
}

void GeographicCoordinate::setMinute(int minute) {
    GeographicCoordinate::minute = minute;
}

void GeographicCoordinate::setSecond(int second) {
    GeographicCoordinate::second = second;
}

void GeographicCoordinate::setDirection(TokenType directionType) {
    GeographicCoordinate::direction = directionType;
}

const bool GeographicCoordinate::hasDirection() {
    if (direction.isDirection()) {
        return true;
    }
    return false;
}

const bool GeographicCoordinate::isLatitude() {
    if (direction.isLatitudeDirection()) {
        return true;
    }
    return false;
}

const bool GeographicCoordinate::isLongitude() {
    if (direction.isLongitudeDirection()) {
        return true;
    }
    return false;
}

std::string GeographicCoordinate::toString() {
    return std::string(to_string(degree))
            .append("^ ")
            .append(to_string(minute))
            .append("' ")
            .append(to_string(second))
            .append("'' ")
            .append(direction.toString());
}

void GeographicCoordinate::print() {
    std::cout << "GeographicCoordinate = ";
    if (degree)
        std::cout << degree << "^ ";
    if (minute)
        std::cout << minute << "' ";
    if (second)
        std::cout << second << "'' ";
    std::cout << direction.toString() << std::endl;
}

void GeographicCoordinate::validate() {
    if (second > 59)
        throw GeoException("GeographicCoordinate exceeds max seconds value");
    if (minute > 59)
        throw GeoException("GeographicCoordinate exceeds max minutes value");
    if (!direction.isDirection()) {
        throw GeoException("GeographicCoordinate has no specified direction");
    }
    double decimalDegree = static_cast<double>(second + 60*minute + 3600*degree) / 3600;
    if (direction.isLatitudeDirection() && decimalDegree > 90) {
        throw GeoException("GeographicCoordinate exceeds max latitude value");
    }
    if (direction.isLongitudeDirection() && decimalDegree > 180) {
        throw GeoException("GeographicCoordinate exceeds max longitude value");
    }
}

void GeographicCoordinate::validateAsXDistance() {
    if (second > 59)
        throw GeoException("GeographicCoordinate exceeds max seconds value");
    if (minute > 59)
        throw GeoException("GeographicCoordinate exceeds max minutes value");
    double decimalDegree = static_cast<double>(second + 60*minute + 3600*degree) / 3600;
    if (decimalDegree > 180) {
        throw GeoException("GeographicCoordinate exceeds max x distance value");
    }
}

void GeographicCoordinate::validateAsYDistance() {
    if (second > 59)
        throw GeoException("GeographicCoordinate exceeds max seconds value");
    if (minute > 59)
        throw GeoException("GeographicCoordinate exceeds max minutes value");
    double decimalDegree = static_cast<double>(second + 60*minute + 3600*degree) / 3600;
    if (decimalDegree > 360) {
        throw GeoException("GeographicCoordinate exceeds max y distance value");
    }
}