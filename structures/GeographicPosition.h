#ifndef _TKOM__INTERPRETER_GEOGRAPHICPOSITION_H
#define _TKOM__INTERPRETER_GEOGRAPHICPOSITION_H

#include "GeographicCoordinate.h"
#include "GeographicDistance.h"

class GeographicPosition {
public:
    GeographicPosition() = default;
    GeographicPosition(const GeographicCoordinate &latitude, const GeographicCoordinate &longitude) {
        GeographicPosition::latitude = latitude;
        GeographicPosition::longitude = longitude;
    }

    void setLatitude(const GeographicCoordinate &latitude) {
        GeographicPosition::latitude = latitude;
    }

    void setLongitude(const GeographicCoordinate &longitude) {
        GeographicPosition::longitude = longitude;
    }

    GeographicDistance operator+(GeographicPosition const &geoPos);
    GeographicDistance operator-(GeographicPosition const &geoPos);
private:
    GeographicCoordinate latitude;
    GeographicCoordinate longitude;
};


#endif //_TKOM__INTERPRETER_GEOGRAPHICPOSITION_H
