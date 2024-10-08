#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

// utils.h
void test_build_vector();
void test_utils();

// convert.h
void test_b2u();
void test_b2t();
void test_t2u();
void test_u2t();
void test_u_max();
void test_u_min();
void test_t_max();
void test_t_min();
void test_convert();

// operations.h
void test_u_add();
void test_u_add_ok();
void test_u_inv();
void test_t_add();
void test_t_add_ok();
void test_t_inv();
void test_u_mul();
void test_t_mul();
void test_operations();

// floating_number.h
void test_build_floating_number();
void test_build_with_float();
void test_build_with_double();
void test_get_type();
void test_floating_number();

#endif // TEST_FUNCTIONS_H