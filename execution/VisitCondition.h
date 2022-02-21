#ifndef _TKOM__INTERPRETER_VISITCONDITION_H
#define _TKOM__INTERPRETER_VISITCONDITION_H


struct VisitCondition {
    bool operator() (const int& condition) const {
        if (condition == 0)
            return false;
        return true;
    }
    bool operator() (const auto&) const {
        return true;
    }
};


#endif //_TKOM__INTERPRETER_VISITCONDITION_H
