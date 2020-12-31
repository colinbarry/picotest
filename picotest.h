/*
# Picotest

Picotest is a minimal C89 unit test framework, consisting of a single header
file that defines 7 macros.

## Usage

A test is a function containing one or more ASSERT statements. If all such
statements evaluate to true, the test has passed. Tests are grouped into
suites, where each suite will evaluate the behaviour of one component of your
code. Each suite must be defined entirely in a single .c file (although .c
files can contain multiple suites.)


`DEF_TEST(test_name)` prologue that defines a test function.

`ASSERT(cond)` `cond` must evaluate to true for the test to have passed. If
any `cond`s evaluate to false, the test function is said to have failed.

`DEF_SUITE(suite_name)` defines a suite of tests.

`RUN_TEST(test_name)` must appear in the body of a DEF_SUITE. It runs the test
of the given name.

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

`IMPORT_SUITE(suite_name)` imports the suite of the given name into the test
runner scope.

`BEGIN_TESTS()` must be called to initialise the test run (and to declare the
`passes` and `failures` variables.)

`RUN_SUITE(suite_name)` executes the given suite, which must previously have
been imported with `IMPORT_SUITE`. 

After all tests are runs, `passes` will contain the number of tests that have
passed, and `failures` the number that have failed.

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

LICENCE - see bottom of file for licence information.

*/


#ifndef PICOTEST_H_
#define PICOTEST_H_

#include <stdio.h>

#define DEF_TEST(x)                                                           \
    static void x##__test(char **err, char **file, int *line)

#define ASSERT(cond)                                                          \
    do {                                                                      \
        if (!(cond)) {                                                        \
            *err = #cond; *file = __FILE__, *line = __LINE__;                 \
            return;                                                           \
        }                                                                     \
    } while (0)

#define DEF_SUITE(name)                                                       \
    void name##__suite(int *passes, int *failures)

#define RUN_TEST(func)                                                        \
    do {                                                                      \
        char *err = NULL, *file;                                              \
        int line;                                                             \
        func##__test(&err, &file, &line);                                     \
        if (err) {                                                            \
            ++*failures;                                                      \
            printf("  FAIL %s '%s' (%s:%i)\n", #func, err, file, line);       \
        } else {                                                              \
            ++*passes; puts("  PASS " #func);                                 \
        }                                                                     \
    } while(0)

#define IMPORT_SUITE(name)                                                    \
    extern void name##__suite(int*, int*)

#define BEGIN_TESTS()                                                         \
    int passes = 0; int failures = 0; do ; while(0)

#define RUN_SUITE(name)                                                       \
    do {puts(#name); name##__suite(&passes, &failures);} while (0)

#endif

/*
MIT License

Copyright (c) 2020 Colin Barry

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
