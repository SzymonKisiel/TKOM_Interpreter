#ifndef CATCHTEST_GEOEXCEPTION_H
#define CATCHTEST_GEOEXCEPTION_H

#include "Exception.h"

class GeoException : public Exception {
public:
    GeoException(std::string msg) : Exception(std::move(msg)) {}
};

#endif //CATCHTEST_GEOEXCEPTION_H
