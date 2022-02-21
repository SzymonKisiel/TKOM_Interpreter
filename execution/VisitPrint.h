#ifndef _TKOM__INTERPRETER_VISITPRINT_H
#define _TKOM__INTERPRETER_VISITPRINT_H

struct VisitPrintValue {
    void operator()(int& x)         { std::cout << x; }
    void operator()(float& x)       { std::cout << x; }
    void operator()(std::string& x) { std::cout << x; }
    void operator()(GeographicCoordinate& x) { std::cout << x.toString(); }
    void operator()(GeographicPosition& x)   { std::cout << x.toString(); }
    void operator()(GeographicDistance& x)   { std::cout << x.toString(); }
    void operator()(auto) { std::cout << "empty/unknown"; }
};

struct VisitToString {
    std::string operator()(int& x)         { return to_string(x); }
    std::string operator()(float& x)       { return to_string(x); }
    std::string operator()(std::string& x) { return x; }
    std::string operator()(GeographicCoordinate& x) { return x.toString(); }
    std::string operator()(GeographicPosition& x)   { return x.toString(); }
    std::string operator()(GeographicDistance& x)   { return x.toString(); }
    std::string operator()(auto) { return "empty/unknown"; }
};


#endif //_TKOM__INTERPRETER_VISITPRINT_H
