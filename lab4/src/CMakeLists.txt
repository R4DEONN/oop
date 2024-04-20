FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(canvas ${SRC})
target_include_directories(canvas PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})