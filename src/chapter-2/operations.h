/**
 * @brief 整数与浮点数的运算
 * @author ricky
 * @date 2024/9/13
 * @version 1.0
 */
#ifndef OPERATION_H
#define OPERATION_H

#include <stdbool.h>

#include "utils.h"

/**
 * 无符号数加法，并判断是否溢出
 * @par x 第一个无符号数
 * @par y 第二个无符号数
 * @par w 数据类型的位数
 * @par res 结果
 * @return true=溢出 false=正常
 */
bool u_add(U x, U y, U w, U* res);

/**
 * 判断两个无符号数相加是否溢出
 * @par x 第一个无符号数
 * @par y 第二个无符号数
 * @par w 数据类型的位数
 * @return true=溢出 false=正常
 */
bool is_u_add_overflows(U x, U y, U w);

/**
 * 计算无符号数的加法逆元
 * @par x 无符号数
 * @par w 数据类型的位数
 * @return 无符号数的加法逆元
 */
U u_inv(U x, U w);

// TODO

#endif // OPERATION_H