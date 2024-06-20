FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(mystring ${SRC})
target_include_directories(mystring PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})