set(SRC_TESTS
    ./client_tests.cpp
)

add_executable(unit_tests ${SRC_TESTS})

target_link_libraries(unit_tests
    criterion
    gcov
)

target_compile_options(unit_tests PRIVATE
    -std=c++20
    --coverage
)

target_link_options(unit_tests PRIVATE --coverage)
