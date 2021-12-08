#ifndef _TKOM__INTERPRETER_VISITPRINT_H
#define _TKOM__INTERPRETER_VISITPRINT_H

struct VisitPrintValue {
    void operator()(int& x)         { std::cout << x << std::endl; }
    void operator()(float& x)       { std::cout << x << std::endl; }
    void operator()(std::string& x) { std::cout << x << std::endl; }
    void operator()(auto)           { std::cout << "empty/unknown" << std::endl; }
};

struct VisitGetValue {
    int operator()(int& x) { return x; }
    float operator()(float& x) { return x; }
    std::string operator()(std::string& x) { return x; }
    int operator()(auto) { return 0;}
};

struct VisitToString {
    std::string operator()(int& x)         { return std::to_string(x); }
    std::string operator()(float& x)       { return std::to_string(x); }
    std::string operator()(std::string& x) { return x; }
    std::string operator()(auto)           { return "empty"; }
};

struct VisitTest {
    std::string operator()(int&)         { return "int"; }
    std::string operator()(float&)       { return "float"; }
    std::string operator()(std::string&) { return "string"; }
    std::string operator()(auto)         { return "empty"; }
};

#endif //_TKOM__INTERPRETER_VISITPRINT_H
