# C++多字节字符

## 示例



我们直接看以下代码

```c++
#include<iostream>

int main() {
	using type = decltype('中');//int
	using type = decltype('AB');//int
    char c = '6666';
	std::cout << '中' << std::endl;//14989485
	std::cout << 'AB' << std::endl;//16706
}
```

很多老师，很多书，喜欢出诸如此类的一些牛马题目，尤其还喜欢问你们，它的值是什么，比如上面这个c的值，愚蠢，天大的愚蠢



## 解释

我们先说从char类型说起:

**char - 能在目标系统上最有效地处理的字符表示的类型（拥有与 signed char 或 unsigned char 之一相同的表示和对齐，但始终是独立的类型）。[多字节字符串](https://zh.cppreference.com/w/cpp/string/multibyte)用此类型表示编码单元。对于每个范围 [0, 255] 中的 unsigned char 类型值，将该值转换成 char 再转换回 unsigned char 产生原值。 (C++11 起) char 的符号性取决于编译器和目标平台：ARM 和 PowerPC 的默认设置通常没有符号，而 x86 与 x64 的默认设置通常有符号。**

---

再谈字面量:

**通常多字符字面量（条件性支持），例如 'AB'，具有 int 类型和实现定义的值。**



## 文档链接

### [char类型](https://zh.cppreference.com/w/cpp/language/types)

### [多字符字面量](https://zh.cppreference.com/w/cpp/language/character_literal)

### [多字节字符串](https://zh.cppreference.com/w/cpp/string/multibyte)