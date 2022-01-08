cmake_minimum_required(VERSION 3.19)
project(CatchTest)

set(CMAKE_CXX_STANDARD 20)
set(GCC_COVERAGE_COMPILE_FLAGS "-fconcepts -Wa,-mbig-obj ")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

file(GLOB_RECURSE SOURCES
        exception/*.h
        exception/*.cpp

        lexer/*.h
        lexer/*.cpp

        parser/*.h
        parser/*.cpp

        execution/*.h
        execution/*.cpp

        structures/*.h
        structures/*.cpp

        PARENT_SCOPE
        )
add_executable(TKOM_Interpreter main.cpp ${SOURCES})
add_subdirectory(tests)