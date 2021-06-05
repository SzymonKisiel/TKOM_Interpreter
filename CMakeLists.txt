cmake_minimum_required(VERSION 3.19)
project(_TKOM__Interpreter)

set(CMAKE_CXX_STANDARD 20)

include_directories(parser/ast)

add_executable(_TKOM__Interpreter main.cpp parser/ast/Node.h lexer/Source.cpp lexer/Source.h lexer/Lexer.cpp lexer/Lexer.h lexer/Token.cpp lexer/Token.h parser/Parser.h parser/ast/TestNode.h lexer/StringSource.cpp lexer/StringSource.h lexer/FileSource.cpp lexer/FileSource.h parser/ast/DeclarationNode.h parser/ast/ProgramNode.h parser/ast/StatementNode.h parser/ast/FunctionNode.h parser/ast/ExpressionNode.h parser/ast/AddExpresionNode.h parser/ast/MultExpressionNode.h parser/ast/FactorNode.h parser/ast/SimpleStatementNode.h parser/ast/AssignmentNode.h parser/ast/FunctionCallNode.h parser/ast/ReturnStatementNode.h parser/ast/ArgumentsNode.h parser/ast/ParametersNode.h)