#ifndef _TKOM__INTERPRETER_VISITPRINT_H
#define _TKOM__INTERPRETER_VISITPRINT_H

struct VisitPrintValue {
    void operator()(int& x)         { std::cout << x; }
    void operator()(float& x)       { std::cout << x; }
    void operator()(std::string& x) { std::cout << x; }
    void operator()(auto)           { std::cout << "empty/unknown"; }
};

struct VisitGetValue {
    int operator()(int& x) { return x; }
    float operator()(float& x) { return x; }
    std::string operator()(std::string& x) { return x; }
    int operator()(auto) { return 0;}
};

struct VisitToString {
    std::string operator()(int& x)         { return to_string(x); }
    std::string operator()(float& x)       { return to_string(x); }
    std::string operator()(std::string& x) { return x; }
    std::string operator()(GeographicCoordinate& x) { return x.toString(); }
    std::string operator()(auto)           { return "empty/unknown"; }
};


#endif //_TKOM__INTERPRETER_VISITPRINT_H
