#include "ParametersNode.h"

void ParametersNode::addType(TokenType type) {
    types.push_back(type);
}

void ParametersNode::addIdentifier(std::string identifier) {
    identifiers.push_back(identifier);
}

std::string ParametersNode::toString(int depth) {
    std::string result = std::string();
    for (int i = 0; i < depth; ++i)
        result.append(prefix);
    result.append("PARAMETERS");

    for (int i = 0; i < std::min(types.size(), identifiers.size()); ++i) {
        result.append("\t")
                .append(tokenTypeToString(types[i]))
                .append("\t")
                .append(identifiers[i]);
    }
    result.append("\n");

    return result;
}

const vector<TokenType> &ParametersNode::getTypes() {
    return types;
}

const vector<std::string> &ParametersNode::getIdentifiers() {
    return identifiers;
}
