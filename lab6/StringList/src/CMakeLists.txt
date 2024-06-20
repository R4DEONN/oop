FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(stringlist ${SRC})
target_include_directories(stringlist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})