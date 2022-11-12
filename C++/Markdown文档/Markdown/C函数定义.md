# C函数定义

## ` (C23 前) 旧式 (K&R) `函数定义。

```c
int max(a, b)
int a, b;
{
    return a>b?a:b;
}
```

---



## `C89`函数定义

```c
max(a, b) // a 和 b 拥有 int 类型，返回类型为 int
{
    return a>b?a:b;
}
```

C89 中， *说明符与限定符* 是可选的，若省略它，则函数返回类型默认为 int （可由 *声明符* 修改）。

另外，旧式定义不要求在 *声明列表* 中声明每个参数。任何缺少声明的参数拥有 int 类型

但是也可以使用正常的我们现在使用的风格

```c
int max(int a, int b)
{
    return a>b?a:b;
}
```

---



## `C23`函数定义

| 不同于[函数声明](https://zh.cppreference.com/w/c/language/function_declaration)，不允许无名形参（否则旧式 (K&R) 函数定义中会有冲突），即使不在函数中使用也必须命名它们。仅有的例外是参数列表 (void) 。 | (C23 前)     |
| ------------------------------------------------------------ | ------------ |
| **函数定义中形参可以为无名，因为旧式 (K&R) 函数定义已被移除。函数体内不能以名称访问无名形参。** | **(C23 起)** |

```c
int f(int, int); // 声明
// int f(int, int) { return 7; } // C23 前错误， C23 起 OK
int f(int a, int b) { return 7; } // 定义
int g(void) { return 8; } // OK ： void 不声明参数
```