/**
 * @brief 纯手搓模拟 IEEE 754 浮点数标准
 * @author ricky
 * @date 2024/9/14
 * @version 1.0
 */
#ifndef FLOATING_NUMBER_H
#define FLOATING_NUMBER_H

#include <stdbool.h>

typedef char bit;
typedef unsigned int size;

/**
 * 浮点数类型
 */
typedef enum {
    NORMALIZED, // 规格化
    UNNORMALIZED, // 非规格化
    POSITIVE_INFINITY, // 正无穷
    NEGATIVE_INFINITY, // 负无穷
    NAN, // not a number
} floating_number_type_enum;

/**
 * 浮点数结构
 * V = (-1)^s * M * 2^E
 */
typedef struct {

    /**
     * 符号位，1 位
     * 若为 1 则代表负数，否则代表正数
     */
    bit s;

    /**
     * 阶码位数
     */
    size k;

    /**
     * 尾数位数
     */
    size n;

    /**
     * 浮点数总位数
     * len = 1 + k + n
     */
    size len;

    /**
     * 阶码，k 位
     * exp = [e(k-1), e(k-2), ..., e(1), e(0)]
     */
    bit* exp;

    /**
     * 位数，n 位
     * frac = [f(n-1), f(n-2), ..., f(1), f(0)]
     */
    bit* frac;

} floating_number;

/**
 * 构建浮点数
 * @par p_num 指向浮点数的指针
 * @par k 阶码位数
 * @par n 尾数位数
 * @par len 浮点数总位数
 * @par bits 位数组
 */
void build_floating_number(floating_number* p_num, size k, size n, size len, bit* bits);

/**
 * 构建 32 位浮点数
 * @par p_num 指向浮点数的指针
 * @par bits 位数组
 */
void build_32(floating_number* p_num, bit* bits);

/**
 * 构建 64 位浮点数
 * @par p_num 指向浮点数的指针
 * @par bits 位数组
 */
void build_64(floating_number* p_num, bit* bits);

/**
 * 构建单精度浮点数
 * @par p_num 指向浮点数的指针
 * @par f 单精度浮点数
 */
void build_with_float(floating_number* p_num, float f);

/**
 * 构建双精度浮点数
 * @par p_num 指向浮点数的指针
 * @par d 双精度浮点数
 */
void build_with_double(floating_number* p_num, double d);

/**
 * 释放内存空间
 * @par p_num 指向浮点数的指针
 */
void destroy_floating_number(floating_number* p_num);

// 打印位
void print_bit(const void* elem);

/**
 * 打印浮点数
 * @par p_num 指向浮点数的指针
 */
void print_floating_number(const floating_number* p_num);

/**
 * 获取浮点数类型
 * @par p_num 指向浮点数的指针
 * @return 浮点数类型
 */
floating_number_type_enum get_type(const floating_number* p_num);

#endif // FLOATING_NUMBER_H