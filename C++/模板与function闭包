#include<iostream>
#include<functional>

template<class F>
void func(F fuc )
{
	fuc();
	std::cout << typeid(F).name() << std::endl;
}
void print(int i)
{
	std::cout << i << std::endl;
}
template<typename T>
void func2(T a)
{
	a();
	std::cout << typeid(T).name() << std::endl;
}
int main()
{
	std::function<void()>A = std::bind(print, 10);
	func(A);
	func2(std::bind(print, 10));
}
