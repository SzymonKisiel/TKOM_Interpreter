#ifndef _TKOM__INTERPRETER_GEOGRAPHICDISTANCE_H
#define _TKOM__INTERPRETER_GEOGRAPHICDISTANCE_H

#include "GeographicCoordinate.h"

class GeographicDistance {
public:
    GeographicDistance() = default;
    GeographicDistance(const GeographicCoordinate &xDistance, const GeographicCoordinate &yDistance) {
        GeographicDistance::xDistance = xDistance;
        GeographicDistance::yDistance = yDistance;
    }
    GeographicDistance(const GeographicCoordinate &xDistance, const bool &isXNegative,
                       const GeographicCoordinate &yDistance, const bool &isYNegative) {
        GeographicDistance::xDistance = xDistance;
        GeographicDistance::isXNegative = isXNegative;
        GeographicDistance::yDistance = yDistance;
        GeographicDistance::isYNegative = isYNegative;
    }

    void setLatitude(const GeographicCoordinate &xDistance) {
        GeographicDistance::xDistance = xDistance;
    }

    void setLongitude(const GeographicCoordinate &yDistance) {
        GeographicDistance::yDistance = yDistance;
    }

    GeographicDistance operator+(GeographicDistance const &geoPos);
    GeographicDistance operator-(GeographicDistance const &geoPos);

    GeographicDistance operator-() const {
        GeographicDistance result = GeographicDistance(xDistance, !isXNegative, yDistance, !isYNegative);
        return result;
    }

    std::string toString() {
        std::string xSign, ySign;
        if (isXNegative)
            xSign = "-";
        if (isYNegative)
            ySign = "-";
        return std::string(xSign)
                .append(xDistance.toString())
                .append("\t")
                .append(ySign)
                .append(yDistance.toString());
    }

    void validate() {
        xDistance.validateAsXDistance();
        yDistance.validateAsYDistance();
    }

private:
    bool isXNegative = false;
    bool isYNegative = false;
    GeographicCoordinate xDistance;
    GeographicCoordinate yDistance;
};


#endif //_TKOM__INTERPRETER_GEOGRAPHICDISTANCE_H
