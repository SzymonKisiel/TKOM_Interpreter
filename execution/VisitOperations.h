#ifndef CATCHTEST_VISITOPERATIONS_H
#define CATCHTEST_VISITOPERATIONS_H

#include "../exception/ExecutionException.h"

// compare operations
struct VisitLess {
    int operator() (int& lhs, int& rhs) {
        if (lhs < rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, float& rhs) {
        if (lhs < rhs)
            return 1;
        return 0;
    }
    int operator() (int& lhs, float& rhs) {
        if (lhs < rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, int& rhs) {
        if (lhs < rhs)
            return 1;
        return 0;
    }
    int operator() (auto lhs, auto rhs) { throw ExecutionException("Comparison < error"); }
};
struct VisitGreater {
    int operator() (int& lhs, int& rhs) {
        if (lhs > rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, float& rhs) {
        if (lhs > rhs)
            return 1;
        return 0;
    }
    int operator() (int& lhs, float& rhs) {
        if (lhs > rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, int& rhs) {
        if (lhs > rhs)
            return 1;
        return 0;
    }
    int operator() (auto lhs, auto rhs) { throw ExecutionException("Comparison > error"); }
};
struct VisitLessOrEqual {
    int operator() (int& lhs, int& rhs) {
        if (lhs <= rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, float& rhs) {
        if (lhs <= rhs)
            return 1;
        return 0;
    }
    int operator() (int& lhs, float& rhs) {
        if (lhs <= rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, int& rhs) {
        if (lhs <= rhs)
            return 1;
        return 0;
    }
    int operator() (auto lhs, auto rhs) { throw ExecutionException("Comparison <= error"); }
};
struct VisitGreaterOrEqual {
    int operator() (int& lhs, int& rhs) {
        if (lhs >= rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, float& rhs) {
        if (lhs >= rhs)
            return 1;
        return 0;
    }
    int operator() (int& lhs, float& rhs) {
        if (lhs >= rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, int& rhs) {
        if (lhs >= rhs)
            return 1;
        return 0;
    }
    int operator() (auto lhs, auto rhs) { throw ExecutionException("Comparison >= error"); }
};
struct VisitEqual {
    int operator() (int& lhs, int& rhs) {
        if (lhs == rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, float& rhs) {
        if (lhs == rhs)
            return 1;
        return 0;
    }
    int operator() (int& lhs, float& rhs) {
        if (lhs == rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, int& rhs) {
        if (lhs == rhs)
            return 1;
        return 0;
    }
    int operator() (auto lhs, auto rhs) { throw ExecutionException("Comparison == error"); }
};
struct VisitNotEqual {
    int operator() (int& lhs, int& rhs) {
        if (lhs != rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, float& rhs) {
        if (lhs != rhs)
            return 1;
        return 0;
    }
    int operator() (int& lhs, float& rhs) {
        if (lhs != rhs)
            return 1;
        return 0;
    }
    int operator() (float& lhs, int& rhs) {
        if (lhs != rhs)
            return 1;
        return 0;
    }
    int operator() (auto lhs, auto rhs) { throw ExecutionException("Comparison != error"); }
};

// multiply operations
struct VisitMult {
    Value operator()(int& lhs, int& rhs) { return lhs * rhs; }
    Value operator()(float& lhs, float& rhs) { return lhs * rhs; }
    Value operator()(int& lhs, float& rhs) { return lhs * rhs; }
    Value operator()(float& lhs, int& rhs) { return lhs * rhs; }
    Value operator()(auto& lhs, auto& rhs) { throw ExecutionException("Multiplication error"); }
};
struct VisitDiv {
    Value operator()(int& lhs, int& rhs) { return lhs / rhs; }
    Value operator()(float& lhs, float& rhs) { return lhs / rhs; }
    Value operator()(int& lhs, float& rhs) { return lhs / rhs; }
    Value operator()(float& lhs, int& rhs) { return lhs / rhs; }
    Value operator()(auto& lhs, auto& rhs) { throw ExecutionException("Division error"); }
};
struct VisitAnd {
    void operator()(int& lhs, int& rhs) {
        cout << lhs << " and " << rhs << endl;
        if (lhs != 0 && rhs != 0)
            lhs = 1;
        else
            lhs = 0;
    }
    void operator()(float& lhs, float& rhs) {
        if (lhs != 0 && rhs != 0)
            lhs = 1;
        else
            lhs = 0;
    }
    void operator()(int& lhs, float& rhs) {
        if (lhs != 0 && rhs != 0)
            lhs = 1;
        else
            lhs = 0;
    }
    void operator()(float& lhs, int& rhs) {
        if (lhs != 0 && rhs != 0)
            lhs = 1;
        else
            lhs = 0;
    }
    void operator()(auto& lhs, auto& rhs) { throw ExecutionException("Logical and error"); }
};

// add operations
struct VisitAdd {
    Value operator()(int& lhs, int& rhs) { return lhs + rhs; }
    Value operator()(float& lhs, float& rhs) { return lhs + rhs; }
    Value operator()(int& lhs, float& rhs) { return lhs + rhs; }
    Value operator()(float& lhs, int& rhs) { return lhs + rhs; }
    Value operator()(std::string& lhs, std::string& rhs) { return lhs.append(rhs); }
    Value operator()(auto& lhs, auto& rhs) { throw ExecutionException("Addition error"); }
};
struct VisitSubstract {
    Value operator()(int& lhs, int& rhs) { return lhs - rhs; }
    Value operator()(float& lhs, float& rhs) { return lhs - rhs; }
    Value operator()(int& lhs, float& rhs) { return lhs - rhs; }
    Value operator()(float& lhs, int& rhs) { return lhs - rhs; }
    Value operator()(auto& lhs, auto& rhs) { throw ExecutionException("Subtraction error"); }
};
struct VisitOr {
    void operator()(int& lhs, int& rhs) {
        if (lhs != 0 || rhs != 0)
            lhs = 1;
        else
            lhs = 0;
    }
    /*void operator()(float& lhs, float& rhs) {
        if (lhs != 0 || rhs != 0)
            lhs = 1;
        else
            lhs = 0;
    }
    void operator()(int& lhs, float& rhs) {
        if (lhs != 0 || rhs != 0)
            lhs = 1;
        else
            lhs = 0;
    }
    void operator()(float& lhs, int& rhs) {
        if (lhs != 0 || rhs != 0)
            lhs = 1;
        else
            lhs = 0;
    }*/
    void operator()(auto& lhs, auto& rhs) { throw ExecutionException("Logical 'or' error"); }
};


#endif //CATCHTEST_VISITOPERATIONS_H
