#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"DynamicArray.h"
void test01()
{
    //初始化动态数组
    Dynamic_Array* myArray = Array_Init();
    //插入元素
    printf("动态数组容量%d\n", Cappcity_Array(myArray));
    printf("动态数组元素个数%d\n", Size_Array(myArray));
    for (int i = 0; i < 10; i++) {
        Push_Back_Array(myArray, i);
    }
    printf("动态数组容量%d\n", Cappcity_Array(myArray));
    printf("动态数组元素个数%d\n", Size_Array(myArray));
    //打印
    Print_Array(myArray);
    printf("查找%d\n", Find_Array(myArray, 2));
    printf("删除\n");
    RemoveByValue_Array(myArray, 9);
    for (int i = 0; i < myArray->size; i++) {
        printf("%d\n", myArray->pAddr[i]);
    }

    for (int i = 0; i < 10; i++) {
        Push_Back_Array(myArray, i);
    }

    for (int i = 0; i < myArray->size; i++) {
        printf("%d\n", myArray->pAddr[i]);
    }
    //销毁
    FreeSpace_Array(myArray);
}
int main()
{
    test01();
}
