cmake_minimum_required(VERSION 3.26)
project(smelt C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(smelt 
        src/main.cpp
        src/project.cpp
        src/config.cpp
        src/lexer.cpp
        src/parser.cpp
        src/ast/integer_node.cpp
        src/ast/namespace_node.cpp
)
target_include_directories(smelt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Windows
if(WIN32)
    target_compile_definitions(smelt PRIVATE SM_WIN32)
elseif(UNIX)
    target_compile_definitions(smelt PRIVATE SM_LINUX)
endif()

# LLVM
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/llvm-project/llvm)
llvm_map_components_to_libnames(llvm_libs support core ir)
target_link_libraries(smelt ${llvm_libs})
message(FATAL_ERROR "${LLVM_AVAILABLE_LIBS}")
target_include_directories(smelt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext/llvm-project/llvm/include)