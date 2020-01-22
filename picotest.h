#ifndef PICOTEST_H_
#define PICOTEST_H_

#include <stdio.h>

#define DEF_TEST(x)         static void x##__test(char **err, char **file, int *line)
#define ASSERT(cond)        do {if (!(cond)) {*err = #cond; *file = __FILE__, *line = __LINE__; return;}} while (0)
#define DEF_SUITE(name)     void name##__suite(int *passes, int *failures)
#define RUN_TEST(func)      do {char *err = NULL, *file; int line; func##__test(&err, &file, &line); if (err) {++*failures; printf("  FAIL %s '%s' (%s:%i)\n", #func, err, file, line);} else {++*passes; puts("  PASS " #func);}} while(0)
#define IMPORT_SUITE(name)  extern void name##__suite(int*, int*)
#define BEGIN_TESTS()       int passes = 0; int failures = 0; do ; while(0)
#define RUN_SUITE(name)     do {puts(#name); name##__suite(&passes, &failures);} while (0)

#endif


