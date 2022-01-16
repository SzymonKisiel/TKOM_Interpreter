#ifndef _TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H
#define _TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H

#include "../lexer/Token.h"
#include "GeographicDirection.h"

class GeographicCoordinate {
public:
    GeographicCoordinate();
    GeographicCoordinate(int degree, int minute, int second, TokenType direction);
    GeographicCoordinate(int degree, int minute, int second, Direction direction);
    const int getDegree() const;
    const int getMinute() const;
    const int getSecond() const;
    const GeographicDirection getDirection() const;
    void setDegree(int degree);
    void setMinute(int minute);
    void setSecond(int second);
    void setDirection(TokenType directionType);
    const bool hasDirection();
    const bool isLatitude();
    const bool isLongitude();
    std::string toString();
    void print();
    void validate();
    void validateAsXDistance();
    void validateAsYDistance();
private:
    int degree = 0;
    int minute = 0;
    int second = 0;
    GeographicDirection direction;
};


#endif //_TKOM__INTERPRETER_GEOGRAPHICCOORDINATE_H
