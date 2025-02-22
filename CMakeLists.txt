cmake_minimum_required(VERSION 3.17)

project(tests C)
enable_testing()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(tests
  src/tests.c
  include/cvkm.h
  libs/flecs/flecs.c
  libs/flecs/flecs.h
  libs/munit/munit.c
  libs/munit/munit.h
)
add_test(NAME tests COMMAND tests)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
  target_link_libraries(tests PRIVATE ${MATH_LIBRARY})
endif()

# Because we don't control those.
set(VKM_DISABLE_WARNINGS_LIST
  libs/flecs/flecs.c
  libs/flecs/flecs.h
)

if(MSVC)
  target_compile_options(tests PRIVATE /W4 /WX)
  set_source_files_properties(${VKM_DISABLE_WARNINGS_LIST} PROPERTIES COMPILE_FLAGS /W0)
  target_link_libraries(tests PRIVATE ws2_32)
else()
  target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
  set_source_files_properties(${VKM_DISABLE_WARNINGS_LIST} PROPERTIES COMPILE_FLAGS -w)
  target_compile_definitions(tests PRIVATE MUNIT_NO_FORK)
endif()
target_compile_definitions(tests PRIVATE VKM_ENABLE_FLECS)

target_include_directories(tests PRIVATE include libs/munit libs/flecs)
