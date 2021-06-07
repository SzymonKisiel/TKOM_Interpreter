#ifndef _TKOM__INTERPRETER_GEOGRAPHICALPOSITION_H
#define _TKOM__INTERPRETER_GEOGRAPHICALPOSITION_H


#include "GeographicalCoordinate.h"

class GeographicalPosition {
public:
    void setLatitude(const GeographicalCoordinate &latitude) {
        GeographicalPosition::latitude = latitude;
    }

    void setLongitude(const GeographicalCoordinate &longitude) {
        GeographicalPosition::longitude = longitude;
    }

private:
    GeographicalCoordinate latitude;
    GeographicalCoordinate longitude
};


#endif //_TKOM__INTERPRETER_GEOGRAPHICALPOSITION_H
