# Picotest

Picotest is a minimal C89 unit test framework, consisting of a single header file that defines 7 macros.

## Installation

The recommended way to incorporate Picotest is using modern CMake with `FetchContent`.

You should add the following configuration to your `CMakeLists.txt` to download
the package and enable testing in your project:

```cmake
include(FetchContent)
option(ENABLE_TESTING "Enable the tests" ON) 
if (ENABLE_TESTING AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    FetchContent_Declare(
        Picotest
        GIT_REPOSITORY https://github.com/colinbarry/picotest
        GIT_TAG main)
    FetchContent_MakeAvailable(Picotest)

    enable_testing()
endif()
```

Picotest can then be included with the following `#include` directive:

```c
#include <picotest/picotest.h>
```

Alternatively, if your project doesn't use CMake, simply copy the header
file `picotest.h` to an appropriate location and include it. Picotest has no
other dependencies and so can be safely deployed by copying the header.

## Usage

A test is a function containing one or more ASSERT statements. If all such statements evaluate to true, the test has passed. Tests are grouped into suites, where each suite will evaluate the behaviour of one component of your code. Each suite must be defined entirely in a single .c file (although .c files can contain multiple suites.)

`DEF_TEST(test_name)` prologue that defines a test function.

`ASSERT(cond)` `cond` must evaluate to true for the test to have passed. If any `cond`s evaluate to false, the test function is said to have failed.

`DEF_SUITE(suite_name)` defines a suite of tests.

`RUN_TEST(test_name)` must appear in the body of a DEF_SUITE. It runs the test of the given name.

```c
DEF_TEST(returns_length_of_a_string)
{
    ASSERT(len("alfa") == 4);
    ASSERT(len("bravo") == 5);
    ASSERT(len("charlie") == 7);
}

DEF_TEST(returns_length_of_an_empty_string)
{
    ASSERT(len("") == 0);
}

DEF_SUITE(strlen)
{
    RUN_TEST(returns_length_of_a_string);
    RUN_TEST(returns_length_of_an_empty_string);
}
```

A test runner is required to run the test suites.

`IMPORT_SUITE(suite_name)` imports the suite of the given name into the test runner scope.

`BEGIN_TESTS()` must be called to initialise the test run (and to declare the `passes` and `failures` variables.)

`RUN_SUITE(suite_name)` executes the given suite, which must previously have been imported with `IMPORT_SUITE`. 

After all tests are runs, `passes` will contain the number of tests that have passed, and `failures` the number that have failed.

```c
IMPORT_SUITE(strlen);
IMPORT_SUITE(reverse);

int main(int argc, char **argv)
{
    BEGIN_TESTS();
    RUN_SUITE(strlen);
    RUN_SUITE(reverse);

    printf("\n%i PASSED\n%i FAILED\n", passes, failures);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
```

## Building the sample

The sample features two test suites, split between two test source files, and a
test runner file. The sample project is built with CMake, which can be invoked
with the following commands:

```bash
cmake -B ./build -DPICOTEST_BUILD_SAMPLE=ON
cmake --build ./build 
```

And then run the sample with:

```bash
./build/sample/sample
```
