# 仅以此记录C#学习文档

## 参考微软文档，运行环境是Visual Studo2022 框架:.NET Framework 4.7.2

### C#语法基本使用 变量 数组 函数 重载 默认参数 封装继承多态，范围for，var

``` C#
using Cshap.Propertie;
using System;
using System.Text;

//命名空间，没什么好说的
namespace Cshap
{
    
    internal class Program
    {
        //默认参数，函数重载
        public static void print(int a = 100)
        {
            Console.WriteLine("重载的print:" + a);
        }
        public static void print()
        {
            Console.WriteLine("函数");
        }
        static void Main(string[] args)
        {
            Console.InputEncoding = Encoding.Unicode;
            //Console表示控制台应用程序的标准输入流、输出流和错误流。 此类不能被继承
            Console.WriteLine("Hello,Word");

            var str = Console.ReadLine();
            Console.WriteLine(str);

            Person person = new Person(str, 18);
            Console.WriteLine(person.GetName() + "," + person.GetAge()
                + "," + person.GetType());

            int[] ints = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            foreach (var i in ints)
                Console.Write(i + " ");

            print(300);
            print();

            //多态
            Test1 test1 = new Test1();
            test1.t();
            test1 = new Test2();
            test1.t();
        }
    }
    public class Person
    {
        private String Name;
        private int Age;
        public Person(string name, int age)
        {
            this.Name = name;
            this.Age = age;
        }
        public Person() { }
        public String GetName()
        {
            return Name;
        }
        public int GetAge()
        {
            return Age;
        }
        public void SetName(String name)
        {
            this.Name = name;
        }
        public void SetAge(int age)
        {
            this.Age = age;
        }
    }
}
```

#### 权限修饰符

1.声明命名空间、类，前面不加限制访问修饰符时，默认访问权限为internal——访问仅限于当前程序集。 

2.声明类成员(包括字段(变量)、属性和方法)默认为private）以及结构类型，前面不加限制访问修饰符时，默认访问权限为private——访问仅限于当前类。

3.声明枚举类型以及接口类型，前面不加限制访问修饰符时，默认为public且只能为public(就算要把限制访问修饰符写出来，也只能写public，而不能使用其他限制访问修饰符)——访问不受限制。

我们都知道的三种类型/成员修饰符public、protected、private，也明白它们所表示的含义，internal也是一各类型/成员修饰符（被修饰的类型或者成员称为内部类型或成员），只是它所修饰的类

只能在同一个程序集中被访问，而同一个程序集表示同一个dll程序集或同一个exe程序集。如果我们另一个程序使用了internal修饰的类生成的dll，那么就是错误的。

#### 编码问题处理

将输入字符编码换成utf16，因为当你系统开启支持Unicode 终端将以utf8显示，但是powershell读取字符串内部转换为utf16再传递给net api，所以我们只需要改变输入字符编码，在Main第一行加上:
``` C#
Console.InputEncoding = Encoding.Unicode;
```

​            

**Test继承多态的实现如下**

``` C#
internal class Test1
    {
        public virtual void t()
        {
            Console.InputEncoding = Encoding.Unicode;
            var str = Console.ReadLine();
            if (str == "13")
                Console.WriteLine("你输入了13");
            else
                Console.WriteLine("没输入13");
        }
    }
    internal class Test2 : Test1
    {
        public override void t()
        {
            Console.WriteLine("Test2继承Test1重写了t虚方法");
        }
    }
```

### Math数学类的使用以及Convert基本数据类型转换类

``` C#
using System;
using System.Runtime.InteropServices;

namespace Cshap2
{

    internal class Program
    {
        private double value;
        public Program(double value = 0)
        {
            this.value = value;
        }
        double Area()
        {
            return Math.PI * Math.Pow(value, 2);
        }

        static void Main(string[] args)
        {
            //var r = Convert.ToDouble(Console.ReadLine());
            //var t = new Program(r);
            //Console.WriteLine("表面积= " + t.Area());
            double x = 3.2, y = 2.4;
            Console.WriteLine((Math.Pow(x, 2) + Math.Pow(y, 2) + 2 * x * y) / (2 * x - 3 * y));
        }
    }
}

```

### 接口
``` C#
interface IMyInterface
{
        // 接口成员
    void MethodToImplement();
}

class InterfaceImplementer : IMyInterface
{
    static void Main()
    {
        InterfaceImplementer iImp = new InterfaceImplementer();
        iImp.MethodToImplement();
    }

    public void MethodToImplement()
    {
        Console.WriteLine("MethodToImplement() called.");
    }
```

C#. 接口（Interface）. 接口定义了所有类继承接口时应遵循的语法合同。. 接口定义了语法合同 "是什么" 部分，派生类定义了语法合同 "怎么做" 部分。. 接口定义了属性、方法和事件，这些都

是接口的成员。. 接口只包含了成员的声明。. 成员的定义是派生类的责任。. 接口提供了派生类应遵循的标准结构。. 接口使得实现接口的类或结构在形式上保持一致

### C#泛型(泛型方法，泛型类，泛型接口，数组)，以及ref关键字引用传递

