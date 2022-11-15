# C++lambda宝典

为什么叫lambda宝典？当你阅读完之后你就不会在有疑惑

## 第一题

```cpp
auto* p = +[] {return 6; };
```

这里的+是什么作用？

1. 这是一个非捕获的lambda，自然可以生成对应转换函数转换为函数指针，这里的一元+是为了辅助推导，是为了创造合适的语境。自然理解为使用转换函数返回函数指针，+指针 符合规范
2. 这里`auto*`的`*`可不可以去掉？可以，没啥作用

## 第二题

```cpp
int main() {
	static int a = 42;
	auto p =[=] { ++a; } ;
	std::cout << sizeof p << '\n';
	p();
	return a;
}
```

提问，打印p是多少？return a是多少？

答案: 1 43

解释

1. 如果变量满足下列条件，那么 **lambda 表达式在使用它前不需要先捕获**：该变量是非局部变量，或具有静态或线程局部[存储期](https://zh.cppreference.com/w/cpp/language/storage_duration)（此时无法捕获该变量），或者该变量是以[常量表达式](https://zh.cppreference.com/w/cpp/language/constant_expression#.E5.B8.B8.E9.87.8F.E8.A1.A8.E8.BE.BE.E5.BC.8F)初始化的引用。

2. 这里的捕获是`[=]`，但是其实写不写都无所谓，反正这个作用域就一个静态局部变量a，你也无法捕获到这个变量。那么按照空类，p的大小一般来说自然也就是1了。

## 第三题

```cpp
//1.
int main() {
	const int a = 6;
	[] {
		std::cout << a << '\n';
	}();
}//通过编译

//2.
int main() {
	constexpr int a = 6;
	[] {
		std::cout << a << '\n';
	}();
}//通过编译

//3.
int main() {
	const float a = 6;
	[] {
		std::cout << a << '\n';
	}();
}//error

//4.
int main() {
	constexpr float a = 6;
	[] {
		std::cout << a << '\n';
	}();
}//通过编译

//5.
int main() {
	const int a = 6;
	[] {
		std::cout << &a << '\n';
	}();
}//error
```

1. 如果变量满足下列条件，那么 lambda 表达式在读取它的值前不需要先捕获：

   - 该变量具有 const 而非 volatile 的整型或枚举类型，并已经用[常量表达式](https://zh.cppreference.com/w/cpp/language/constant_expression#.E5.B8.B8.E9.87.8F.E8.A1.A8.E8.BE.BE.E5.BC.8F)初始化，或者
   - 该变量是 `constexpr` 的且没有 mutable 成员。

2. 同上

3. 同上

4. 同上

5. 这个比较特殊，是ODR的一个事情

   #### ODR 使用

   非正式地说： 1. 一个对象在它的值被读取（除非它是编译时常量）或写入，或它的地址被取，或者被引用绑定时，这个对象被 ODR 使用。 2. 使用“所引用的对象在编译期未知”的引用时，这个引用被 ODR 使用。 3. 一个函数在被调用或它的地址被取时，被 ODR 使用。 如果一个对象、引用或函数被 ODR 使用，那么程序中必须有它的定义；否则通常会有链接时错误。

   链接是:https://zh.cppreference.com/w/cpp/language/definition

但是说实话其实你也可以不考虑ODR，只需要看1的规则，是说**lambda表达式再读取它的值前不需要先捕获**，可没说读地址。当然本质的原因肯定是ODR，只是这个概念也比较生涩。

## 小总结

记住下面两条概念就好

1. 如果变量满足下列条件，那么 lambda 表达式在使用它前不需要先捕获：

- 该变量是非局部变量，或具有静态或线程局部[存储期](https://zh.cppreference.com/w/cpp/language/storage_duration)（此时无法捕获该变量），或者
- 该变量是以[常量表达式](https://zh.cppreference.com/w/cpp/language/constant_expression#.E5.B8.B8.E9.87.8F.E8.A1.A8.E8.BE.BE.E5.BC.8F)初始化的引用。

2. 如果变量满足下列条件，那么 lambda 表达式在读取它的值前不需要先捕获：

- 该变量具有 const 而非 volatile 的整型或枚举类型，并已经用[常量表达式](https://zh.cppreference.com/w/cpp/language/constant_expression#.E5.B8.B8.E9.87.8F.E8.A1.A8.E8.BE.BE.E5.BC.8F)初始化，或者
- 该变量是 `constexpr` 的且没有 mutable 成员。

## 继承lambda

你不会以为我要像下面这样，讲这么简单的吧？？

```cpp
struct X :decltype([] {std::cout << "66\n"; }){

};
```

这完全没什么好说的，我们需要套个娃

```cpp
template<class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
//使用方式:
int main() {
    auto c = overloaded{ [](int arg) { std::cout << arg << ' '; },
                         [](double arg) { std::cout << arg << ' '; },
                          [](auto arg) { std::cout << arg << ' '; }
    };
    c(10);
    c(15.1);
    c("傻子傻子");
}
```

只有五行代码而已，提示:要求C++20，如果是C++17需要加上推导指引，using 声明使用形参包是C++17添加

```cpp
template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;//CTAD 用户定义推导指引 C++17
```

## lambda捕获子句包展开

```cpp
template<class... Args>
void f(Args... args){
	auto lm = [&args...] { return g(args...); };
	lm();
}
int main() {
	f(1, 1.0, 1.f);
}
```

## new一个带捕获lambda

```cpp
#include<iostream>
int main() {
	auto lambda = [x = 0](int c) {std::cout << c << std::endl; };
	auto pLambda = std::make_shared<decltype(lambda)>(lambda);
	(*pLambda)(10);

	auto p = new auto([x = 0](int c) {std::cout << c << std::endl; });
	(*p)(10);
	delete p;
}
```

返回的指针是指向了lambda类的对象，自然要先`*`然后调用operator()，如果你对`new auto()`这个组合有疑问

- *类型* 或 *new类型* 中使用了[占位符](https://zh.cppreference.com/w/cpp/language/auto)，即 auto 或 decltype(auto) (C++14 起)，可能与[类型约束](https://zh.cppreference.com/w/cpp/language/constraints#.E6.A6.82.E5.BF.B5)结合 (C++20 起)

```cpp
auto p = new auto(5.6);
```

## lambda表达式是什么？

**lambda 表达式是纯右值表达式，它的类型是独有的无名非联合非聚合类类型，被称为*闭包类型*（closure type），它（对于 [实参依赖查找](https://zh.cppreference.com/w/cpp/language/adl) 而言）在含有该 lambda 表达式的最小块作用域、类作用域或命名空间作用域声明。**



## lambda与constexpr

```cpp
	constexpr int a = [] {return 6; }();//合法 要求C++17
```

可以显式指定函数调用运算符或运算符模板的任意特化为 [constexpr 函数](https://zh.cppreference.com/w/cpp/language/constexpr#constexpr_.E5.87.BD.E6.95.B0)。**如果没有此说明符但函数调用运算符或任意给定的运算符模板特化恰好满足针对 constexpr 函数的所有要求，那么它也会是 `constexpr` 的**

## 总结

lambda的模板形参，泛型lambda也没什么好介绍的了，没啥坑，先这样

