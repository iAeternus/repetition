/**
 * @brief 数据类型的转换
 * @author ricky
 * @date 2024/9/13
 * @version 1.0
 */
#ifndef CONVERT_H
#define CONVERT_H

#include "utils.h"

/**
 * 二进制转无符号数
 * @par x 二进制向量
 * @par w 数据类型的位数
 */
U b2u(B_VEC x, U w);

/**
 * 二进制转补码
 * @par x 二进制向量
 * @par w 数据类型的位数
 */
S b2t(B_VEC x, U w);

/**
 * 补码转无符号数
 * @par x 二进制向量（补码）
 * @par w 数据类型的位数
 * @return 无符号数
 */
U t2u(S x, U w);

/**
 * 无符号数转补码
 * @par u 无符号数
 * @par w 数据类型的位数
 * @return 补码
 */
S u2t(U u, U w);

/**
 * 无符号数最大值
 * @par w 数据类型的位数
 */
U u_max(U w);

/**
 * 无符号数最小值
 * @par w 数据类型的位数
 */
U u_min(U w);

/**
 * 有符号数最大值
 * @par w 数据类型的位数
 */
S t_max(U w);

/**
 * 有符号数最小值
 * @par w 数据类型的位数
 */
S t_min(U w);

#endif  // CONVERT_H