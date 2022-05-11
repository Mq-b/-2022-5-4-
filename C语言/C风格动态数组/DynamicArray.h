#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct DYNAMICARRAY
{
	int* pAddr;//存放当前数据的地址
	int size;//当前有多少元素
	int capacity;//容量，我容器最大能容纳多少元素
}Dynamic_Array;

//初始化
Dynamic_Array* Array_Init();
//插入
void Push_Back_Array(Dynamic_Array*arr,int value);
//根据位置删除
void Remove_Array(Dynamic_Array* arr, int pos);
//根据值删除
void RemoveByValue_Array(Dynamic_Array*arr,int value);
//查找
int Find_Array(Dynamic_Array* arr, int value);
//打印
void Print_Array(Dynamic_Array* arr);
//释放动态数组的内存
void FreeSpace_Array(Dynamic_Array* arr);
//清空数组
void Clear_Array(Dynamic_Array* arr);
//获取动态数组的容量
int Cappcity_Array(Dynamic_Array* arr);
//获得动态数组当前元素个数
int Size_Array(Dynamic_Array* arr);
//根据位置获取某个位置元素
int At_Array(Dynamic_Array* arr, int poa);

#endif 