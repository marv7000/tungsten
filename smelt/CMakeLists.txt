cmake_minimum_required(VERSION 3.26)
project(smelt C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(smelt 
    src/main.cpp 
    src/project.cpp
    src/config.cpp
)
target_include_directories(smelt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# LLVM
target_include_directories(smelt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext/llvm-project/llvm/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/llvm-project/llvm)

llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(smelt ${llvm_libs})
find_package(LLVM REQUIRED CONFIG)
