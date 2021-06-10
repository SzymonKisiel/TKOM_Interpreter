#ifndef _TKOM__INTERPRETER_GEOGRAPHICALCOORDINATE_H
#define _TKOM__INTERPRETER_GEOGRAPHICALCOORDINATE_H


class GeographicalCoordinate {
public:
    void setDegree(int degree) {
        GeographicalCoordinate::degree = degree;
    }

    void setMinute(int minute) {
        GeographicalCoordinate::minute = minute;
    }

    void setSecond(int second) {
        GeographicalCoordinate::second = second;
    }

private:
    int degree;
    int minute;
    int second;
};


#endif //_TKOM__INTERPRETER_GEOGRAPHICALCOORDINATE_H
