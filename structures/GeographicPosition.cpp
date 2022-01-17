#include "GeographicPosition.h"
#include "GeographicDistance.h"

GeographicPosition::GeographicPosition() = default;

GeographicPosition::GeographicPosition(const GeographicCoordinate &latitude, const GeographicCoordinate &longitude) {
    GeographicPosition::latitude = latitude;
    GeographicPosition::longitude = longitude;
}

const GeographicCoordinate GeographicPosition::getLatitude() const {
    return latitude;
}

const GeographicCoordinate GeographicPosition::getLongitude() const {
    return longitude;
}

void GeographicPosition::setLatitude(const GeographicCoordinate &latitude) {
    GeographicPosition::latitude = latitude;
}

void GeographicPosition::setLongitude(const GeographicCoordinate &longitude) {
    GeographicPosition::longitude = longitude;
}

GeographicPosition GeographicPosition::operator+(const GeographicDistance &geoDist) const {
    int x1SecondSum = GeographicPosition::latitude.getSecond()
                      + GeographicPosition::latitude.getMinute() * 60
                      + GeographicPosition::latitude.getDegree() * 3600;
    if (GeographicPosition::latitude.getDirection().isSouth())
        x1SecondSum *= -1;

    int x2SecondSum = geoDist.getXDistance().getSecond()
                      + geoDist.getXDistance().getMinute() * 60
                      + geoDist.getXDistance().getDegree() * 3600;
    if (geoDist.getIfXNegative())
        x2SecondSum *= -1;

    int y1SecondSum = GeographicPosition::longitude.getSecond()
                      + GeographicPosition::longitude.getMinute() * 60
                      + GeographicPosition::longitude.getDegree() * 3600;
    if (GeographicPosition::longitude.getDirection().isWest())
        y1SecondSum *= -1;

    int y2SecondSum = geoDist.getYDistance().getSecond()
                      + geoDist.getYDistance().getMinute() * 60
                      + geoDist.getYDistance().getDegree() * 3600;
    if (geoDist.getIfYNegative())
        y2SecondSum *= -1;

    // sum x to max 90 degrees
    int xSecondSum = x1SecondSum + x2SecondSum;
    xSecondSum = min(xSecondSum, 90 * 3600);
    xSecondSum = max(xSecondSum, -90 * 3600);

    // sum y and normalize to (-180, 180) range
    int ySecondSum = y1SecondSum + y2SecondSum;
    ySecondSum += 180 * 3600;
    ySecondSum %= 360 * 3600;
    ySecondSum -= 180 * 3600;

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

    Direction resultXDirection = isResultXNegative ? Direction::S : Direction::N;
    Direction resultYDirection = isResultYNegative ? Direction::W : Direction::E;

    GeographicPosition result = GeographicPosition(
            GeographicCoordinate(resultXDegree, resultXMinute, resultXSecond, resultXDirection),
            GeographicCoordinate(resultYDegree, resultYMinute, resultYSecond, resultYDirection)
    );
    return result;
}

GeographicPosition GeographicPosition::operator-(const GeographicDistance &geoDist) const {
    return this->operator+(-geoDist);
}

GeographicDistance GeographicPosition::operator-(const GeographicPosition &geoPos) const {
    int x1SecondSum = GeographicPosition::latitude.getSecond()
                      + GeographicPosition::latitude.getMinute() * 60
                      + GeographicPosition::latitude.getDegree() * 3600;
    if (GeographicPosition::latitude.getDirection().isSouth())
        x1SecondSum *= -1;

    int x2SecondSum = geoPos.getLatitude().getSecond()
                      + geoPos.getLatitude().getMinute() * 60
                      + geoPos.getLatitude().getDegree() * 3600;
    if (geoPos.getLatitude().getDirection().isSouth())
        x2SecondSum *= -1;

    int y1SecondSum = GeographicPosition::longitude.getSecond()
                      + GeographicPosition::longitude.getMinute() * 60
                      + GeographicPosition::longitude.getDegree() * 3600;
    if (GeographicPosition::longitude.getDirection().isWest())
        y1SecondSum *= -1;

    int y2SecondSum = geoPos.getLongitude().getSecond()
                      + geoPos.getLongitude().getMinute() * 60
                      + geoPos.getLongitude().getDegree() * 3600;
    if (geoPos.getLongitude().getDirection().isWest())
        y2SecondSum *= -1;

    // sum x to max 180 degrees
    int resultX = x1SecondSum - x2SecondSum;
    resultX = min(resultX, 180 * 3600);
    resultX = max(resultX, -180 * 3600);

    // sum y to max 360 degrees and normalize to (-360, 360) range
    int resultY = (y1SecondSum - y2SecondSum) % (360 * 3600);

    bool isResultXNegative = false;
    if (resultX < 0) {
        resultX *= -1;
        isResultXNegative = true;
    }
    bool isResultYNegative = false;
    if (resultY < 0) {
        resultY *= -1;
        isResultYNegative = true;
    }

    int resultXDegree = resultX / 3600;
    int resultXMinute = resultX % 3600 / 60;
    int resultXSecond = resultX % 60;

    int resultYDegree = resultY / 3600;
    int resultYMinute = resultY % 3600 / 60;
    int resultYSecond = resultY % 60;

    GeographicDistance result = GeographicDistance(
            GeographicCoordinate(resultXDegree, resultXMinute, resultXSecond, Direction::NONE),
            isResultXNegative,
            GeographicCoordinate(resultYDegree, resultYMinute, resultYSecond, Direction::NONE),
            isResultYNegative
    );
    return result;
}

std::string GeographicPosition::toString() {
    return std::string(latitude.toString())
            .append("\t")
            .append(longitude.toString());
}

void GeographicPosition::validate() {
    latitude.validate();
    longitude.validate();
    if (!latitude.isLatitude())
        throw GeoException("GeographicPosition first coordinate is not latitude");
    if (!longitude.isLongitude())
        throw GeoException("GeographicPosition second coordinate is not longitude");
}