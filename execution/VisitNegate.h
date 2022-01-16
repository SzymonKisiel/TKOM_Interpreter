#ifndef CATCHTEST_VISITNEGATE_H
#define CATCHTEST_VISITNEGATE_H

struct VisitNegate {
    Value operator()(int& x)         { return -x; }
    Value operator()(float& x)       { return -x; }
    Value operator()(std::string& x) { return x; }
    Value operator()(GeographicCoordinate& x) { return x; }
    Value operator()(GeographicPosition& x)   { return x; }
    Value operator()(GeographicDistance& x)   { return x; }
    Value operator()(auto) { return "empty/unknown"; }
};

#endif //CATCHTEST_VISITNEGATE_H
