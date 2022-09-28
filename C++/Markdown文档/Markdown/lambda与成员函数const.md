参考以下代码:
```C++
#include<iostream>
struct T {
	void f() {
		int c = 10;
		[=] {
			n = c;
			std::cout << n << std::endl;
			c = 10;//编译错误
		}();
	}
	int n = 0;
};
int main() {
	T c;
	c.f();
	std::cout << c.n;
	[=] {c.n = 10; }();//编译错误
}
```

非const的成员函数内，lambda的=捕获的this指针自然就不是const的，那么成员变量自然可以修改，反之亦然。如果是函数局部的变量，若未加mutable，lambda的operator()则是const的，无法在lambda内修改

强调：const只是修改了this指针为const的，对于成员函数内局部变量的修改没有关系

&引用捕获也是同理
