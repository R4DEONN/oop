FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(httpurl ${SRC})
target_include_directories(httpurl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})