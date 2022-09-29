## 前言

我们不详细讲述lambda的基本知识

我们都使用过lambda，一般来说 ，我们都是`auto x = [](){};`这样的语句去创建一个lambda，这样的lambda，auto推导的是一个匿名lambda类的对象类型，实则是实例化了一个lambda类的对象

如果不进行捕获，则lambda匿名类实则为空类，如果进行`sizeof x`的结果会为1,这些都没什么好说的

当我们使用`x()`的时候也就是调用这个函数对象的`operator()`

这些都不是我们今天要讲述的重点，我们想要用函数指针来接lambda表达式，那又会如何呢？

## 普通lambda的转换函数

切记，不管是普通lambda还是泛型lambda(c++14)都不能带捕获才可以有默认的转换函数

我们举一个例子:
```C++
int(*p)(int) = [](int n) {return n; };
```

像上面这样的一行代码将生成什么呢？如下:

```C++
int main()
{
      
  class __lambda_2_17
  {
    public: 
    inline /*constexpr */ int operator()(int n) const
    {
      return n;
    }
    
    using retType_2_17 = int (*)(int);
    inline constexpr operator retType_2_17 () const noexcept
    {
      return __invoke;
    }
    
    private: 
    static inline /*constexpr */ int __invoke(int n)
    {
      return __lambda_2_17{}.operator()(n);
    }
    
    
    public:
    // /*constexpr */ __lambda_2_17() = default;
    
  };
  
  using FuncPtr_2 = int (*)(int);
  FuncPtr_2 p = static_cast<int (*)(int)>(__lambda_2_17{}.operator __lambda_2_17::retType_2_17());
  return 0;
}
```

首先它为lambda生成了一个类，这很正常，我们看类内:它有一个public的`operator()`，一个using`retType_2_17 = int (*)(int);`它就是我们转换函数转换的类型

一个private的静态函数`int __invoke(int n)`，这个静态函数就是为了被转换函数返回函数指针而存在的,它实则是创建临时的lambda对象，再调用它的`operator()`

转换函数`operator retType_2_17`,转换函数相信也都不用介绍了，可隐式转换为函数指针

最终p实际是是等于了lambda构造临时对象再隐式的调用了转换函数转换为了一个函数指针

**可能有点小绕？实际是想想就理解了，代码只是参考性的**


## 泛型lambda转换函数

其实是差不多的，并没有多少的区别，但还是举例子代码给大家看看吧

```C++
int(*p)(int) = [](auto n) {return n; };
```

生成:

```C++
int main()
{
      
  class __lambda_2_17
  {
    public: 
    template<class type_parameter_0_0>
    inline /*constexpr */ auto operator()(type_parameter_0_0 n) const
    {
      return n;
    }
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ int operator()<int>(int n) const
    {
      return n;
    }
    #endif
    
    
    /* First instantiated from: insights.cpp:2 */
    #ifdef INSIGHTS_USE_TEMPLATE
    using retType_2_17 = int (*)(int);
    template<>
    inline constexpr operator retType_2_17 () const noexcept
    {
      return __invoke;
    }
    #endif
    
    private: 
    template<class type_parameter_0_0>
    static inline /*constexpr */ auto __invoke(type_parameter_0_0 n)
    {
      return __lambda_2_17{}.operator()<type_parameter_0_0>(n);
    }
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    static inline /*constexpr */ int __invoke<int>(int n)
    {
      return __lambda_2_17{}.operator()<int>(n);
    }
    #endif
    
    
    public:
    // /*constexpr */ __lambda_2_17() = default;
    
  };
  
  using FuncPtr_2 = int (*)(int);
  FuncPtr_2 p = static_cast<int (*)(int)>(__lambda_2_17{}.operator __lambda_2_17::retType_2_17());
  return 0;
}

```
不再详细说这个例子了,那就用文档的概念和例子结束泛型lambda转换函数的介绍吧

泛型无捕获 lambda 拥有一个用户定义的转换函数模板，它具有与函数调用运算符模板相同的虚设模板形参列表。如果它的返回类型为空或 auto，那么将由函数模板特化上的返回类型推导获得，而它会以转换函数模板的模板实参推导获得。

```C++
void f1(int (*)(int)) {}
void f2(char (*)(int)) {}
void h(int (*)(int)) {}  // #1
void h(char (*)(int)) {} // #2
 
auto glambda = [](auto a) { return a; };
f1(glambda); // OK
f2(glambda); // 错误：不可转换
h(glambda);  // OK：调用 #1，因为 #2 不可转换
 
int& (*fpi)(int*) = [](auto* a) -> auto& { return *a; }; // OK
```
