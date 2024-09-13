#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_functions.h"
#include "convert.h"
#include "operations.h"

void test_build_vector() {
    // Given
    int w_x = 8, w_y = 9, w_z = 10;
    B_VEC x, y, z;

    // When
    build_vector(0b11010010, w_x, &x);
    build_vector(0b011010010, w_y, &y);
    build_vector(0b1011010010, w_z, &z);
    
    // Then
    print_vector(x, w_x);
    print_vector(y, w_y);
    print_vector(z, w_z);

    // Final
    destroy_vector(&x);
    destroy_vector(&y);
    destroy_vector(&z);
}

void test_utils() {
    test_build_vector();
}

void test_b2u() {
    // Given
    B_VEC x;
    U w = 8;
    build_vector(0b11010010, w, &x);

    // When
    U res = b2u(x, w);

    // Then
    printf("%u\n", res);
    assert(res == 210);

    // Final
    destroy_vector(&x);
}

void test_b2t() {
    // Given
    B_VEC x;
    U w = 8;
    build_vector(0b11010010, w, &x);

    // When
    S res = b2t(x, w);

    // Then
    printf("%d\n", res);
    assert(res == -46);

    // Final
    destroy_vector(&x);
}

void test_t2u() {
    // Given
    S x = -46; // 补码：0b 1101 0010
    U w = 8;

    // When
    U res = t2u(x, w);

    // Then
    printf("%u\n", res);
    assert(res == 0b11010010);
}

void test_u2t() {
    // Given
    U u = 0b11010010; // 210
    U w = 8;

    // When
    S res = u2t(u, w);

    // Then
    printf("%d\n", res);
    assert(res == -46);
}

void test_u_max() {
    // Given
    U w = 8;

    // When
    U res = u_max(w);

    // Then
    printf("%u\n", res);
    assert(res == 255);
}

void test_u_min() {
    // Given
    U w = 8;

    // When
    U res = u_min(w);

    // Then
    printf("%u\n", res);
    assert(res == 0);
}

void test_t_max() {
    // Given
    U w = 8;

    // When
    U res = t_max(w);

    // Then
    printf("%d\n", res);
    assert(res == 127);
}

void test_t_min() {
    // Given
    U w = 8;

    // When
    U res = t_min(w);

    // Then
    printf("%d\n", res);
    assert(res == -128);
}

void test_convert() {
    test_b2u();
    test_b2t();
    test_t2u();
    test_u2t();
    test_u_max();
    test_u_min();
    test_t_max();
    test_t_min();
}

void test_u_add() {
    // Given
    U x = 0b1001;
    U y = 0b1100;
    U w = 4;
    U res;

    // When
    bool tag = u_add(x, y, w, &res);

    // Then
    printf("%d + %d = %d %s\n", x, y, res, tag ? "overflow" : "normal");
    assert(tag == is_u_add_overflows(x, y, w)); // true
    assert(res == 0b0101); // 5
}

void test_u_inv() {
    // Given
    int n = 5;
    U x[] = {0x0, 0x5, 0x8, 0xD, 0xF};
    U w = 4;
    U res[n];

    // When
    for(int i = 0; i < n; ++i) {
        res[i] = u_inv(x[i], w);
    }

    // Then
    print_arr(res, n, sizeof(U), print_unsigned_int);
    print_arr(res, n, sizeof(U), print_big_hex);
}

void test_operations() {
    test_u_add();
    test_u_inv();
}