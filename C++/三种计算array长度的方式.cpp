#include<iostream>
template<size_t size>
void func(int(*arr)[size]) {
	std::cout << size << std::endl;
}
void func2(int(*arr)[10]) {
	std::cout << sizeof * arr / sizeof(int) << std::endl;
}
template<typename T,size_t size>
void func3(T(&arr)[size])
{
	std::cout << size << std::endl;
}
int main() {
	int arr[10];
	func(&arr);
	func2(&arr);
	func3(arr);
}