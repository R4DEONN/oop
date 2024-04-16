cmake_minimum_required(VERSION 3.26)
project(ex2)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_subdirectory(src)

add_executable(CalculatorApp main.cpp)
target_link_libraries(CalculatorApp PRIVATE calculator)

add_subdirectory(test)

# Добавьте зависимость сборки от цели запуска тестов
add_dependencies(CalculatorApp run_tests)