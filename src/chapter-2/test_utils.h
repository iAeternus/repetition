#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdbool.h>

// 打印绿色文本
#define GREEN_COLOR "\033[32m"
#define DEFAULT_COLOR "\033[0m"

/**
 * 具体测试函数指针
 */
typedef void (*test_function)();

/**
 * 单元测试函数-计时
 * @par msg 单元测试信息
 * @par func 具体测试函数指针
 */
void test_with_time(const char* msg, test_function func);

/**
 * 单元测试函数-不计时
 * @par msg 单元测试信息
 * @par func 具体测试函数指针
 */
void test(const char* msg, test_function func);

#endif // TEST_UTILS_H