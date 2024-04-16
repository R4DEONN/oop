FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(calculator ${SRC})
target_include_directories(calculator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})