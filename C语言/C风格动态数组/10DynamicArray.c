#include"DynamicArray.h"
//初始化
Dynamic_Array* Array_Init(){
	//申请内存
	Dynamic_Array* myArray = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));
	//初始化
	myArray->size = 0;
	myArray->capacity = 20;
	myArray->pAddr = malloc(sizeof(int) * myArray->capacity);
	return myArray;
}
//插入
void Push_Back_Array(Dynamic_Array* arr, int value){
	if (arr == NULL) {
		return;
	}
	//判断空间是否足够
	if (arr->size==arr->capacity) {
		//第一步申请一块更大的内存空间 新空间是旧空间的两倍
		int* newSpace = malloc(sizeof(int) * arr->capacity * 2);
		//第二步 拷贝数据到新的空间,也就是把pAddr拷贝到newSpace
		memcpy(newSpace,arr->pAddr, arr->capacity * sizeof(int));
		//第三步 释放旧空间的内存
		free(arr->pAddr);
		//更新容量
		arr->capacity = arr->capacity * 2;
		arr->pAddr = newSpace;
	}
	arr->pAddr[arr->size] = value;
	arr->size++;
}
//根据位置删除
void Remove_Array(Dynamic_Array* arr, int pos){
	if (arr == NULL) {
		return;
	//判断位置是否有效
	}
	if (pos < 0 || pos >= arr->size) {
		return;
	}
	//删除元素
	for (int i = pos; i < arr->size-1; i++) {
		arr->pAddr[i] = arr->pAddr[i + 1];
	}
	arr->size--;
}
//根据值删除
void RemoveByValue_Array(Dynamic_Array* arr, int value){
	if (arr == NULL) {
		return;
	}
	//找到值的位置
	int pos = Find_Array(arr, value);
	//删除
	Remove_Array(arr, pos);
}
//查找
int Find_Array(Dynamic_Array* arr, int value){
	if (arr == NULL) {
		return-1;
	}
	int pos = -1;
	for (int i = 0; i < arr->size; i++) {
		if (arr->pAddr[i] == value) {
			pos = i;
			break;
		}
	}
	return pos;
}
//打印
void Print_Array(Dynamic_Array* arr){
	if (arr == NULL) {
		return;
	}
	for (int i = 0; i < arr->size; i++) {
		printf("%d", arr->pAddr[i]);
	}
	printf("\n");
}
//释放动态数组的内存
void FreeSpace_Array(Dynamic_Array* arr){
	if (arr == NULL) {
		return;
	}
	if (arr->pAddr != NULL) {
		free(arr->pAddr);
		arr->pAddr = NULL;
	}
	//free(arr);
	//arr = NULL;
}
//清空数组
void Clear_Array(Dynamic_Array* arr) {
	if (arr == NULL) {
		return;
	}
	arr->size = 0;
}
//获取动态数组的容量
int Cappcity_Array(Dynamic_Array* arr) {
	if (arr == NULL) {
		return-1;
	}
	return arr->capacity;
}
//获得动态数组当前元素个数
int Size_Array(Dynamic_Array* arr) {
	if (arr == NULL) {
		return-1;
	}
	return arr->size;
}
//根据位置获取某个位置元素
int At_Array(Dynamic_Array* arr, int poa) {
	return arr->pAddr[poa];
}