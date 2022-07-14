#include<iostream>
decltype(auto) Test(auto&& a) {
	std::cout << __FUNCSIG__ << std::endl;
}
int main() {
	Test<int&&>(5);
}