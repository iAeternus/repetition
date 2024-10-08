#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "unit_tests.h"
#include "test_utils.h"
#include "convert.h"
#include "operations.h"
#include "floating_number.h"

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
    const int N = 5;
    U x[] = {0x0, 0x5, 0x8, 0xD, 0xF};
    U w = 4;
    U res[N];

    // When
    for(int i = 0; i < N; ++i) {
        res[i] = u_inv(x[i], w);
    }

    // Then
    print_arr(res, N, sizeof(U), print_unsigned_int);
    print_arr(res, N, sizeof(U), print_big_hex);
}

void test_t_add() {
    // Given
    const int N = 5;
    S x[] = {-8, -8, -8, 2, 5};
    S y[] = {-5, -8, 5, 5, 5};
    U w = 4;
    S res1[N], res2[N];
    overflow_type_enum types[N];
    
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

void test_t_inv() {
    // Given
    const int N = 5;
    S x[] = {0x0, 0x5, 0x8, 0xD, 0xF};
    U w = 4;
    S res[N];

    // When
    for(int i = 0; i < N; ++i) {
        res[i] = t_inv(x[i], w);
    }

    // Then
    print_arr(x, N, sizeof(S), print_signed_int);
    print_arr(res, N, sizeof(S), print_signed_int);
    print_arr(res, N, sizeof(S), print_big_hex);
}

void test_u_mul() {
    // Given
    const int N = 3;
    U x[] = {5, 4, 3};
    U y[] = {3, 7, 3};
    U w = 3;
    U res1[N], res2[N];

    // When
    for(int i = 0; i < N; ++i) {
        res1[i] = x[i] * y[i];
        res2[i] = u_mul(x[i], y[i], w);
    }

    // Then
    print_arr(res1, N, sizeof(U), print_unsigned_int);
    print_arr(res2, N, sizeof(U), print_unsigned_int);
}

void test_t_mul() {
    // Given
    const int N = 3;
    S x[] = {-3, -4, 3};
    S y[] = {3, -1, 3};
    U w = 3;
    S res1[N], res2[N];

    // When
    for(int i = 0; i < N; ++i) {
        res1[i] = x[i] * y[i];
        res2[i] = t_mul(x[i], y[i], w);
    }

    // Then
    print_arr(res1, N, sizeof(S), print_signed_int);
    print_arr(res2, N, sizeof(S), print_signed_int);
}

void test_operations() {
    test("u_add", test_u_add);
    test("u_add_ok", test_u_add_ok);
    test("u_inv", test_u_inv);
    test("t_add", test_t_add);
    test("t_add_ok", test_t_add_ok);
    test("t_inv", test_t_inv);
    test("u_mul", test_u_mul);
    test("t_mul", test_t_mul);
}

void test_build_floating_number() {
    // Given
    floating_number num;
    size k = 4;
    size n = 3;
    size len = 8;
    bit bits[] = "00110110";

    // When
    build_floating_number(&num, k, n, len, bits);

    // Then
    print_floating_number(&num);

    // Final
    destroy_floating_number(&num);
}

void test_build_with_float() {
    // Given
    floating_number num;
    float f = 3510593.0f;

    // When
    build_with_float(&num, f);

    // Then
    print_floating_number(&num);

    // Final
    destroy_floating_number(&num);
}

void test_build_with_double() {
    // Given
    floating_number num;
    double d = 3510593.0;

    // When
    build_with_double(&num, d);

    // Then
    print_floating_number(&num);

    // Final
    destroy_floating_number(&num);
}

void test_get_type() {
    // Given
    floating_number a, b, c, d, e;

    build_32(&a, "00111111110000000000000000000000"); // 1.5 规格化值
    build_32(&b, "00000000000000000000000000000001"); // 0.0000001192092896 非规格化值
    build_32(&c, "01111111100000000000000000000000"); // 正无穷
    build_32(&d, "11111111100000000000000000000000"); // 负无穷
    build_32(&e, "01111111101111111111111111111111"); // NaN

    // When
    floating_number_type_enum res1 = get_type(&a);
    floating_number_type_enum res2 = get_type(&b);
    floating_number_type_enum res3 = get_type(&c);
    floating_number_type_enum res4 = get_type(&d);
    floating_number_type_enum res5 = get_type(&e);

    // Then
    print_floating_number(&a);
    print_floating_number(&b);
    print_floating_number(&c);
    print_floating_number(&d);
    print_floating_number(&e);

    printf("%d %d %d %d %d\n", res1, res2, res3, res4, res5);
    
    assert(res1 == NORMALIZED);
    assert(res2 == UNNORMALIZED);
    assert(res3 == POSITIVE_INFINITY);
    assert(res4 == NEGATIVE_INFINITY);
    assert(res5 == NAN);

    // Final
    destroy_floating_number(&a);
    destroy_floating_number(&b);
    destroy_floating_number(&c);
    destroy_floating_number(&d);
    destroy_floating_number(&e);
}

void test_floating_number() {
    test("build_floating_number", test_build_floating_number);
    test("build_with_float", test_build_with_float);
    test("build_with_double", test_build_with_double);
    test("get_type", test_get_type);
}