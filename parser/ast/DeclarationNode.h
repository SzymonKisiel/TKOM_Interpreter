#ifndef _TKOM__INTERPRETER_DECLARATIONNODE_H
#define _TKOM__INTERPRETER_DECLARATIONNODE_H

class DeclarationNode : public Node {
    std::string id;
    //type
    std::unique_ptr<ExpressionNode> expression;
public:
    void setExpression(std::unique_ptr<ExpressionNode> expression) {
        this->expression = std::move(expression);
    }

    std::string toString() {
        return "DECLARATION";
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        if (expression != nullptr)
            expression->print(depth + 1);
    };
};


#endif //_TKOM__INTERPRETER_DECLARATIONNODE_H
