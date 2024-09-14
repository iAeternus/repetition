#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

typedef unsigned int U;
typedef signed int S;

typedef U* B_VEC;

// 计算 2^n
#define POW_2(n) ((1) << (n))

/**
 * 断言指针不为空
 * 若指针为空则打印信息结束程序，否则什么都不做
 * @par ptr 指针
 * @par msg 信息
 */
void assert_not_null(void* ptr, const char* msg);

/**
 * 构建二进制向量
 * 定义二进制向量 x = [a(w-1), a(w-2), ..., a(1), a(0)]
 * @par num 二进制数（原码）
 * @par w 数据类型的位数
 * @par x 二进制向量（指针传参）
 */
void build_vector(S num, U w, B_VEC* x);

/**
 * 销毁二进制向量
 * @par x 二进制向量（指针传参）
 */
void destroy_vector(B_VEC* x);

/**
 * 打印二进制向量
 * @par x 二进制向量
 * @par w 数据类型的位数
 */
void print_vector(const B_VEC x, U w);

/**
 * 打印元素的函数指针
 */
typedef void (*elem_print_func)(const void* elem);

// 打印有符号数
void print_signed_int(const void* elem);

// 打印无符号数
void print_unsigned_int(const void* elem);

// 打印有符号数的十六进制表示（字母大写）
void print_big_hex(const void* elem);

// 打印有符号数的十六进制表示（字母小写）
void print_small_hex(const void* elem);

// 打印有符号数的补码二进制表示
void print_binary(const void* elem);

/**
 * 打印数组通用版
 * @par arr 指向数组的指针
 * @par size 数组元素个数
 * @par elem_size 单个数组元素的大小，单位：字节
 * @par func 打印元素的函数指针
 */
void print_arr(const void* p_arr, const U size, const U elem_size, const elem_print_func func);

/**
 * 溢出类型枚举
 */
typedef enum {
    POSITIVE_OVERFLOW, // 正溢出
    NORMAL, // 正常
    NEGATIVE_OVERFLOW, // 负溢出
} overflow_type_enum;

/**
 * 将溢出类型枚举转化为描述
 */
const char* to_string(overflow_type_enum type);

/**
 * 将float的内存表示转换为二进制位字符串
 */
char* float_to_binary_string(float f);

/**
 * 将double的内存表示转换为二进制位字符串
 */
char* double_to_binary_string(double d);

/**
 * 判断字符串是否由全 0 字符构成
 */
bool is_string_all_zero(const char* str, U len);

/**
 * 判断字符串是否由全 1 字符构成
 */
bool is_string_all_one(const char* str, U len);

#endif // UTILS_H