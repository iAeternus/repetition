#include <stdio.h>
#include <stdlib.h>

#include "floating_number.h"
#include "utils.h"

void build_floating_number(floating_number* p_num, size k, size n, size len, bit* bits) {
    if(bits == NULL || len == 0) {
        return;
    }

    p_num->s = bits[0];
    p_num->k = k;
    p_num->n = n;
    p_num->len = len;
    p_num->exp = (bit*)malloc(sizeof(bit) * (p_num->k + 1));
    assert_not_null(p_num->exp, NULL);
    p_num->frac = (bit*)malloc(sizeof(bit) * (p_num->n + 1));
    assert_not_null(p_num->frac, NULL);

    for(int i = 0; i < p_num->k; ++i) {
        p_num->exp[i] = bits[i + 1];
    }
    p_num->exp[p_num->k] = '\0';

    for(int i = 0; i < p_num->n; ++i) {
        p_num->frac[i] = bits[i + 1 + p_num->k];
    }
    p_num->frac[p_num->n] = '\0';
}

void build_32(floating_number* p_num, bit* bits) {
    build_floating_number(p_num, 8, 23, 32, bits);
}

void build_64(floating_number* p_num, bit* bits) {
    build_floating_number(p_num, 11, 52, 64, bits);
}

void build_with_float(floating_number* p_num, float f) {
    build_32(p_num, float_to_binary_string(f));
}

void build_with_double(floating_number* p_num, double d) {
    build_64(p_num, double_to_binary_string(d));
}

void destroy_floating_number(floating_number* p_num) {
    if(p_num->exp) {
        free(p_num->exp);
        p_num->exp = NULL;
    }
    if(p_num->frac) {
        free(p_num->frac);
        p_num->frac = NULL;
    }
}

void print_bit(const void* elem) {
    printf("%c", *(const bit*)elem);
}

void print_floating_number(const floating_number* p_num) {
    print_bit(&p_num->s);
    putchar(' ');
    for(size i = 0; i < p_num->k; ++i) {
        print_bit(&p_num->exp[i]);
    }
    putchar(' ');
    for(size i = 0; i < p_num->n; ++i) {
        print_bit(&p_num->frac[i]);
    }
    putchar('\n');
}

floating_number_type_enum get_type(const floating_number* p_num) {
    // 规格化数，阶码既不全为 0，也不全为 1
    if(!is_string_all_zero(p_num->exp, p_num->k) && !is_string_all_one(p_num->exp, p_num->k)) {
        return NORMALIZED;
    }
    // 非规格化数，阶码为全 0
    if(is_string_all_zero(p_num->exp, p_num->k)) {
        return UNNORMALIZED;
    }

    // 特殊值，阶码全为 1
    if(is_string_all_one(p_num->exp, p_num->k)) {
        // 尾数全为 0，无穷
        if(is_string_all_zero(p_num->frac, p_num->n)) {
            return p_num->s == '1' ? NEGATIVE_INFINITY : POSITIVE_INFINITY;
        } else {
            // 尾数不全为 0，NaN
            return NAN;
        }
    }
}