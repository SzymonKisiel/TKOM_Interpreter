cmake_minimum_required(VERSION 3.19)
project(_TKOM__Interpreter)

set(CMAKE_CXX_STANDARD 20)

set(GCC_COVERAGE_COMPILE_FLAGS "-fconcepts")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(parser/ast)

add_executable(_TKOM__Interpreter main.cpp parser/ast/Node.h lexer/Source.cpp lexer/Source.h lexer/Lexer.cpp lexer/Lexer.h lexer/Token.cpp lexer/Token.h parser/Parser.h lexer/StringSource.cpp lexer/StringSource.h lexer/FileSource.cpp lexer/FileSource.h parser/ast/DeclarationNode.h parser/ast/ProgramNode.h parser/ast/StatementNode.h parser/ast/FunctionNode.h parser/ast/ExpressionNode.h parser/ast/AddExpressionNode.h parser/ast/MultExpressionNode.h parser/ast/FactorNode.h parser/ast/SimpleStatementNode.h parser/ast/AssignmentNode.h parser/ast/FunctionCallNode.h parser/ast/ReturnStatementNode.h parser/ast/ArgumentsNode.h parser/ast/ParametersNode.h exception/Exception.h exception/ParserException.h exception/LexerException.h structures/GeographicPosition.h structures/GeographicCoordinate.h execution/Context.cpp execution/Context.h exception/ExecutionException.h parser/ast/StatementNode.cpp parser/ast/IfStatementNode.cpp parser/ast/IfStatementNode.h parser/ast/WhileStatementNode.cpp parser/ast/WhileStatementNode.h parser/ast/SimpleStatementNode.cpp parser/ast/ReturnStatementNode.cpp parser/ast/ProgramNode.cpp parser/ast/MultExpressionNode.cpp parser/ast/FunctionNode.cpp parser/ast/FunctionCallNode.cpp parser/ast/FactorNode.cpp parser/ast/ExpressionNode.cpp parser/ast/DeclarationNode.cpp parser/ast/AssignmentNode.cpp parser/ast/ArgumentsNode.cpp parser/ast/AddExpressionNode.cpp parser/ast/ParametersNode.cpp execution/VisitCondition.h execution/VisitPrint.h execution/Function.h execution/PrintFunction.h structures/GeographicDistance.h execution/VisitCheckType.h)