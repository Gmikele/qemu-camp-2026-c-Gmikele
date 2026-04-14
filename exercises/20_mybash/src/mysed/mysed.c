#include "mysed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    // 检查输入参数有效性
    if (!cmd || !old_str || !new_str) {
        return -1;
    }
    
    // 初始化输出参数
    *old_str = NULL;
    *new_str = NULL;
    
    // 检查命令格式：应该以's/'开头
    if (strlen(cmd) < 4 || cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }
    
    // 查找第一个分隔符'/'的位置
    const char* first_slash = strchr(cmd, '/');
    if (!first_slash) {
        return -1;
    }
    
    // 查找第二个分隔符'/'的位置
    const char* second_slash = strchr(first_slash + 1, '/');
    if (!second_slash) {
        return -1;
    }
    
    // 查找第三个分隔符'/'的位置（结束符）
    const char* third_slash = strchr(second_slash + 1, '/');
    if (!third_slash) {
        return -1;
    }
    
    // 计算old_str的长度
    size_t old_len = second_slash - first_slash - 1;
    if (old_len == 0) {
        return -1;  // old_str不能为空
    }
    
    // 计算new_str的长度
    size_t new_len = third_slash - second_slash - 1;
    
    // 分配内存并复制old_str
    *old_str = (char*)malloc(old_len + 1);
    if (!*old_str) {
        return -1;
    }
    strncpy(*old_str, first_slash + 1, old_len);
    (*old_str)[old_len] = '\0';
    
    // 分配内存并复制new_str
    *new_str = (char*)malloc(new_len + 1);
    if (!*new_str) {
        free(*old_str);
        *old_str = NULL;
        return -1;
    }
    strncpy(*new_str, second_slash + 1, new_len);
    (*new_str)[new_len] = '\0';
    
    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // 检查输入参数有效性
    if (!str || !old || !new) {
        return;
    }
    
    // 查找old字符串在str中的位置
    char* pos = strstr(str, old);
    if (!pos) {
        return;  // 没有找到，直接返回
    }
    
    // 计算长度
    size_t old_len = strlen(old);
    size_t new_len = strlen(new);
    size_t str_len = strlen(str);
    
    // 如果new比old长，需要确保有足够的空间
    // 这里假设str有足够的空间（根据调用者保证）
    
    if (new_len > old_len) {
        // 需要移动后面的字符
        size_t move_len = str_len - (pos - str) - old_len + 1;  // +1 for null terminator
        memmove(pos + new_len, pos + old_len, move_len);
    } else if (new_len < old_len) {
        // 需要向前移动字符
        size_t move_len = str_len - (pos - str) - old_len + 1;  // +1 for null terminator
        memmove(pos + new_len, pos + old_len, move_len);
    }
    
    // 复制new字符串到找到的位置
    memcpy(pos, new, new_len);
}

int __cmd_mysed(const char* rules, const char* str) {
    // 检查输入参数有效性
    if (!rules || !str) {
        fprintf(stderr, "Error: NULL rules or str parameter\n");
        return 1;
    }

    // printf("rules: %s\n", rules);
    // printf("str: %s\n", str);

    char* old_str = NULL;
    char* new_str = NULL;

    // 解析规则，例如 "s/old/new/"
    if (parse_replace_command(rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    if (!old_str || !new_str) {
        fprintf(stderr, "Error: Failed to parse old/new strings from rules\n");
        free(old_str);
        free(new_str);
        return 1;
    }

    // 复制原始字符串，因为我们可能会修改它（避免修改输入参数）
    char line[1024];
    strncpy(line, str, sizeof(line) - 1);
    line[sizeof(line) - 1] = '\0';  // 确保终止

    // 执行替换：在 line 中把 old_str 替换为 new_str（第一次出现）
    replace_first_occurrence(line, old_str, new_str);

    // 输出结果（建议加上换行，除非 str 本身带了）
    printf("%s\n", line);

    // 释放动态分配的内存
    free(old_str);
    free(new_str);

    return 0;
}