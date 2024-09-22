cmake_minimum_required(VERSION 3.10)
project(MarkdownCompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(md_compiler
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
)