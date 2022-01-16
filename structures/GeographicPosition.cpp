#include "GeographicPosition.h"
#include "GeographicDistance.h"

GeographicPosition::GeographicPosition() = default;

GeographicPosition::GeographicPosition(const GeographicCoordinate &latitude, const GeographicCoordinate &longitude) {
    GeographicPosition::latitude = latitude;
    GeographicPosition::longitude = longitude;
}

void GeographicPosition::setLatitude(const GeographicCoordinate &latitude) {
    GeographicPosition::latitude = latitude;
}

void GeographicPosition::setLongitude(const GeographicCoordinate &longitude) {
    GeographicPosition::longitude = longitude;
}

GeographicPosition GeographicPosition::operator+(const GeographicDistance &geoDist) const {
    throw("geo + geodist not implemented");
}

GeographicPosition GeographicPosition::operator-(const GeographicDistance &geoDist) const {
    throw("geo - geodist not implemented");
}

GeographicDistance GeographicPosition::operator-(const GeographicPosition &geoPos) const {
    throw("geo - geo not implemented");
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