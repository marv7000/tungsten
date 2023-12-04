cmake_minimum_required(VERSION 3.26)
project(smelt C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(smelt 
        src/main.cpp
        src/project.cpp
        src/config.cpp
        src/lexer.cpp
        src/parser.cpp
        src/ast/literal_expr.cpp
        src/code.cpp
        src/ast/struct_node.cpp
        src/ast/function_node.cpp
        src/ast/call_expr.cpp
        src/ast/binary_expr.cpp
        src/ast/variable_expr.cpp
        src/ast/prototype_node.cpp
        src/ast/iexpr.cpp
        src/ast/block_expr.cpp
        include/parser_position.h
        src/parser_position.cpp
        src/ast/type.cpp
        src/ast/int_literal_expr.cpp
        include/ast/int_literal_expr.h
        src/ast/return_expr.cpp
        include/ast/return_expr.h
        src/ast/string_literal_expr.cpp
        include/ast/string_literal_expr.h
)
target_include_directories(smelt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

# Windows
if(WIN32)
    target_compile_definitions(smelt PRIVATE SM_WIN32)
elseif(UNIX)
    target_compile_definitions(smelt PRIVATE SM_LINUX)
endif()

# LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
llvm_config(smelt USE_SHARED support core irreader)