cmake_minimum_required(VERSION 3.26)
project(StringListApp)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH "bin")

add_subdirectory(src)

add_executable(StringListApp main.cpp)

target_link_libraries(StringListApp PRIVATE stringlist)

add_subdirectory(test)

add_dependencies(StringListApp run_tests)