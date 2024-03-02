#include <picotest/picotest.h>

static int len(const char *s)
{
    int len = 0;
    while (*s++)
        ++len;

    return len;
}

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
