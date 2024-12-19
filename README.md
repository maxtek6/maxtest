# Maxtest

Simple unit testing framework for C/C++ and CMake. This project was 
created due to the significant overlap in the unit testing code for
our existing C and C++ projects.

This is not meant to be a replacement for GTest or any other widely
used testing framework. It lacks support for benchmarking, mocking,
and other features that would be useful for a complex project. This
framework is most useful for developers who want to bootstrap simple
unit tests to establish test coverage in their projects.

## Requirements

+ C++11
+ CMake >= 3.10

## Basic Usage

A basic unit test file should be written as follows:

```c++
#include <maxtest.hpp>

// any additional classes or functions here

MAXTEST_MAIN
{
    MAXTEST_TEST_CASE(test_name)
    {
        const int n(5);
        MAXTEST_ASSERT(n > 0);  
    };
}
```

There are 3 macros defined by the `maxtest.hpp` header:

+ `MAXTEST_ASSERT(COND)`: assert the result of a boolean expression. If
the evaluated expression is `false`, the test will fail.
+ `MAXTEST_TEST_CASE(NAME)`: defines a single test case to be run. By
default, a test case will always pass unless one of the assertions
invoked by `MAXTEST_ASSERT` fails.
+ `MAXTEST_MAIN`: indicates the start of the block where the test cases
will be defined. All test cases must be declared in this block. No other
classes or functions can be declared in this block.
+ Note that any calls to the functions in the `maxtest` namespace may be
legal, but they are not recommended and their behavior is undefined.

## Integration with CMake

Maxtest can be integrated as a git submodule or imported via `FetchContent`:
```cmake
FetchContent_Declare(
    Maxtest
    GIT_REPOSITORY https://github.com/maxtek6/maxtest.git
    GIT_TAG master
)
FetchContent_MakeAvailable(Maxtest)
```

Once the package has been imported, an executable can be created using the
targets. Assume the file `main.cpp` has the example code from above:

```cmake
maxtest_add_target(unittest main.cpp)
```

Using the `maxtest_add_test` command, declare each test name as declared in
the source file using `MAXTEST_TEST_CASE`:

```cmake
# "" represents any additional args passed when the test is run
maxtest_add_test(unittest test_name "")
```

## Roadmap

+ Test coverage using `gcovr`
+ Improved CMake functions