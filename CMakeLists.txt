cmake_minimum_required(VERSION 3.10)

project(maxtest)

include(GNUInstallDirs)

option(MAXTEST_CTEST_INIT "Initialize CTest from this directory" ON)
option(MAXTEST_TESTS "Build tests" OFF)

add_library(maxtest INTERFACE)
target_include_directories(maxtest INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(
    TARGETS maxtest
    EXPORT MaxtestTargets
)

# Export targets to build tree for FetchContent
export(
    TARGETS maxtest
    NAMESPACE maxtest::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/MaxtestTargets.cmake"
)

install(
    FILES maxtest.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT MaxtestTargets
    FILE MaxtestTargets.cmake
    NAMESPACE maxtest::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/maxtest
)

# Create config file for build tree (FetchContent)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/maxtestConfig.cmake"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/MaxtestTargets.cmake\")\n"
)

# Create config file for install tree
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/maxtestConfig-install.cmake"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/MaxtestTargets.cmake\")\n"
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/maxtestConfig-install.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/maxtest
    RENAME maxtestConfig.cmake
)

if(MAXTEST_CTEST_INIT)
    include(CTest)
    enable_testing()
endif()

set(CTEST_OUTPUT_ON_FAILURE ON)

function(maxtest_add_executable TARGET_NAME)
    add_executable(${TARGET_NAME} ${ARGN})
    target_link_libraries(${TARGET_NAME} PRIVATE maxtest)
endfunction()

function(maxtest_add_test TARGET_NAME TEST_NAME)
    add_test(NAME ${TEST_NAME} COMMAND ${TARGET_NAME} ${TEST_NAME} ${ARGN})
endfunction()

if(MAXTEST_TESTS)
    add_subdirectory(tests)
endif()