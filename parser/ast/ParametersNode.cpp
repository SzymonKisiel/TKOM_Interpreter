#include "ParametersNode.h"

void ParametersNode::addType(TokenType type) {
    types.push_back(type);
}

void ParametersNode::addIdentifier(std::string identifier) {
    identifiers.push_back(identifier);
}

std::string ParametersNode::toString() {
    std::string result("PARAMETERS");
//        for (int i = 0; i < std::min(types.size(), identifiers.size()); ++i) {
//            result.append(tokenTypeToString(types[i]));
//            //<< '\t' << tokenTypeToString(types[i]) << '\t' << identifiers[i];
//        }
    return result;
}

void ParametersNode::print(int depth) {
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << toString();
    for (int i = 0; i < std::min(types.size(), identifiers.size()); ++i) {
        std::cout << '\t' << tokenTypeToString(types[i]) << '\t' << identifiers[i];
    }
    std::cout << std::endl;
}

const vector<TokenType> &ParametersNode::getTypes() {
    return types;
}

const vector<std::string> &ParametersNode::getIdentifiers() {
    return identifiers;
}
