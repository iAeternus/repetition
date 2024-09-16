#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/**
 * 断言指针不为空
 * 若指针为空则打印信息结束程序，否则什么都不做
 * @par ptr 指针
 * @par msg 信息
 */
void assert_not_null(void* ptr, const char* msg) {
    if(!ptr) {
        if(msg) {
            puts(msg);
        }
        exit(EXIT_FAILURE);
    }
}

void build_vector(S num, U w, B_VEC* x) {
    *x = (B_VEC)malloc(sizeof(U) * w);
    assert_not_null(*x, NULL);

    U i;
    for (i = 0; i < w; ++i) {
        (*x)[i] = (num >> i) & 1;
    }
}

void destroy_vector(B_VEC* x) {
    free(*x);
    *x = NULL;
}

/**
 * 计算大于w的数中能整除n的最小的数
 */
static U exact_division(U w, U n) {
    for(U i = w + 1; ; ++i) {
        if(i % n == 0) {
            return i;
        }
    }
    return 0;
}

void print_vector(B_VEC x, U w) {
    // 打印前导0
    U max_len = exact_division(w, 4);
    U cover = max_len - w;
    if(cover < 4) {
        for(U i = 0; i < cover; ++i) {
            putchar('0');
        }
    }

    U idx = cover;
    for(U i = 0; i < w; ++i) {
        printf("%u", x[w - i - 1]);
        idx++;
        if(idx % 4 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}

void print_signed_int(const void* elem) {
    printf("%d ", *(const S*)elem);
}

void print_unsigned_int(const void* elem) {
    printf("%u ", *(const U*)elem);
}

void print_big_hex(const void* elem) {
    printf("0x%X ", *(const S*)elem);
}

void print_small_hex(const void* elem) {
    printf("0x%x ", *(const S*)elem);
}

void print_binary(const void* elem) {
    S num = *(const S*)elem;
    U mask = 1U << 31;
    for (int i = 31; i >= 0; --i) {
        U testBit = (U)num & mask;
        printf("%u", testBit ? 1 : 0);
        mask >>= 1;
    }
    putchar(' ');
}

void print_arr(const void* p_arr, const U size, const U elem_size, const elem_print_func func) {
    char* ptr = (char*) p_arr;
    for(U i = 0; i < size; ++i) {
        func(ptr);
        ptr += elem_size;
    }
    putchar('\n');
}

/**
 * 将溢出类型枚举转化为描述
 */
const char* to_string(overflow_type_enum type) {
    switch(type) {
    case POSITIVE_OVERFLOW:
        return "positive overflow";
    case NORMAL:
        return "normal";
    case NEGATIVE_OVERFLOW:
        return "negative overflow";
    default:
        puts("Incorrect type.");
        return NULL;
    }
}

char* float_to_binary_string(float f) {
    char* binary_str = (char*)malloc(33 * sizeof(char));
    assert_not_null(binary_str, NULL);

    unsigned char* f_bytes = (unsigned char*)&f;
    memset(binary_str, '0', 32);
    binary_str[32] = '\0';

    for (int i = 0; i < sizeof(float); ++i) {
        for (int j = 0; j < 8; ++j) {
            int bit_index = 31 - (i * 8 + j);
            if (f_bytes[i] & (1 << j)) {
                binary_str[bit_index] = '1';
            }
        }
    }

    return binary_str;
}

char* double_to_binary_string(double d) {
    char* binary_str = (char*)malloc(65 * sizeof(char));
    assert_not_null(binary_str, NULL);

    unsigned char* d_bytes = (unsigned char*)&d;

    memset(binary_str, '0', 64);
    binary_str[64] = '\0';

    for (int i = 0; i < sizeof(double); ++i) {
        for (int j = 0; j < 8; ++j) {
            int bit_index = 63 - (i * 8 + j);
            if (d_bytes[i] & (1 << j)) {
                binary_str[bit_index] = '1';
            }
        }
    }

    return binary_str;
}

bool is_string_all_zero(const char* str, U len) {
    if(!str || len == 0) {
        return true;
    }

    for(U i = 0; i < len; ++i) {
        if(str[i] != '0') {
            return false;
        }
    }
    return true;
}

bool is_string_all_one(const char* str, U len) {
    if(!str || len == 0) {
        return true;
    }

    for(U i = 0; i < len; ++i) {
        if(str[i] != '1') {
            return false;
        }
    }
    return true;
}

void add_binary(const char* a, const char* b, char* result, int k) {  
    int carry = 0; // 进位  
    for (int i = k - 1; i >= 0; i--) {  
        int sum = (a[i] - '0') + (b[i] - '0') + carry; // 假设'a'和'b'中的元素是'0'或'1'  
        result[i + 1] = (sum % 2) + '0'; // 存储当前位的和（模2）  
        carry = sum / 2; // 更新进位  
    }  
    if (carry) { // 如果最高位相加后有进位  
        result[0] = '1'; // 在结果数组的最前面添加进位  
    } else {  
        // 如果没有进位，则结果数组的第一个元素是未定义的，我们可以设置为0或保留为'\0'（如果作为字符串处理）  
        result[0] = '0'; // 或者不设置，让调用者知道结果从result[1]开始  
    }  
    // 注意：这里我们假设result有足够的空间来存储k+1个元素  
    // 在实际使用中，应该确保result指向的数组至少包含k+1个元素  
  
    // 由于我们通常希望结果是一个有效的字符串（以'\0'结尾），我们可以添加：  
    result[k + (carry ? 1 : 0)] = '\0'; // 根据是否有进位来设置字符串的结尾  
  
    // 如果不需要以'\0'结尾的字符串，可以省略上述设置'\0'的代码  
}  

void subtract_binary(const char* a, const char* b, char* result, int k) {  
    int borrow = 0; // 借位（实际上是“进位”的反向）  
    for (int i = k - 1; i >= 0; i--) {  
        int diff = (a[i] - '0') - (b[i] - '0') - borrow; // 同样假设'a'和'b'中的元素是'0'或'1'  
        if (diff < 0) {  
            diff += 2; // 相当于从高位借1（即加上2）  
            borrow = 1; // 设置借位  
        } else {  
            borrow = 0; // 清除借位  
        }  
        result[i] = diff + '0'; // 存储结果（注意这里我们直接存储在result的当前位置）  
    }  
  
    // 处理结果数组前的可能的前导0（如果有的话）  
    // 注意：这里我们假设result有足够的空间来存储k个元素（不考虑可能的进位）  
    // 但在实际情况下，如果结果比输入短，我们可能需要左移结果并填充前导0或进行其他处理  
  
    // 由于减法通常不会产生比减数更长的结果（在二进制中），我们不需要担心结果数组溢出  
    // 但为了安全起见，调用者应该确保result指向的数组至少包含k个元素  
  
    // 如果需要，可以添加代码来移除结果前导的'0'（除了最高位可能是'0'之外）  
  
    // 同样的，如果我们希望结果是一个有效的字符串，我们可以在最后添加'\0'  
    result[k] = '\0'; // 假设result至少有k+1个元素的空间  
  
    // 注意：上面的函数没有处理a小于b的情况（即需要借位但最高位也不足以借的情况）  
    // 在那种情况下，你可能需要设置一个标志来表示结果是负数，或者将结果视为补码形式  
    // 在二进制中，这通常意味着对结果取反并加1来得到原数的绝对值  
}  