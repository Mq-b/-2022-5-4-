#include <stdio.h>
#include <math.h>

//类似c++重载
#define cbrt(X) _Generic((X), \
              long double: cbrtl, \
                  default: cbrt,  \
                    float: f1  \
)(X)

float f1(float n){//自定义函数
    return n+10;
}

int main(void)
{
    double x = 8.0;
    const float y = 3.375;
    printf("cbrt(8.0) = %f\n", cbrt(x)); // 选择默认的 cbrt
    printf("cbrtf(3.375) = %f\n", cbrt(y)); // 将 const float 转换成 float，
}
/*
 * 可参数文档链接
 * https://zh.cppreference.com/w/c/language/generic 泛型选择
 */
