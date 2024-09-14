#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void build_vector(S num, U w, B_VEC* x) {
    *x = (B_VEC)malloc(sizeof(U) * w);
    if (*x == NULL) {
        exit(EXIT_FAILURE);
    }

    U i;
    for (i = 0; i < w; ++i) {
        (*x)[i] = (num >> i) & 1;
    }
}

void destroy_vector(B_VEC* x) {
    free(*x);
    *x = NULL;
}

/**
 * 计算大于w的数中能整除n的最小的数
 */
static U exact_division(U w, U n) {
    for(U i = w + 1; ; ++i) {
        if(i % n == 0) {
            return i;
        }
    }
    return 0;
}

void print_vector(B_VEC x, U w) {
    // 打印前导0
    U max_len = exact_division(w, 4);
    U cover = max_len - w;
    if(cover < 4) {
        for(U i = 0; i < cover; ++i) {
            putchar('0');
        }
    }

    U idx = cover;
    for(U i = 0; i < w; ++i) {
        printf("%u", x[w - i - 1]);
        idx++;
        if(idx % 4 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}

void print_signed_int(const void* elem) {
    printf("%d ", *(const S*)elem);
}

void print_unsigned_int(const void* elem) {
    printf("%u ", *(const U*)elem);
}

void print_big_hex(const void* elem) {
    printf("0x%X ", *(const S*)elem);
}

void print_small_hex(const void* elem) {
    printf("0x%x ", *(const S*)elem);
}

void print_binary(const void* elem) {
    S num = *(const S*)elem;
    U mask = 1U << 31;
    for (int i = 31; i >= 0; --i) {
        U testBit = (U)num & mask;
        printf("%u", testBit ? 1 : 0);
        mask >>= 1;
    }
    putchar(' ');
}

void print_arr(const void* p_arr, const U size, const U elem_size, const elem_print_func func) {
    char* ptr = (char*) p_arr;
    for(U i = 0; i < size; ++i) {
        func(ptr);
        ptr += elem_size;
    }
    putchar('\n');
}

/**
 * 将溢出类型枚举转化为描述
 */
const char* to_string(overflow_type_enum type) {
    switch(type) {
    case POSITIVE_OVERFLOW:
        return "positive overflow";
    case NORMAL:
        return "normal";
    case NEGATIVE_OVERFLOW:
        return "negative overflow";
    default:
        puts("Incorrect type.");
        return NULL;
    }
}