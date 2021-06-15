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


#endif //_TKOM__INTERPRETER_VISITPRINT_H
