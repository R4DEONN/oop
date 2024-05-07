FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(date ${SRC})
target_include_directories(date PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})