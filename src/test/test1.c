#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 将float的内存表示转换为二进制位字符串
 */
char* float_to_binary_string(float f) {
    char* binaryStr = (char*)malloc(33 * sizeof(char));
    if (!binaryStr)
        return NULL;

    unsigned char* fBytes = (unsigned char*)&f;
    memset(binaryStr, '0', 32);
    binaryStr[32] = '\0';

    for (int i = 0; i < sizeof(float); ++i) {
        for (int j = 0; j < 8; ++j) {
            int bitIndex = 31 - (i * 8 + j);
            if (fBytes[i] & (1 << j)) {
                binaryStr[bitIndex] = '1';
            }
        }
    }

    return binaryStr;
}

/**
 * 将double的内存表示转换为二进制位字符串
 */
char* double_to_binary_string(double d) {
    char* binaryStr = (char*)malloc(65 * sizeof(char));
    if (!binaryStr)
        return NULL;

    unsigned char* dBytes = (unsigned char*)&d;

    memset(binaryStr, '0', 64);
    binaryStr[64] = '\0';

    for (int i = 0; i < sizeof(double); ++i) {
        for (int j = 0; j < 8; ++j) {
            int bitIndex = 63 - (i * 8 + j);
            if (dBytes[i] & (1 << j)) {
                binaryStr[bitIndex] = '1';
            }
        }
    }

    return binaryStr;
}

int main() {
    printf("%s\n", float_to_binary_string(3510593.0f));
    printf("%s\n", double_to_binary_string(3510593.0));

    return 0;
}