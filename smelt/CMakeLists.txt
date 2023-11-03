cmake_minimum_required(VERSION 3.26)
project(smelt)

set(CMAKE_CXX_STANDARD 20)

add_executable(smelt 
    src/main.cpp 
    src/project.cpp
    src/config.cpp
)
target_include_directories(smelt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# LLVM
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/llvm-project/llvm)
target_include_directories(smelt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext/llvm-project/llvm/include)
target_link_libraries(smelt PUBLIC LLVM)