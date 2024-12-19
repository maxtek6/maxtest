cmake_minimum_required(VERSION 3.10)

project(maxtest)

option(MAXTEST_CTEST_INIT "Initialize CTest from this directory" ON)
option(MAXTEST_TESTS "Build tests" OFF)

add_library(maxtest INTERFACE)
target_include_directories(maxtest INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_library(Maxtest::Maxtest ALIAS maxtest)

if(MAXTEST_CTEST_INIT)
  include(CTest)
  enable_testing()
endif()

set(CTEST_OUTPUT_ON_FAILURE ON)

function(maxtest_add_target name sources)
  add_executable(${name} ${sources})
  target_link_libraries(${name} PRIVATE Maxtest::Maxtest)
endfunction(maxtest_add_target)

function(maxtest_add_test target name args)
    add_test(NAME ${name} COMMAND ${target} ${name} ${args})
endfunction(maxtest_add_test)

if(MAXTEST_TESTS)
  add_subdirectory(tests)
endif()