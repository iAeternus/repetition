#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/**
 * 断言指针不为空
 * 若指针为空则打印信息结束程序，否则什么都不做
 * @par ptr 指针
 * @par msg 信息
 */
void assert_not_null(void* ptr, const char* msg) {
    if(!ptr) {
        if(msg) {
            puts(msg);
        }
        exit(EXIT_FAILURE);
    }
}

void build_vector(S num, U w, B_VEC* x) {
    *x = (B_VEC)malloc(sizeof(U) * w);
    assert_not_null(*x, NULL);

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

char* float_to_binary_string(float f) {
    char* binary_str = (char*)malloc(33 * sizeof(char));
    assert_not_null(binary_str, NULL);

    unsigned char* f_bytes = (unsigned char*)&f;
    memset(binary_str, '0', 32);
    binary_str[32] = '\0';

    for (int i = 0; i < sizeof(float); ++i) {
        for (int j = 0; j < 8; ++j) {
            int bit_index = 31 - (i * 8 + j);
            if (f_bytes[i] & (1 << j)) {
                binary_str[bit_index] = '1';
            }
        }
    }

    return binary_str;
}

char* double_to_binary_string(double d) {
    char* binary_str = (char*)malloc(65 * sizeof(char));
    assert_not_null(binary_str, NULL);

    unsigned char* d_bytes = (unsigned char*)&d;

    memset(binary_str, '0', 64);
    binary_str[64] = '\0';

    for (int i = 0; i < sizeof(double); ++i) {
        for (int j = 0; j < 8; ++j) {
            int bit_index = 63 - (i * 8 + j);
            if (d_bytes[i] & (1 << j)) {
                binary_str[bit_index] = '1';
            }
        }
    }

    return binary_str;
}

bool is_string_all_zero(const char* str, U len) {
    if(!str || len == 0) {
        return true;
    }

    for(U i = 0; i < len; ++i) {
        if(str[i] != '0') {
            return false;
        }
    }
    return true;
}

bool is_string_all_one(const char* str, U len) {
    if(!str || len == 0) {
        return true;
    }

    for(U i = 0; i < len; ++i) {
        if(str[i] != '1') {
            return false;
        }
    }
    return true;
}