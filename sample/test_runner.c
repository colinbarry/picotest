#include "../picotest.h"
#include <stdlib.h>

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

