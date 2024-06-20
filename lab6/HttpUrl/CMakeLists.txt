cmake_minimum_required(VERSION 3.26)
project(HttpUrlApp)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH "bin")

add_subdirectory(src)

add_executable(HttpUrlApp main.cpp)

target_link_libraries(HttpUrlApp PRIVATE httpurl)

add_subdirectory(test)

add_dependencies(HttpUrlApp run_tests)