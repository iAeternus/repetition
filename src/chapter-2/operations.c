#include <stdio.h>
#include <stdlib.h>

#include "operations.h"

/**
 * 无符号数加法，并判断是否溢出
 * @par x 第一个无符号数
 * @par y 第二个无符号数
 * @par w 数据类型的位数
 * @par res 结果（指针传参）
 * @return true=溢出 false=正常
 */
bool u_add(U x, U y, U w, U* res) {
    U sum = x + y;
    if(sum < POW_2(w)) {
        *res = sum;
        return false;
    }

    // 溢出
    *res = x - POW_2(w) + y; // x + y - 2^w
    return true;
}

/**
 * 判断两个无符号数相加是否溢出
 * @par x 第一个无符号数
 * @par y 第二个无符号数
 * @par w 数据类型的位数
 * @return true=溢出 false=正常
 */
bool u_add_ok(U x, U y, U w) {
    U res;
    u_add(x, y, w, &res);
    return res < x; // x + y < x 时溢出
}

/**
 * 计算无符号数的加法逆元
 * @par x 无符号数
 * @par w 数据类型的位数
 * @return 无符号数的加法逆元
 */
U u_inv(U x, U w) {
    return x == 0 ? x : POW_2(w) - x;
}

/**
 * 补码加法，并判断是否溢出
 * @par x 第一个补码
 * @par y 第二个补码
 * @par w 数据类型的位数
 * @par res 结果（指针传参）
 * @return 溢出类型枚举
 */
overflow_type_enum t_add(S x, S y, U w, S* res) {
    S sum = x + y;
    S tmp = POW_2(w - 1);
    S rep = tmp << 1; // 2^w
    overflow_type_enum type;
    if(sum >= tmp) {
        *res = x - rep + y;
        type = POSITIVE_OVERFLOW;
    } else if(sum >= -tmp) {
        *res = x + y;
        type = NORMAL;
    } else {
        *res = x + y + rep;
        type = NEGATIVE_OVERFLOW;
    }
    return type;
}