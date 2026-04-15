cmake_minimum_required(VERSION 3.26)
project(LABA2)

set(CMAKE_CXX_STANDARD 20)

# main
add_executable(LABA2 main.cpp
        dynamicArray.h
        linkedList.h
        sequence.h
        arraySequence.h
        listSequence.h
        mutableArraySequence.h
        immutableArraySequence.h
        mutableListSequence.h
        immutableListSequence.h
        i_enumerator.h
        i_enumerable.h
        option.h
)

# Подключаем GoogleTest
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable( googletest )

enable_testing()

add_executable(
        tests
        tests/MutArraySequenceTest.cpp
        tests/ImmutArraySequenceTest.cpp
        tests/ImmutListSequenceTest.cpp
        tests/MutListSequenceTest.cpp
        tests/OptionTest.cpp
)

target_link_libraries(
        tests
        gtest_main
)

target_include_directories( tests PRIVATE ${CMAKE_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(tests)