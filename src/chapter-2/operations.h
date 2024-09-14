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
 * @par res 结果（指针传参）
 * @return true=溢出 false=正常
 */
bool u_add(U x, U y, U w, U* res);

/**
 * 判断两个无符号数相加是否正常，64位无符号数
 * @par x 第一个无符号数
 * @par y 第二个无符号数
 * @return true=正常 false=溢出
 */
bool u_add_ok(U x, U y);

/**
 * 计算无符号数的加法逆元
 * @par x 无符号数
 * @par w 数据类型的位数
 * @return 无符号数的加法逆元
 */
U u_inv(U x, U w);

/**
 * 补码加法，并判断是否溢出
 * @par x 第一个补码
 * @par y 第二个补码
 * @par w 数据类型的位数
 * @par res 结果（指针传参）
 * @return 溢出类型枚举
 */
overflow_type_enum t_add(S x, S y, U w, S* res);

/**
 * 判断两个补码相加是否正常，64位补码
 * @par x 第一个补码
 * @par y 第二个补码
 * @return true=正常 false=溢出
 */
bool t_add_ok(S x, S y);

#endif // OPERATION_H