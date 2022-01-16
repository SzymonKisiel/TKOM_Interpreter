#ifndef _TKOM__INTERPRETER_GEOGRAPHICDISTANCE_H
#define _TKOM__INTERPRETER_GEOGRAPHICDISTANCE_H


#include "GeographicCoordinate.h"
class GeographicPosition;

class GeographicDistance {
public:
    GeographicDistance();
    GeographicDistance(const GeographicCoordinate &xDistance, const GeographicCoordinate &yDistance);
    GeographicDistance(const GeographicCoordinate &xDistance, const bool &isXNegative,
                       const GeographicCoordinate &yDistance, const bool &isYNegative);
    void setLatitude(const GeographicCoordinate &xDistance);
    void setLongitude(const GeographicCoordinate &yDistance);
    GeographicDistance operator+(const GeographicDistance &geoDist) const;
    GeographicPosition operator+(const GeographicPosition &geoPos) const;
    GeographicDistance operator-(const GeographicDistance &geoDist) const;
    GeographicDistance operator-() const;
    std::string toString();
    void validate();
private:
    bool isXNegative = false;
    bool isYNegative = false;
    GeographicCoordinate xDistance;
    GeographicCoordinate yDistance;
};


#endif //_TKOM__INTERPRETER_GEOGRAPHICDISTANCE_H
