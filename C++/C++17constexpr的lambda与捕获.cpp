#include<iostream>
class Test {
public:
	Test() = default;
	void t() {
		auto f = [*this]()mutable{//这里，捕获*this意味着该lambda生成的闭包将存储当前对象的一份 拷贝 。
			a = 100;
			std::cout << a << ' ' << b << ' ' << ' ' << c << '\n';
		};
		f();//调用
		std::cout << this->a << std::endl;//0
	}
private:
	int a=0;
	int b=0;
	double c=0.;
};
int main() {
	auto f = [] {return 5 * 3; };
	int n[f()];//合法
	//c++17起，只要能编译期求值的lambda都隐含constexpr
	
	auto g = [](int c)constexpr->int {return c * 5; };
	//我们也可以写明constexpr 然后->int帮助推导返回类型
	int n2[g(5)];

	Test c;
	c.t();
}
//[*this]也是c++17新增语法