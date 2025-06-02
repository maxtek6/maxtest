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

function(maxtest_add_executable TARGET_NAME)
    add_executable(${TARGET_NAME} ${ARGN})
    target_link_libraries(${TARGET_NAME} PRIVATE Maxtest::Maxtest)
endfunction()

function(maxtest_add_test TARGET_NAME TEST_NAME)
    add_test(NAME ${TEST_NAME} COMMAND ${TARGET_NAME} ${TEST_NAME} ${ARGN})
endfunction()

if(MAXTEST_TESTS)
    add_subdirectory(tests)
endif()