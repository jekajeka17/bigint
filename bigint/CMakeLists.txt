cmake_minimum_required(VERSION 2.8)

project(BIGINT)

include_directories(${BIGINT_SOURCE_DIR})

add_executable(
        big_integer_tmp
        big_integer.h
        big_integer_arithmetic.cpp
        big_integer_private.cpp
        big_integer_ctors.cpp
        big_integer_commons.cpp
        big_integer_cmp.cpp
        main.cpp
)

add_executable(
        big_integer_testing
        big_integer_testing.cpp
        big_integer.h
        big_integer_arithmetic.cpp
        big_integer_private.cpp
        big_integer_ctors.cpp
        big_integer_commons.cpp
        big_integer_cmp.cpp
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc main.cpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(big_integer_testing -lgmp -lgmpxx -lpthread)
