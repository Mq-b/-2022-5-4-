#include<stdio.h>
#include<iostream>
void insert(int a[], int n)
{
	int  interval = n >> 1;
	while (interval > 0)
	{
		for (int i = interval; i < n; i += interval)//划分小组。 
			for (int j = i; j > 0; j = j - interval)//小组内进行直接插入排序。 
				if (a[j] < a[j - interval])
				std::swap(a[j], a[j - interval]);
		interval >>= 1;
	}
}
int main()
{ 
	int a[10] = { 7,3,1,6,2,0,5,8,4,9 };
	insert(a, 10);
	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);
}
