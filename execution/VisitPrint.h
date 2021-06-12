//
// Created by kislu on 12.06.2021.
//

#ifndef _TKOM__INTERPRETER_VISITPRINT_H
#define _TKOM__INTERPRETER_VISITPRINT_H


struct VisitPrint {
    void operator()(int& x)         { std::cout << "int: " << x << std::endl; }
    void operator()(float& x)       { std::cout << "float: " << x << std::endl; }
    void operator()(std::string& x) { std::cout << "string: " << x << std::endl; }
    void operator()(auto)           { std::cout << "empty/unknown\n"; }
};

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
