#include<iostream>
#include<thread>
void f(int i, std::string const& s) {}
void oops(int some_param) {
	char buffer[1024];
	sprintf(buffer, "%i", some_param);//把十进制整形转换为字符串
	//std::thread t(f, 3, buffer);	//错误方式有可能引发未定义行为，在第23面和24上有详细介绍
	std::thread t(f, 3, std::string(buffer));//手动转化为string，而不是thread构造函数隐式转换
	t.detach();
}
int main() {
	oops(6);
}