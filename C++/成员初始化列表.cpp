#include<iostream>
class Test {
public:
	Test() :m(d), d(0) {}

	int d;
	int m;
};

class Test2 {
public:
	Test2() :m(d), d(0) {}

	int m;
	int d;
};
int main() {
	Test a;
	Test2 b;
	std::cout << a.d << ' ' << a.m << std::endl;
	std::cout << b.d << ' ' << b.m << std::endl;
}
//第一种行为是安全的 成员初始化列表的顺序是声明的顺序 第一个类先声明了d  它就会先初始化 然后给m初始化 没有问题 第二种则不是