#include<iostream>
class Demo {
public:
	Demo(int i):m(i){}
	void operator()() {
		[this] {std::cout << m << std::endl; }();
	}
	void demo(int a) {
		[=,this] { this->m = a; }();//有所不同的是没有[&this]这种东西，只需要像目前这样就能修改成员变量的值了
	}
	void test() {
		[this] {this->m = 111; };
	}
private:
	int m = 0;
};
int main() {

	//当不接收参数的时候可以省略()，最后加上()是为了调用,下面这些产生的结果是一样的，至少在目前是的
	std::cout << [] { return 5; }() << std::endl;

	std::cout << []()->decltype(auto) {return 5; }() << std::endl;

	std::cout << []()->int {return 5; }() << std::endl;

	std::cout << []()->auto {return 5; }() << std::endl;


	int a = 0;
	//或者接收参数
	auto p = [](int b) {std::cout << b << std::endl; };
	p(a);
	auto p2 = [](auto b) {std::cout << b << std::endl; };
	p2(a);


	//或者直接捕获 下面的区别无非是捕获整个作用域和捕获具体的变量
	[=] {std::cout << a << std::endl; }();
	[i = a] {std::cout << i << std::endl; }();

	//或者直接修改
	[&] {a = 100; std::cout << a << std::endl; }();

	[&a] {a = 100; std::cout << a << std::endl; }();

	//这种方式不是引用，它是值捕获，可以避免过多拷贝和空引用，且外部的a并没有被改变
	[ca=std::as_const(a)] ()mutable {ca = 10; std::cout << ca << std::endl; }();
	std::cout << a << std::endl;

	//下面这是在类内的捕获情况
	Demo demo(10);

	demo();

	demo.demo(123);

	demo();

	demo.test();//这种方式是无法改变成员变量的值的

	demo();


	//其实还有很多操作，最后补充一下，可以像下面这样
	int e(0), f(0), g(0);
	[E = e, F = f, G = g] {std::cout << E << ' ' << F << ' ' << G << std::endl; }();

	[&E = e, &F = f, &G = g] {E = 1, F = 2, G = 3; std::cout << E << ' ' << F << ' ' << G << std::endl; }();
	std::cout << e << ' ' << f << ' ' << g << std::endl;
	
	//另外，不省略()然后->指定类型啥的其实都行，如果是引用捕获的时候()mutable的话也合法，虽然没啥区别，先这样，语法糖而已
	return 0;
}