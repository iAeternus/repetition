#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "test_functions.h"
#include "test_utils.h"
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
    test("build_vector", test_build_vector);
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
    test("b2u", test_b2u);
    test("b2t", test_b2t);
    test("t2u", test_t2u);
    test("u2t", test_u2t);
    test("u_max", test_u_max);
    test("u_min", test_u_min);
    test("t_max", test_t_max);
    test("t_min", test_t_min);
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
    assert(tag == true);
    assert(res == 0b0101); // 5
}

void test_u_add_ok() {
    // Given
    U a = UINT_MAX;
    U b = 1;
    U c = 100;
    U d = 200;

    // When
    bool res1 = u_add_ok(a, b); // 溢出
    bool res2 = u_add_ok(c, d); // 正常

    // Then
    printf("%d + %d = %d\t%s\n", a, b, a + b, res1 ? "normal" : "overflow");
    printf("%d + %d = %d\t%s\n", c, d, c + d, res2 ? "normal" : "overflow");
}

void test_u_inv() {
    // Given
    const int n = 5;
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

void test_t_add() {
    // Given
    const int n = 5;
    S x[] = {-8, -8, -8, 2, 5};
    S y[] = {-5, -8, 5, 5, 5};
    U w = 4;
    S res1[n], res2[n];
    overflow_type_enum types[n];
    
    // When
    for(int i = 0; i < 5; ++i) {
        res1[i] = x[i] + y[i];
        types[i] = t_add(x[i], y[i], w, &res2[i]);
    }

    // Then
    for(int i = 0; i < 5; ++i) {
        printf("%d\t%d\t%s\n", res1[i], res2[i], to_string(types[i]));
    }
}

void test_t_add_ok() {
    // Given
    S a = INT_MAX;
    S b = 1;
    S c = 100;
    S d = 200;
    S e = INT_MIN;
    S f = -1;

    // When
    bool res1 = t_add_ok(a, b); // 正溢出
    bool res2 = t_add_ok(c, d); // 正常
    bool res3 = t_add_ok(e, f); // 负溢出

    // Then
    printf("%d + %d = %d\t%s\n", a, b, a + b, res1 ? "normal" : "overflow");
    printf("%d + %d = %d\t\t\t%s\n", c, d, c + d, res2 ? "normal" : "overflow");
    printf("%d + %d = %d\t%s\n", e, f, e + f, res3 ? "normal" : "overflow");
}

void test_operations() {
    test("u_add", test_u_add);
    test("u_add_ok", test_u_add_ok);
    test("u_inv", test_u_inv);
    test("t_add", test_t_add);
    test("t_add_ok", test_t_add_ok);
}