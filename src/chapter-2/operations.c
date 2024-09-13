#include "operations.h"

/**
 * 无符号数加法，并判断是否溢出
 * @par x 第一个无符号数
 * @par y 第二个无符号数
 * @par w 数据类型的位数
 * @par res 结果
 * @return true=溢出 false=正常
 */
bool u_add(U x, U y, U w, U* res) {
    U tmp = x + y;
    if(tmp < POW_2(w)) {
        *res = tmp;
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
bool is_u_add_overflows(U x, U y, U w) {
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