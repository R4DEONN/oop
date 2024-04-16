include(AddCatch2)

add_executable(tests CalculatorTest.cpp)
target_link_libraries(tests PRIVATE calculator Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)

add_custom_target(run_tests
        COMMAND tests
        DEPENDS tests
)