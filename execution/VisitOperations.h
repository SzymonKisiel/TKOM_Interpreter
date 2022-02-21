#ifndef CATCHTEST_VISITOPERATIONS_H
#define CATCHTEST_VISITOPERATIONS_H

#include "../exception/ExecutionException.h"

// compare operations
struct VisitLess {
    int operator() (const int& lhs, const int& rhs) const {
        if (lhs < rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const float& rhs) const {
        if (lhs < rhs)
            return 1;
        return 0;
    }
    int operator() (const int& lhs, const float& rhs) const {
        if (lhs < rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const int& rhs) const {
        if (lhs < rhs)
            return 1;
        return 0;
    }
    int operator() (const auto&, const auto&) const { throw ExecutionException("Comparison < error"); }
};
struct VisitGreater {
    int operator() (const int& lhs, const int& rhs) const {
        if (lhs > rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const float& rhs) const {
        if (lhs > rhs)
            return 1;
        return 0;
    }
    int operator() (const int& lhs, const float& rhs) const {
        if (lhs > rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const int& rhs) const {
        if (lhs > rhs)
            return 1;
        return 0;
    }
    int operator() (const auto&, const auto&) const { throw ExecutionException("Comparison > error"); }
};
struct VisitLessOrEqual {
    int operator() (const int& lhs, const int& rhs) const {
        if (lhs <= rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const float& rhs) const {
        if (lhs <= rhs)
            return 1;
        return 0;
    }
    int operator() (const int& lhs, const float& rhs) const {
        if (lhs <= rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const int& rhs) const {
        if (lhs <= rhs)
            return 1;
        return 0;
    }
    int operator() (const auto&, const auto&) const { throw ExecutionException("Comparison <= error"); }
};
struct VisitGreaterOrEqual {
    int operator() (const int& lhs, const int& rhs) const {
        if (lhs >= rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const float& rhs) const {
        if (lhs >= rhs)
            return 1;
        return 0;
    }
    int operator() (const int& lhs, const float& rhs) const {
        if (lhs >= rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const int& rhs) const {
        if (lhs >= rhs)
            return 1;
        return 0;
    }
    int operator() (const auto&, const auto&) const { throw ExecutionException("Comparison >= error"); }
};
struct VisitEqual {
    int operator() (const int& lhs, const int& rhs) const {
        if (lhs == rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const float& rhs) const {
        if (lhs == rhs)
            return 1;
        return 0;
    }
    int operator() (const int& lhs, const float& rhs) const {
        if (lhs == rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const int& rhs) const {
        if (lhs == rhs)
            return 1;
        return 0;
    }
    int operator() (const auto&, const auto&) const { throw ExecutionException("Comparison == error"); }
};
struct VisitNotEqual {
    int operator() (const int& lhs, const int& rhs) const {
        if (lhs != rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const float& rhs) const {
        if (lhs != rhs)
            return 1;
        return 0;
    }
    int operator() (const int& lhs, const float& rhs) const {
        if (lhs != rhs)
            return 1;
        return 0;
    }
    int operator() (const float& lhs, const int& rhs) const {
        if (lhs != rhs)
            return 1;
        return 0;
    }
    int operator() (const auto&, const auto&) const { throw ExecutionException("Comparison != error"); }
};

// multiply operations
struct VisitMult {
    Value operator()(const int& lhs, const int& rhs) const { return lhs * rhs; }
    Value operator()(const float& lhs, const float& rhs) const { return lhs * rhs; }
    Value operator()(const int& lhs, const float& rhs) const { return lhs * rhs; }
    Value operator()(const float& lhs, const int& rhs) const { return lhs * rhs; }
    Value operator()(const auto&, const auto&) const { throw ExecutionException("Multiplication error"); }
};
struct VisitDiv {
    Value operator()(const int& lhs, const int& rhs) const { return lhs / rhs; }
    Value operator()(const float& lhs, const float& rhs) const { return lhs / rhs; }
    Value operator()(const int& lhs, const float& rhs) const { return lhs / rhs; }
    Value operator()(const float& lhs, const int& rhs) const { return lhs / rhs; }
    Value operator()(const auto&, const auto&) const { throw ExecutionException("Division error"); }
};
struct VisitAnd {
    int operator()(const int& lhs, const int& rhs) const {
        //cout << lhs << " and " << rhs << endl;
        if (lhs != 0 && rhs != 0)
            return 1;
        return 0;
    }
    int operator()(const float& lhs, const float& rhs) const {
        if (lhs != 0 && rhs != 0)
            return 1;
        return 0;
    }
    int operator()(const int& lhs, const float& rhs) const {
        if (lhs != 0 && rhs != 0)
            return 1;
        return 0;
    }
    int operator()(const float& lhs, const int& rhs) const {
        if (lhs != 0 && rhs != 0)
            return 1;
        return 0;
    }
    int operator()(const auto&, const auto&) const { throw ExecutionException("Logical and error"); }
};

// add operations
struct VisitAdd {
    Value operator()(const int& lhs, const int& rhs) const { return lhs + rhs; }
    Value operator()(const float& lhs, const float& rhs) const { return lhs + rhs; }
    Value operator()(const int& lhs, const float& rhs) const { return lhs + rhs; }
    Value operator()(const float& lhs, const int& rhs) const { return lhs + rhs; }
    Value operator()(const std::string& lhs, const std::string& rhs) const { return std::string().append(lhs).append(rhs); }
    // geodist + geodist
    Value operator()(const GeographicDistance& lhs, const GeographicDistance& rhs) const { return lhs + rhs; }
    // geo + geodist
    Value operator()(const GeographicPosition& lhs, const GeographicDistance& rhs) const { return lhs + rhs; }
    // geodist + geo
    Value operator()(const GeographicDistance& lhs, const GeographicPosition& rhs) const { return lhs + rhs; }
    Value operator()(const auto&, const auto&) const { throw ExecutionException("Addition error"); }
};
struct VisitSubtract {
    Value operator()(const int& lhs, const int& rhs) const { return lhs - rhs; }
    Value operator()(const float& lhs, const float& rhs) const { return lhs - rhs; }
    Value operator()(const int& lhs, const float& rhs) const { return lhs - rhs; }
    Value operator()(const float& lhs, const int& rhs) const { return lhs - rhs; }
    // geodist - geodist
    Value operator()(const GeographicDistance& lhs, const GeographicDistance& rhs) const { return lhs - rhs; }
    // geo - geo
    Value operator()(const GeographicPosition& lhs, const GeographicPosition& rhs) const { return lhs - rhs; }
    // geo - geodist??
    Value operator()(const GeographicPosition& lhs, const GeographicDistance& rhs) const { return lhs - rhs; }
    Value operator()(const auto&, const auto&) const { throw ExecutionException("Subtraction error"); }
};
struct VisitOr {
    int operator()(const int& lhs, const int& rhs) const {
        if (lhs != 0 || rhs != 0)
            return 1;
        return 0;
    }
    int operator()(const float& lhs, const float& rhs) const {
        if (lhs != 0 || rhs != 0)
            return 1;
        return 0;
    }
    int operator()(const int& lhs, const float& rhs) const {
        if (lhs != 0 || rhs != 0)
            return 1;
        return 0;
    }
    int operator()(const float& lhs, const int& rhs) const {
        if (lhs != 0 || rhs != 0)
            return 1;
        return 0;
    }
    int operator()(const auto&, const auto&) const { throw ExecutionException("Logical 'or' error"); }
};


#endif //CATCHTEST_VISITOPERATIONS_H
