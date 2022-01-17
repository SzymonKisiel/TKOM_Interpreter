#include "GeographicDistance.h"
#include "GeographicPosition.h"

GeographicDistance::GeographicDistance() = default;

GeographicDistance::GeographicDistance(const GeographicCoordinate &xDistance, const GeographicCoordinate &yDistance) {
    GeographicDistance::xDistance = xDistance;
    GeographicDistance::yDistance = yDistance;
}

GeographicDistance::GeographicDistance(const GeographicCoordinate &xDistance, const bool &isXNegative,
                   const GeographicCoordinate &yDistance, const bool &isYNegative) {
    GeographicDistance::xDistance = xDistance;
    GeographicDistance::isXNegative = isXNegative;
    GeographicDistance::yDistance = yDistance;
    GeographicDistance::isYNegative = isYNegative;
}

GeographicCoordinate GeographicDistance::getXDistance() const {
    return xDistance;
}

bool GeographicDistance::getIfXNegative() const {
    return isXNegative;
}

GeographicCoordinate GeographicDistance::getYDistance() const {
    return yDistance;
}

bool GeographicDistance::getIfYNegative() const {
    return isYNegative;
}


void GeographicDistance::setLatitude(const GeographicCoordinate &xDistance) {
    GeographicDistance::xDistance = xDistance;
}

void GeographicDistance::setLongitude(const GeographicCoordinate &yDistance) {
    GeographicDistance::yDistance = yDistance;
}

GeographicDistance GeographicDistance::operator+(const GeographicDistance &geoDist) const {
    int x1SecondSum = GeographicDistance::xDistance.getSecond()
                      + GeographicDistance::xDistance.getMinute() * 60
                      + GeographicDistance::xDistance.getDegree() * 3600;
    if (GeographicDistance::isXNegative)
        x1SecondSum *= -1;

    int x2SecondSum = geoDist.xDistance.getSecond()
                      + geoDist.xDistance.getMinute() * 60
                      + geoDist.xDistance.getDegree() * 3600;
    if (geoDist.isXNegative)
        x2SecondSum *= -1;

    int y1SecondSum = GeographicDistance::yDistance.getSecond()
                      + GeographicDistance::yDistance.getMinute() * 60
                      + GeographicDistance::yDistance.getDegree() * 3600;
    if (GeographicDistance::isYNegative)
        y1SecondSum *= -1;

    int y2SecondSum = geoDist.yDistance.getSecond()
                      + geoDist.yDistance.getMinute() * 60
                      + geoDist.yDistance.getDegree() * 3600;
    if (geoDist.isYNegative)
        y2SecondSum *= -1;

    // sum x to max 180 degrees
    int xSecondSum = x1SecondSum + x2SecondSum;
    xSecondSum = min(xSecondSum, 180 * 3600);
    xSecondSum = max(xSecondSum, -180 * 3600);

    // sum y to max 360 degrees and normalize to (-360, 360) range
    int ySecondSum = (y1SecondSum + y2SecondSum) % (360 * 3600);
//    if (ySecondSum > 180 * 3600) {
//        ySecondSum = 360 * 3600 - ySecondSum;
//    }
//    if (ySecondSum < -180 * 3600) {
//        ySecondSum = 360 * 3600 + ySecondSum;
//    }

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

GeographicPosition GeographicDistance::operator+(const GeographicPosition &geoPos) const {
    return geoPos.operator+(*this);
}

GeographicDistance GeographicDistance::operator-(const GeographicDistance &geoDist) const {
    return this->operator+(-geoDist);
}

GeographicDistance GeographicDistance::operator-() const {
    GeographicDistance result = GeographicDistance(xDistance, !isXNegative, yDistance, !isYNegative);
    return result;
}

std::string GeographicDistance::toString() {
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

void GeographicDistance::validate() {
    xDistance.validateAsXDistance();
    yDistance.validateAsYDistance();
}