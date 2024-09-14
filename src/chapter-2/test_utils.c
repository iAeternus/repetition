#include <stdio.h>
#include <time.h>

#include "test_utils.h"

void test_with_time(const char* msg, test_function func) {
    printf(GREEN_COLOR "[%s]" DEFAULT_COLOR "\n", msg);
    clock_t start, end;
    double cpu_time_used;
    int sum = 0;

    start = clock();
    func();
    end = clock();

    cpu_time_used = ((double) (end - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf(GREEN_COLOR "[time] %.6f ms\n" DEFAULT_COLOR, cpu_time_used);
    putchar('\n');
}

void test(const char* msg, test_function func) {
    printf(GREEN_COLOR "[%s]" DEFAULT_COLOR "\n", msg);
    func();
    putchar('\n');
}