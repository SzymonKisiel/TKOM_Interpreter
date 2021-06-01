cmake_minimum_required(VERSION 3.19)
project(_TKOM__Interpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(_TKOM__Interpreter main.cpp lexer/Source.cpp lexer/Source.h lexer/Lexer.cpp lexer/Lexer.h lexer/Token.cpp lexer/Token.h parser/Parser.cpp parser/Parser.h parser/Node.cpp parser/Node.h lexer/StringSource.cpp lexer/StringSource.h lexer/FileSource.cpp lexer/FileSource.h)