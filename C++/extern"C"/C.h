#pragma once;       //防止头文件重复包含
#ifdef __cplusplus //使用预定义宏判断是否为cpp文件
extern "C" {
#endif
    void display();
#ifdef __cplusplus 
}
#endif
