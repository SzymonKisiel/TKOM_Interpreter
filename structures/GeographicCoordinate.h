#ifndef _TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H
#define _TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H

#include "../lexer/Token.h"

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

    void print() {
        std::cout << "GeographicCoordinate = ";
        if (degree)
            std::cout << degree << "^ ";
        if (minute)
            std::cout << minute << "' ";
        if (second)
            std::cout << second << "'' ";
        std::cout << tokenTypeToString(direction) << std::endl;
    }

    GeographicCoordinate operator+(GeographicCoordinate const &geoPos);
    GeographicCoordinate operator-(GeographicCoordinate const &geoPos);
private:
    int degree = 0;
    int minute = 0;
    int second = 0;
    TokenType direction;
};


#endif //_TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H