``` C#
namespace Cshap3
{
    internal class Test<T>//泛型类
    {
        private T _value;
        public Test(T value)
        {
            this._value = value;
        }
        public T GetValue()
        {
            return this._value;
        }
        public ref T Get_ref_Value()
        {
            return ref this._value;
        }
        public void print()
        {
            Console.WriteLine(this._value);
        }
        public void type<T2>()
        {
            Console.WriteLine("泛型模板内也可以写泛型方法，如:"+typeof(T) + " " + typeof(T2));
        }
    }

    internal class Program
    {
        static void Swap<T>(ref T lhs, ref T rhs)//泛型方法
        {
            T temp;
            temp = lhs;
            lhs = rhs;
            rhs = temp;
        }
        public static void TestSwap()
        {
            int a = 1;
            int b = 2;

            Swap<int>(ref a, ref b);//ref关键字表示一个值是通过引用传递的
            System.Console.WriteLine(a + " " + b);
        }

        static void Main(string[] args)
        {
            TestSwap();

            var t = new Test<int>(10);
            var t2 = new Test<string>("******");
            t.Get_ref_Value() = 78;
            t2.Get_ref_Value() = "``````````";
            t.print();
            t.type<int>();
            t2.print();
            t2.type<double>();
            
        }
    }
}

```

#### 泛型和数组

``` C#
        static void Main()
        {
            int[] arr = { 0, 1, 2, 3, 4 };
            List<int> list = new List<int> { 5, 6, 7, 8, 9 };
            ProcessItems(arr);
            ProcessItems(list);
        }
        static void ProcessItems<T>(IList<T> coll)
        {
            // IsReadOnly:为数组返回 True，为列表返回 False。
            System.Console.WriteLine("IsReadOnly returns {0} for this collection.", coll.IsReadOnly);
            foreach (T item in coll)
            {
                System.Console.Write(item.ToString() + " ");
            }
            System.Console.WriteLine();
        }
```

其实也可以直接用泛型函数来接数组

```csharp
static void f<T>(T[] c,T v)
{
    c[1] = v;
}
static void Main(string[] args)
{
    int[] ints = { 1, 2, 3, 4, 5, 6 };
    f(ints, 10);
    foreach(var i in ints){
        Console.Write(i + " ");
    }
}
```



#### 泛型接口

``` C#
interface IMyInterface<T>
    {
        // 接口成员
        void MethodToImplement(T value);
    }
    class Test<T>:IMyInterface<int>
    {
        public T v;

        public void MethodToImplement(int value)
        {
            Console.WriteLine("MethodToImplement() called. vaue= {0}", value);
        }
    }
    class InterfaceImplementer
    {
        static void Main()
        {
            var test = new Test<string>();
            test.v = "hello";
            test.MethodToImplement(6);
            Console.WriteLine(test.v);
        }
    }
```
这里是用泛型类继承实现泛型接口，普通的类也一样

注意，这里的IList表示可按照索引单独访问的对象的集合，自然可以接收数组或list等

只是基本使用，最好还需参考[**微软文档**](https://docs.microsoft.com/zh-cn/dotnet/csharp/programming-guide/generics/generic-interfaces)



### lambda 表达式

将 lambda 表达式的输入参数括在括号中。 使用空括号指定零个输入参数：

```csharp
Action line = () => Console.WriteLine();
```

如果 lambda 表达式只有一个输入参数，则括号是可选的：

```csharp
Func<double, double> cube = x => x * x * x;
```

两个或更多输入参数使用逗号加以分隔：

```csharp
Func<int, int, bool> testForEquality = (x, y) => x == y;
```

有时，编译器无法推断输入参数的类型。 可以显式指定类型，如下面的示例所示：

```csharp
Func<int, string, bool> isTooLong = (int x, string s) => s.Length > x;
```



Action是无返回值的lambda，Func是有返回值的lambda，Func中类型列表的最后一个类型表示的是它要返回的类型

将lambda作为参数传递给函数，使用泛型函数接收，如下:

```csharp
 	internal class Program
    {
        static void F<T,T2>(Func<T,T2> f,T value)
        {
            Console.WriteLine(f(value));
        }
        static void Main(string[] args)
        {
            Func<double, double> cube = x => x * x * x;
            Console.WriteLine(cube(5));
            F(cube,100);
        }
    }
```

其实我们也可以直接像下面这样传参

```csharp
F(x => x * x * x, 100);
```

如果是传递Action，那就更简单了

```csharp
static void A<T1,T2>(Action<T1,T2> c,T1 str,T2 num)
{
    c(str,num);
}
//lambda定义和调用:
Action<string,int> greet = (name,c) =>
{
    string greeting = $"Hello {name}!";
    Console.WriteLine(greeting+c);
};
A(greet, "abcd", 66);
```

我们再总结一下Action与Func的区别，我们写泛型函数接Func的时候，因为Func的第一个类型是传入类型，所以我们的T就用了两次`static void F<T,T2>(Func<T,T2> f,T value)`

Action不需要指定返回值，那么它<>里面的类型也就对应着传入的类型，也就是

`static void A<T1,T2>(Action<T1,T2> c,T1 str,T2 num)`

我们还需要注意一个非常重要的一点，我们不能只传入lambda，让lambda在函数里面再传参，那样是不行的，需要将调用的参数也传入，比如:

```csharp
static void A<T1,T2>(Action<T1,T2> c)
{
    c("ha",6);
}
A(greet);
```

这样是**绝对不可以的**

[微软文档](https://learn.microsoft.com/zh-cn/dotnet/csharp/language-reference/operators/lambda-expressions)说明
