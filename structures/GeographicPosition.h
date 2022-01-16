#ifndef _TKOM__INTERPRETER_GEOGRAPHICPOSITION_H
#define _TKOM__INTERPRETER_GEOGRAPHICPOSITION_H

#include "GeographicCoordinate.h"
class GeographicDistance;

class GeographicPosition {
public:
    GeographicPosition();
    GeographicPosition(const GeographicCoordinate &latitude, const GeographicCoordinate &longitude) ;
    void setLatitude(const GeographicCoordinate &latitude);
    void setLongitude(const GeographicCoordinate &longitude);
    GeographicPosition operator+(const GeographicDistance &geoDist) const;
    GeographicPosition operator-(const GeographicDistance &geoDist) const;
    GeographicDistance operator-(const GeographicPosition &geoPos) const;
    std::string toString();
    void validate();
private:
    GeographicCoordinate latitude;
    GeographicCoordinate longitude;
};


#endif //_TKOM__INTERPRETER_GEOGRAPHICPOSITION_H
