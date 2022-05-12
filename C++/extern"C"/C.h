#pragma once;       //防止头文件重复包含，Windows平台专属
#ifdef __cplusplus //使用预定义宏判断是否为cpp文件
extern "C" {
    void display();
}
#endif
#ifndef __cplusplus
void display();
#endif