#ifndef _TKOM__INTERPRETER_RETURNSTATEMENTNODE_H
#define _TKOM__INTERPRETER_RETURNSTATEMENTNODE_H

// return_statement = "return" , [expression] , ";" ;
class ReturnStatementNode : public Node {
    std::unique_ptr<ExpressionNode> returnExpression;
public:
    void setReturnExpression(std::unique_ptr<ExpressionNode> returnExpression) {
        this->returnExpression = std::move(returnExpression);
    }

    std::string toString() {
        return "RETURN_STATEMENT";
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        std::cout << toString() << std::endl;
        if (returnExpression != nullptr)
            returnExpression->print(depth + 1);
    };
};


#endif //_TKOM__INTERPRETER_RETURNSTATEMENTNODE_H
