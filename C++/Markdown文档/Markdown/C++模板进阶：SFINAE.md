# C++模板进阶：SFINAE



**SFINAE是 Substitution failure is not an error(替换失败不是错误)的缩写**

我们不再介绍它，知乎的大佬对此介绍的很好，我们只为了重复记忆

[C++模板进阶指南：SFINAE](https://zhuanlan.zhihu.com/p/21314708)

 代码:

```c++
#include<iostream>
template<typename T, typename = std::enable_if_t<(sizeof(T) > 4)>>
void foo() {
	std::cout << "first" << std::endl;
}

int main() {
	foo<double>();
}
```

只需要这样一段小小的代码就能解释std::enable_if的用处吗，我们看经过编译器处理后:

```c++
template<>
void foo<double, void>()
{
  std::operator<<(std::cout, "first").operator<<(std::endl);
}
```

模板经过编译器实例化后就是这样，我们可以看到这个函数第二个类型就是void了，这是因为`std::enable_if_t<true>`，会产生一个void，反之，如果不符合里面的条件，这里是`sizeof(T) > 4`，就是`enable_if <false>`

enable_if<false>这个特化形式中，压根就没有这个::type，也就失败了，不会匹配上，当然这也不会error

我们可以拿一个进行比较例子:

```c++
#include<iostream>
template<typename T, typename = std::enable_if_t<(sizeof(T) > 4)>>
void foo() {
	std::cout << "first" << std::endl;
}
template<class T>
void foo()requires std::is_integral_v<T>{
	std::cout << "6" << std::endl;
}
int main() {
	foo<double>();
	foo<int>();
}
```

将分别打印 `first` 和 `6`

requires约束是c++20的特性，与它相比，std::enable_if简直就是垃圾，但是很多库和公司标准并没那么高，也就只能使用std::enable_if了
