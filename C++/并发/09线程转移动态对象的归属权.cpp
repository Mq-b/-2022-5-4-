#include<iostream>
#include<thread>
#include<memory>
class V {
public:
	int a;
};

void T(std::unique_ptr<V>p) { }

void test() {
	std::unique_ptr<V>p(new V);
	p->a=42;
	std::thread t(T, std::move(p));//其实和普通的传参没什么区别，就是变成了移动语义的智能指针
	t.join();
}

int main() {
	test();
}
//25页下半部分