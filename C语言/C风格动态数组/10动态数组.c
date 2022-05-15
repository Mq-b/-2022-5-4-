#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"DynamicArray.h"
void test01()
{
    //��ʼ����̬����
    Dynamic_Array* myArray = Array_Init();
    //����Ԫ��
    printf("��̬��������%d\n", Cappcity_Array(myArray));
    printf("��̬����Ԫ�ظ���%d\n", Size_Array(myArray));
    for (int i = 0; i < 10; i++) {
        Push_Back_Array(myArray, i);
    }
    printf("��̬��������%d\n", Cappcity_Array(myArray));
    printf("��̬����Ԫ�ظ���%d\n", Size_Array(myArray));
    //��ӡ
    Print_Array(myArray);
    printf("����%d\n", Find_Array(myArray, 2));
    printf("ɾ��\n");
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
    //����
    FreeSpace_Array(myArray);
}
int main()
{
    test01();
}