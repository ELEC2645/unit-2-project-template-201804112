#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// 声明通用辅助函数
void strip_newline(char *str);
void get_safe_string(const char *prompt, char *buffer, int size);
double get_safe_double(const char *prompt);
void to_lowercase(char *str);

#endif