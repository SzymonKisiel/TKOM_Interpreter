#ifndef _TKOM__INTERPRETER_ASSIGNMENTNODE_H
#define _TKOM__INTERPRETER_ASSIGNMENTNODE_H


class AssignmentNode : public Node {
    std::string id;
    std::unique_ptr<ExpressionNode> expression;
public:
    void setExpression(std::unique_ptr<ExpressionNode> expression) {
        this->expression = std::move(expression);
    }

    std::string toString() {
        return "ASSIGNMENT";
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        if (expression != nullptr)
            expression->print(depth + 1);
    };
};


#endif //_TKOM__INTERPRETER_ASSIGNMENTNODE_H
