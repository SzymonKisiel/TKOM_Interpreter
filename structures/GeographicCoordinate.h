#ifndef _TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H
#define _TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H

#include "../lexer/Token.h"
#include "GeographicDistance.h"
#include "GeographicDirection.h"

class GeographicCoordinate {
public:
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

    GeographicDistance operator+(GeographicCoordinate const &geoPos);
    GeographicDistance operator-(GeographicCoordinate const &geoPos);
private:
    int degree = 0;
    int minute = 0;
    int second = 0;
    GeographicDirection direction;
};


#endif //_TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H
