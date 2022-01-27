#ifndef _TKOM__INTERPRETER_VISITCONDITION_H
#define _TKOM__INTERPRETER_VISITCONDITION_H


struct VisitCondition {
    bool operator() (int& condition) {
        if (condition == 0)
            return false;
        return true;
    }
    bool operator() (auto&) {
        return true;
    }
};


#endif //_TKOM__INTERPRETER_VISITCONDITION_H
