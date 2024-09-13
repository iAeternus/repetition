#include "convert.h"

/**
 * 二进制转无符号数
 * @par x 二进制向量
 * @par w 数据类型的位数
 */
U b2u(B_VEC x, U w) {
    U res = 0;
    for (U i = 0; i < w; ++i) {
        res += x[i] * POW_2(i);
    }
    return res;
}

/**
 * 二进制转补码
 * @par x 二进制向量
 * @par w 数据类型的位数
 */
S b2t(B_VEC x, U w) {
    S res = -x[w - 1] * POW_2(w - 1);
    for(U i = 0; i < w - 1; ++i) {
        res += x[i] * POW_2(i);
    }
    return res;
}

/**
 * 补码转无符号数
 * @par x 二进制向量（补码）
 * @par w 数据类型的位数
 * @return 无符号数
 */
U t2u(S x, U w) {
    return x < 0 ? x + POW_2(w) : x;
}

/**
 * 无符号数转补码
 * @par u 无符号数
 * @par w 数据类型的位数
 * @return 补码
 */
S u2t(U u, U w) {
    S tmax = t_max(w);
    return u > tmax ? u - POW_2(w) : u;
}

/**
 * 无符号数最大值
 * @par w 数据类型的位数
 */
U u_max(U w) {
    return POW_2(w) - 1;
}

/**
 * 无符号数最小值
 * @par w 数据类型的位数
 */
U u_min(U w) {
    return 0;
}

/**
 * 有符号数最大值
 * @par w 数据类型的位数
 */
S t_max(U w) {
    return POW_2(w - 1) - 1;
}

/**
 * 有符号数最小值
 * @par w 数据类型的位数
 */
S t_min(U w) {
    return -POW_2(w - 1);
}