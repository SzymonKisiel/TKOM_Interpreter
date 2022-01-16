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

    GeographicDistance operator+(const GeographicDistance &geoPos) const {
        int x1SecondSum = GeographicDistance::xDistance.getSecond()
                           + GeographicDistance::xDistance.getMinute() * 60
                           + GeographicDistance::xDistance.getDegree() * 3600;
        if (GeographicDistance::isXNegative)
            x1SecondSum *= -1;

        int x2SecondSum = geoPos.xDistance.getSecond()
                           + geoPos.xDistance.getMinute() * 60
                           + geoPos.xDistance.getDegree() * 3600;
        if (geoPos.isXNegative)
            x2SecondSum *= -1;

        int y1SecondSum = GeographicDistance::yDistance.getSecond()
                           + GeographicDistance::yDistance.getMinute() * 60
                           + GeographicDistance::yDistance.getDegree() * 3600;
        if (GeographicDistance::isYNegative)
            y1SecondSum *= -1;

        int y2SecondSum = geoPos.yDistance.getSecond()
                           + geoPos.yDistance.getMinute() * 60
                           + geoPos.yDistance.getDegree() * 3600;
        if (geoPos.isYNegative)
            y2SecondSum *= -1;

        // sum x to max 90 degrees
        int xSecondSum = min(x1SecondSum + x2SecondSum, 90 * 3600);

        // sum y to max 360 degrees and normalize to (-180, 180) range
        int ySecondSum = (y1SecondSum + y2SecondSum) % (360 * 3600);
        if (ySecondSum > 180 * 3600) {
            ySecondSum = 360 * 3600 - ySecondSum;
        }
        if (ySecondSum < -180 * 3600) {
            ySecondSum = 360 * 3600 + ySecondSum;
        }

        bool isResultXNegative = false;
        if (xSecondSum < 0) {
            xSecondSum *= -1;
            isResultXNegative = true;
        }
        bool isResultYNegative = false;
        if (ySecondSum < 0) {
            ySecondSum *= -1;
            isResultYNegative = true;
        }

        int resultXDegree = xSecondSum / 3600;
        int resultXMinute = xSecondSum % 3600 / 60;
        int resultXSecond = xSecondSum % 60;

        int resultYDegree = ySecondSum / 3600;
        int resultYMinute = ySecondSum % 3600 / 60;
        int resultYSecond = ySecondSum % 60;

        GeographicDistance result = GeographicDistance(
            GeographicCoordinate(resultXDegree,resultXMinute,resultXSecond,Direction::NONE),
            isResultXNegative,
            GeographicCoordinate(resultYDegree,resultYMinute,resultYSecond,Direction::NONE),
            isResultYNegative
        );
        return result;
    }
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
