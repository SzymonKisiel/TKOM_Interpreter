#ifndef CATCHTEST_VISITNEGATE_H
#define CATCHTEST_VISITNEGATE_H

struct VisitNegate {
    Value operator()(int& x)         { return -x; }
    Value operator()(float& x)       { return -x; }
    Value operator()(std::string& x) { throw ExecutionException("Negation error - can not negate string"); }
    Value operator()(GeographicCoordinate& x) { throw ExecutionException("Negation error - can not negate geocoord"); }
    Value operator()(GeographicPosition& x)   { throw ExecutionException("Negation error - can not negate geo"); }
    Value operator()(GeographicDistance& x)   { return -x; }
    Value operator()(auto) { return "empty/unknown"; }
};

#endif //CATCHTEST_VISITNEGATE_H
