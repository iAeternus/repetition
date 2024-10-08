#include <stdio.h>
#include <stdlib.h>

#include "operations.h"
#include "convert.h"

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
 * 判断两个无符号数相加是否正常，64位无符号数
 * @par x 第一个无符号数
 * @par y 第二个无符号数
 * @return true=正常 false=溢出
 */
bool u_add_ok(U x, U y) {
    U sum = x + y;
    return sum >= x;
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

/**
 * 判断两个补码相加是否正常，64位补码
 * @par x 第一个补码
 * @par y 第二个补码
 * @return true=正常 false=溢出
 */
bool t_add_ok(S x, S y) {
    S sum = x + y;
    bool neg_over = x < 0 && y < 0 && sum >= 0;
    bool pos_over = x >= 0 && y >= 0 && sum < 0;
    return !neg_over && !pos_over;
}

/**
 * 计算补码的加法逆元
 * @par x 补码，注意 t_min <= x <= t_max
 * @par w 数据类型的位数
 * @return 补码的加法逆元，若出现错误，则返回 0
 */
S t_inv(S x, U w) {
    S tmin = t_min(w);
    if(x == tmin) {
        return tmin;
    } else if(x > tmin) {
        return -x;
    } else {
        puts("x cannot be less than tmin.");
        return 0;
    }
}

/**
 * 无符号数乘法
 * @par x 第一个无符号数
 * @par y 第二个无符号数
 * @par w 数据类型的位数
 * @return x * y
 */
U u_mul(U x, U y, U w) {
    return (x * y) % POW_2(w);
}

/**
 * 补码乘法
 * @par x 第一个补码
 * @par y 第二个补码
 * @par w 数据类型的位数
 * @return x * y
 */
S t_mul(S x, S y, U w) {
    return u2t((x * y) % POW_2(w), w);
}