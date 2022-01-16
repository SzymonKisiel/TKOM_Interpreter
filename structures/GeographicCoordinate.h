#ifndef _TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H
#define _TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H

#include "../lexer/Token.h"
#include "GeographicDirection.h"

class GeographicCoordinate {
public:
    GeographicCoordinate() : degree(0), minute(0), second(0) {};
    GeographicCoordinate(int degree, int minute, int second, TokenType direction) :
        degree(degree), minute(minute), second(second), direction(direction) {};
    GeographicCoordinate(int degree, int minute, int second, Direction direction) :
            degree(degree), minute(minute), second(second), direction(direction) {};

    const int getDegree() const {
        return GeographicCoordinate::degree;
    }

    const int getMinute() const {
        return GeographicCoordinate::minute;
    }

    const int getSecond() const {
        return GeographicCoordinate::second;
    }

    const GeographicDirection getDirection() const {
        return GeographicCoordinate::direction;
    }

    void setDegree(int degree) {
        GeographicCoordinate::degree = degree;
    }

    void setMinute(int minute) {
        GeographicCoordinate::minute = minute;
    }

    void setSecond(int second) {
        GeographicCoordinate::second = second;
    }

    void setDirection(TokenType directionType) {
        GeographicCoordinate::direction = directionType;
    }

    const bool hasDirection() {
        if (direction.isDirection()) {
            return true;
        }
        return false;
    }

    const bool isLatitude() {
        if (direction.isLatitudeDirection()) {
            return true;
        }
        return false;
    }

    const bool isLongitude() {
        if (direction.isLongitudeDirection()) {
            return true;
        }
        return false;
    }

    std::string toString() {
        return std::string(to_string(degree))
                            .append("^ ")
                            .append(to_string(minute))
                            .append("' ")
                            .append(to_string(second))
                            .append("'' ")
                            .append(direction.toString());
    }

    void print() {
        std::cout << "GeographicCoordinate = ";
        if (degree)
            std::cout << degree << "^ ";
        if (minute)
            std::cout << minute << "' ";
        if (second)
            std::cout << second << "'' ";
        std::cout << direction.toString() << std::endl;
    }

    void validate() {
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

    void validateAsXDistance() {
        if (second > 59)
            throw GeoException("GeographicCoordinate exceeds max seconds value");
        if (minute > 59)
            throw GeoException("GeographicCoordinate exceeds max minutes value");
        double decimalDegree = static_cast<double>(second + 60*minute + 3600*degree) / 3600;
        if (decimalDegree > 90) {
            throw GeoException("GeographicCoordinate exceeds max x distance value");
        }
    }

    void validateAsYDistance() {
        if (second > 59)
            throw GeoException("GeographicCoordinate exceeds max seconds value");
        if (minute > 59)
            throw GeoException("GeographicCoordinate exceeds max minutes value");
        double decimalDegree = static_cast<double>(second + 60*minute + 3600*degree) / 3600;
        if (decimalDegree > 180) {
            throw GeoException("GeographicCoordinate exceeds max y distance value");
        }
    }

private:
    int degree = 0;
    int minute = 0;
    int second = 0;
    GeographicDirection direction;
};


#endif //_TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H
