cmake_minimum_required(VERSION 3.20)
project(LABA3)

set(CMAKE_CXX_STANDARD 20)

# ===================== GoogleTest =====================

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# ===================== MAIN APP =====================

add_executable(LABA3
        main.cpp
)

# чтобы хедеры нормально находились
target_include_directories(LABA3 PRIVATE ${CMAKE_SOURCE_DIR})

# ===================== TESTS =====================

add_executable(tests
        tests/test_rect_matrix.cpp
        tests/test_square_matrix.cpp
        tests/test_triangle_matrix.cpp
        tests/test_diagonal_matrix.cpp
        tests/test_sparse_matrix.cpp
        tests/test_vector.cpp
)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(tests
        gtest
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)