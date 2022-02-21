#ifndef CATCHTEST_VISITNEGATE_H
#define CATCHTEST_VISITNEGATE_H

struct VisitNegate {
    Value operator()(const int& x) const { return -x; }
    Value operator()(const float& x) const { return -x; }
    Value operator()(const std::string& x) const { throw ExecutionException("Negation error - can not negate string"); }
    Value operator()(const GeographicCoordinate& x) const { throw ExecutionException("Negation error - can not negate geocoord"); }
    Value operator()(const GeographicPosition& x) const { throw ExecutionException("Negation error - can not negate geo"); }
    Value operator()(const GeographicDistance& x) const { return -x; }
    Value operator()(const auto&) const { throw ExecutionException("Negation error"); }
};

#endif //CATCHTEST_VISITNEGATE_H
