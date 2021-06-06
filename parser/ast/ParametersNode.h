#ifndef _TKOM__INTERPRETER_PARAMETERSNODE_H
#define _TKOM__INTERPRETER_PARAMETERSNODE_H

// parameters = parameter , {"," , parameter} ;
// parameter  = type , id ;
class ParametersNode : public Node {
    std::vector<TokenType> types;
    std::vector<std::string> identifiers;
public:
    void addType(TokenType type) {
        types.push_back(type);
    }

    void addIdentifier(std::string identifier) {
        identifiers.push_back(identifier);
    }

    std::string toString() {
        std::string result("PARAMETERS");
//        for (int i = 0; i < std::min(types.size(), identifiers.size()); ++i) {
//            result.append(tokenTypeToString(types[i]));
//            //<< '\t' << tokenTypeToString(types[i]) << '\t' << identifiers[i];
//        }
        return result;
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString();
        for (int i = 0; i < std::min(types.size(), identifiers.size()); ++i) {
            std::cout << '\t' << tokenTypeToString(types[i]) << '\t' << identifiers[i];
        }
        std::cout << std::endl;
    }
};


#endif //_TKOM__INTERPRETER_PARAMETERSNODE_H
