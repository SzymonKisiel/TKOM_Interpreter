#include "ParametersNode.h"

void ParametersNode::addType(TokenType type) {
    types.push_back(type);
}

void ParametersNode::addIdentifier(std::string identifier) {
    identifiers.push_back(identifier);
}

std::string ParametersNode::toString(int depth) const {
    std::string result = getPrefix(depth);
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

std::vector<TokenType> ParametersNode::getTypes() const {
    return types;
}

std::vector<std::string> ParametersNode::getIdentifiers() const {
    return identifiers;
}
