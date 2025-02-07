cmake_minimum_required(VERSION 3.17)

project(tests C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(tests
  src/tests.c
  include/cvkm.h
  libs/munit/munit.c
  libs/munit/munit.h
)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
  target_link_libraries(tests PUBLIC ${MATH_LIBRARY})
endif()

target_include_directories(tests PRIVATE include libs/flecs libs/munit)
target_compile_definitions(tests PRIVATE MUNIT_NO_FORK)
