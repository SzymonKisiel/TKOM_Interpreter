//
// Created by kislu on 04.06.2021.
//

#ifndef _TKOM__INTERPRETER_FACTORNODE_H
#define _TKOM__INTERPRETER_FACTORNODE_H


class FactorNode : public Node {
    //type
    //value
public:
    std::string toString() {
        return "FACTOR";
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
    }
};


#endif //_TKOM__INTERPRETER_FACTORNODE_H
