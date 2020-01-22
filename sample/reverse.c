#include "../picotest.h"
#include <stdlib.h>

static void reverse(int *arr, int len)
{
    int half = len / 2;
    int i;

    for (i = 0; i < half; ++i) {
        int temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }
}

DEF_TEST(reverses_an_array_of_length_1)
{
    int *arr = malloc(sizeof(int) * 1);
    arr[0] = 23;
    
    reverse(arr, 1);

    ASSERT(arr[0] == 23);
}

DEF_TEST(reverses_a_large_array)
{
    const int size = 10;
    int i;
    int *arr = malloc(sizeof(int) * size);
    
    for (i = 0; i < size; ++i)
        arr[i] = i;

    reverse(arr, size);

    for (i = 0; i < size; ++i)
        ASSERT(arr[i] == size - 1 - i);
}

DEF_SUITE(reverse)
{
    RUN_TEST(reverses_an_array_of_length_1);
    RUN_TEST(reverses_a_large_array);
}
