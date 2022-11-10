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

我们还需要注意一个非常重要的一点，我们不能只传入lambda，让lambda在函数里面再传参，那样是不行的，比如将调用的参数也通过泛型函数传入，比如:

```csharp
static void A<T1,T2>(Action<T1,T2> c)
{
    c("ha",6);
}
A(greet);
```

这样是**绝对不可以的**

[微软文档](https://learn.microsoft.com/zh-cn/dotnet/csharp/language-reference/operators/lambda-expressions)说明



### 元组

它使用非常的简单，我们直接举一个鸡兔同笼返回两个int的例子

```c#
private static (int,int) F()
{
    for(int i = 1; i < 35; i++)
    {
        for(int j =1; j < 35; j++)
        {
            int x = i * 2 + j * 4;
            int y = i + j ;
            if(x ==94&&y ==35)
            {
                return (i, j);
            }
        }
    }
    return (0, 0);
}
```



### 可变参数

```c#
static void print<T>(params T[] list)
{
    foreach(var item in list)
    {
        Console.Write("{0} ",item);
    }
    Console.WriteLine();
}

static void print(params char[] list)//如果传递的是数组则为按引用传递
{
    for(int i = 0; i < list.Length; i++)
    {
        list[i] = '*';
    }
}

static void Main(string[] args)
{
    print(1, 2, 3, 4, 5, 6);
    print("1", "2", "3", "4", "5", "6");
    char[] str = { '1', '2', '3', '4','5','6' };
    Console.WriteLine(str);
    print(str);
    Console.WriteLine(str);
}
```



### dynamic关键词

```csharp
internal class Program
{
    public static void print(params dynamic[] dunamics)
    {
        foreach (dynamic dunamic in dunamics)//dynamic可以从object数组的元素得到真正的类型
        {
            Console.Write(dunamic);
        }
        Console.WriteLine();
    }
    static void Main(string[] args)
    {
        print(1, '*', 5.6, "哈哈");
    }
```

dynamic是FrameWork4.0的新特性。dynamic的出现让C#具有了弱语言类型的特性。编译器在编译的时候不再对类型进行检查，编译期默认dynamic对象支持你想要的任何特性。比如，即使你对GetDynamicObject方法返回的对象一无所知，你也可以像如下那样进行代码的调用，编译器不会报错

常有人会拿var这个关键字来和dynamic做比较。实际上，var和dynamic完全是两个概念，根本不应该放在一起做比较。var实际上是编译期抛给我们的“语法糖”，一旦被编译，编译期会自动匹配var 变量的实际类型，并用实际类型来替换该变量的申明，这看上去就好像我们在编码的时候是用实际类型进行申明的。而dynamic被编译后，实际是一个object类型，只不过编译器会对dynamic类型进行特殊处理，让它在编译期间不进行任何的类型检查，而是将类型检查放到了运行期。

### 运算符重载

```c++
class Box
{
    private double length;      // 长度
    private double breadth;     // 宽度
    private double height;      // 高度

    public Box(double length, double breadth, double height)
    {
        this.length = length;
        this.breadth = breadth;
        this.height = height;
    }

    public double getVolume()
    {
        return length * breadth * height;
    }
    public void setLength(double len)
    {
        length = len;
    }
    public void setBreadth(double bre)
    {
        breadth = bre;
    }
    public void setHeight(double hei)
    {
        height = hei;
    }
    public static Box operator +(Box b, Box c)
    {
        Box box = new Box(0,0,0);
        box.length = b.length + c.length;
        box.breadth = b.breadth + c.breadth;
        box.height = b.height + c.height;
        return box;
    }

```

**C# 要求所有的运算符重载都声明为 public 和 static ， 这表示它们与其类或结构相关联， 而不是与某个特定实例相关联，所有运算符重载的代码体不能访问非静态类成员**

|                        操作符                         |                     描述                     |
| :---------------------------------------------------: | :------------------------------------------: |
|            `+`, `-`, `!`, `~`, `++`, `--`             | 这些一元运算符需要一个操作数，并且可以重载。 |
|                `+`, `-`, `*`, `/`, `%`                |  这些二进制运算符取一个操作数并且可以重载。  |
|           `==`, `!=`, `<`, `>`, `<=`, `>=`            |           这些比较运算符都可以重载           |
|                      `&&`, `//`                       |         条件逻辑运算符不能直接重载。         |
|             `+=`， `-=`,`*=`，`/=`，`％=`             |            赋值运算符不能被重载。            |
| `=`, `.`, `?:`, `->`, `new`, `is`, `sizeof`, `typeof` |             这些运算符不能重载。             |

---

### C#断言和反射

```csharp
static void Main(string[] args)
{
    int i = 42;
    Type type = i.GetType();//反射，运行期获得类型
    Console.WriteLine(type);
    Trace.Assert(type != null);
}
```



## WinForm入门图形界面GUI

### 创建窗口与添加控件按钮事件点击和MessagBox

Program.cs

```csharp
namespace WinForms01
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.Run(new MyForm());
        }
    }
}
```

Myform.cs

```csharp
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WinForms01
{
    internal class MyForm:Form
    {
        private Button button1 = new Button();
        private Button button2 = new Button(); 

        public MyForm()
        {
            this.Text = "我的小窗口";//窗口名称
            InitializeComponent();

            this.Controls.Add(button2);//手动添加按钮
            button2.Text = "代码添加的按钮";
            button2.Location = new Point(40, 40);
            button2.Size = new Size(100, 40);
            this.button2.Click += new System.EventHandler(this.oneClick);
        }

        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(163, 89);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(104, 50);
            this.button1.TabIndex = 0;
            this.button1.Text = "测试按钮";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // MyForm
            // 
            this.ClientSize = new System.Drawing.Size(481, 261);
            this.Controls.Add(this.button1);
            this.Name = "MyForm";
            this.ResumeLayout(false);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.button1.Text = "测试按钮被按下";
            MessageBox.Show("你点击了测试按钮");
        }
        private void oneClick(object sender,EventArgs e)
        {
            MessageBox.Show("代码写的按钮被你点击了");
        }
    }
}
```

我们既可以使用可视化的方式添加控件和修改属性，也可以自己写代码，我们使用可视化的方式修改后会自己生成代码。

vs创建项目后悔自动生成两个这样的文件，我们是全部删了后自己写的

我们给button1绑定了一个函数，当它按下的时候函数就会执行

button1是使用图形化的方式创建的和双击添加的默认点击执行事件，button2是我们自己用代码实现的

除了click的事件，还能写很多别的，在vs的属性界面有显示



### 练习:显示时间

先介绍**partial**

C# 2.0 引入了局部类型的概念。局部类型允许我们将一个类、结构或接口分成几个部分，分别实现在几个不同的.cs文件中。

局部类型适用于以下情况：

(1) 类型特别大，不宜放在一个文件中实现。

(2) 一个类型中的一部分代码为自动化工具生成的代码，不宜与我们自己编写的代码混合在一起。

(3) 需要多人合作编写一个类。

局部类型是一个纯语言层的编译处理，不影响任何执行机制——事实上C#编译器在编译的时候仍会将各个部分的局部类型合并成一个完整的类。

如果使用vs创建默认的WinForm项目，那么它就是这样的，下面我们看代码实现



Program.cs

```csharp
using System;
using System.Windows.Forms;

namespace WindowsForms02
{
    internal static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
```

Form1.cs 

```csharp
using System;
using System.Windows.Forms;
namespace WindowsForms02
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void OnButtonClick(object sender, EventArgs e)
        {
            string timeStr = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            timeField.Text = timeStr;
        }
    }
}
```

Form1.Designer.cs

```csharp
namespace WindowsForms02
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.timeField = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(213, 84);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(103, 32);
            this.button1.TabIndex = 0;
            this.button1.Text = "显示时间";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.OnButtonClick);
            // 
            // timeField
            // 
            this.timeField.Location = new System.Drawing.Point(122, 142);
            this.timeField.Name = "timeField";
            this.timeField.Size = new System.Drawing.Size(294, 21);
            this.timeField.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(543, 281);
            this.Controls.Add(this.timeField);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox timeField;
    }
}
```

Form1.Designer.cs里面的代码其实就是我们在设计界面修改添加的控件与属性，Form1.cs 我们其实只是写了一个回调的函数

### 文本框TextBox

Form1.Designer.cs

```csharp
namespace WinForms04
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.NameBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // NameBox
            // 
            this.NameBox.ForeColor = System.Drawing.SystemColors.Highlight;
            this.NameBox.Location = new System.Drawing.Point(245, 79);
            this.NameBox.Multiline = true;
            this.NameBox.Name = "NameBox";
            this.NameBox.Size = new System.Drawing.Size(243, 70);
            this.NameBox.TabIndex = 0;
            this.NameBox.Text = "Test";
            this.NameBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.ONMyKeyPress);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.NameBox);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private TextBox NameBox;
    }
}
```

Form1.cs

```csharp
namespace WinForms04
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void ONMyKeyPress(object sender, KeyPressEventArgs e)
        {
            var ch = e.KeyChar;//获取输入的字符
            if(ch == '\r')
            {
                string str = NameBox.Text;//获取文本框上的字符串
                MessageBox.Show(str,"对话框");
            }
        }
    }
}
```



### 复选框CheckBox

Form1.Designer.cs

```csharp
namespace WinForms05
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Password = new System.Windows.Forms.TextBox();
            this.MyCheckBox = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // Password
            // 
            this.Password.Location = new System.Drawing.Point(255, 47);
            this.Password.Name = "Password";
            this.Password.PasswordChar = '*';
            this.Password.Size = new System.Drawing.Size(182, 27);
            this.Password.TabIndex = 0;
            this.Password.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.Password_KeyPress);
            // 
            // MyCheckBox
            // 
            this.MyCheckBox.AutoSize = true;
            this.MyCheckBox.Location = new System.Drawing.Point(328, 103);
            this.MyCheckBox.Name = "MyCheckBox";
            this.MyCheckBox.Size = new System.Drawing.Size(91, 24);
            this.MyCheckBox.TabIndex = 1;
            this.MyCheckBox.Text = "显示密码";
            this.MyCheckBox.UseVisualStyleBackColor = true;
            this.MyCheckBox.Click += new System.EventHandler(this.MyCheckBox_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.MyCheckBox);
            this.Controls.Add(this.Password);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private TextBox Password;
        private CheckBox MyCheckBox;
    }
}
```

Form1.cs

```csharp
namespace WinForms05
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Password_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '\r')
            {
                string str = Password.Text;
                MessageBox.Show(str, "你输入的密码:");
            }
        }

        private void MyCheckBox_Click(object sender, EventArgs e)
        {
            bool isChecked = MyCheckBox.Checked;
            if (isChecked)//判断当前有没有选中
            {
                Password.PasswordChar = '\0';//设置为明文显示
            }
            else
            {
                Password.PasswordChar = '*';
            }
        }
    }
}
```

其实重点只是在于最后一个函数，和Check事件而已，当复选框被点击的时候此信号被触发，然后使用Checked知道当前复选框是否是被选择状态，再进行设置



### 下拉列表ComboBox



Form1.Designer.cs

```csharp
namespace WinForms06
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "离谱"});
            this.comboBox1.Location = new System.Drawing.Point(271, 49);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(151, 28);
            this.comboBox1.TabIndex = 0;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(328, 105);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(94, 29);
            this.button1.TabIndex = 1;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.comboBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private ComboBox comboBox1;
        private Button button1;
    }
}
```

Form1.cs

```csharp
namespace WinForms06
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            //手动添加一些
            comboBox1.Items.Add("red");
            comboBox1.Items.Add("green");
            comboBox1.Items.Add("blue");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //SelectedItem:选中的值，null表示未选中
            //SelectedIndex:选中项的索引，-1表示未选中
            int index = comboBox1.SelectedIndex;
            string sel = (string)comboBox1.SelectedItem;
            if (index != -1 || sel != null)
            {
                MessageBox.Show("选中了: " + sel + " 索引是: " + index);
            }
            else
            {
                MessageBox.Show("你未选中任何");
            }
        }
    }
}
```



### 列表框listBox

Form1.Designer.cs

```csharp
namespace WinForms07
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 20;
            this.listBox1.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "red"});
            this.listBox1.Location = new System.Drawing.Point(200, 90);
            this.listBox1.Name = "listBox1";
            this.listBox1.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
            this.listBox1.Size = new System.Drawing.Size(262, 164);
            this.listBox1.TabIndex = 0;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.listBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private ListBox listBox1;
    }
}
```

Form1.cs

```csharp
namespace WinForms07
{
    class Student
    {
        public int Id { get; set; }
        public string Name { get; set; }

        public Student(int id, string name)
        {
            Id = id;
            Name = name;
        }
        public override string ToString()//所有类型都隐式继承Object，这里是重写
        {
            return String.Format("{0}  {1}",Id,Name);
        }
    }
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            //列表框能添加任意类型，我们这里就使用自定义数据类型，它显示的结果就是ToString的
            listBox1.Items.Add(new Student(1, "武庚"));
            listBox1.Items.Add(new Student(2, "白菜"));
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string str=" ";
            foreach(var i in listBox1.SelectedIndices)
            {
                str += i.ToString()+'\n';
            }
            MessageBox.Show("选中了: " + str);
        }
    }
}
```



### 学生信息编辑保存Json

Form1.Designer.cs

```csharp
namespace WinForms08
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.idFiled = new System.Windows.Forms.TextBox();
            this.nameField = new System.Windows.Forms.TextBox();
            this.sexFiled = new System.Windows.Forms.TextBox();
            this.phoneFiled = new System.Windows.Forms.TextBox();
            this.button = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(152, 72);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(39, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "学号";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(152, 120);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 20);
            this.label2.TabIndex = 1;
            this.label2.Text = "姓名";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(152, 176);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 20);
            this.label3.TabIndex = 2;
            this.label3.Text = "性别";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(136, 216);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(54, 20);
            this.label4.TabIndex = 3;
            this.label4.Text = "手机号";
            // 
            // idFiled
            // 
            this.idFiled.Location = new System.Drawing.Point(256, 72);
            this.idFiled.Name = "idFiled";
            this.idFiled.Size = new System.Drawing.Size(168, 27);
            this.idFiled.TabIndex = 4;
            // 
            // nameField
            // 
            this.nameField.Location = new System.Drawing.Point(256, 120);
            this.nameField.Name = "nameField";
            this.nameField.Size = new System.Drawing.Size(168, 27);
            this.nameField.TabIndex = 5;
            // 
            // sexFiled
            // 
            this.sexFiled.Location = new System.Drawing.Point(256, 176);
            this.sexFiled.Name = "sexFiled";
            this.sexFiled.Size = new System.Drawing.Size(168, 27);
            this.sexFiled.TabIndex = 6;
            // 
            // phoneFiled
            // 
            this.phoneFiled.Location = new System.Drawing.Point(256, 216);
            this.phoneFiled.Name = "phoneFiled";
            this.phoneFiled.Size = new System.Drawing.Size(168, 27);
            this.phoneFiled.TabIndex = 7;
            // 
            // button
            // 
            this.button.Location = new System.Drawing.Point(137, 293);
            this.button.Name = "button";
            this.button.Size = new System.Drawing.Size(102, 36);
            this.button.TabIndex = 8;
            this.button.Text = "保存";
            this.button.UseVisualStyleBackColor = true;
            this.button.Click += new System.EventHandler(this.button_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(527, 367);
            this.Controls.Add(this.button);
            this.Controls.Add(this.phoneFiled);
            this.Controls.Add(this.sexFiled);
            this.Controls.Add(this.nameField);
            this.Controls.Add(this.idFiled);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private TextBox idFiled;
        private TextBox nameField;
        private TextBox sexFiled;
        private TextBox phoneFiled;
        private Button button;
    }
}
```

Form1.cs

```csharp
using Newtonsoft.Json;
using System.Net.Http.Json;
using System.Text.Json.Serialization;

namespace WinForms08
{
    class Student
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public bool Sex { get; set; }
        public string Phone { get; set; }
        public Student()
        {

        }
        public Student(int Id, string Name, bool Sex, string Phone)
        {
            this.Id = Id;
            this.Name = Name;
            this.Sex = Sex;
            this.Phone = Phone;
        }
    }
        public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, EventArgs e)
        {
            Student stu = new Student();
            stu.Id=Convert.ToInt32(idFiled.Text);
            stu.Name=nameField.Text; 
            stu.Phone = phoneFiled.Text;
            stu.Sex = sexFiled.SelectedText != null;

            //JSON支持
            string jsonStr = JsonConvert.SerializeObject(stu);//序列化
            JsonSerializer serializer = new JsonSerializer();
            using (StreamWriter sw = new StreamWriter("json.json"))
            using (JsonWriter writer = new JsonTextWriter(sw))
            {
                 serializer.Serialize(writer, jsonStr);
            }
        }
    }
}
```



### 图片框PictureBox

Form1.Designer.cs

```csharp
namespace WinForms09
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(800, 450);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.pictureBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }
        #endregion

        private PictureBox pictureBox1;
    }
}
```

Form1.cs

```csharp
namespace WinForms09
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            Bitmap img = new Bitmap("D:\\自用\\vs的c++\\WinForms09\\新素材\\1 (107).jpg");
            int w = img.Width;
            int h = img.Height;
            //设置缩放模式
            pictureBox1.SizeMode = PictureBoxSizeMode.Zoom;
            pictureBox1.Image = img;//将图片放到控件中

            //也可以直接加载图片文件
            pictureBox1.Load("D:\\自用\\vs的c++\\WinForms09\\新素材\\1 (108).jpg");
            
        }
    }
}
```

### 资源文件

资源文件的使用很简单，我们只需要点开项目的`Resources.resx`文件然后手动添加即可，这里是添加了一个图片

添加后使用的代码:

```csharp
Bitmap photo = Properties.Resources.img;
w = photo.Width;
h = photo.Height;
pictureBox1.Image = photo;//把图片放入到控件中
```

资源文件是直接打包到exe中，就算我们后来直接把图片删除也不影响exe运行



### 简易计算器

![](https://github.com/13870517674/-2022-5-4-/blob/main/C%EF%BC%83/image/01.png)

**Form1.Designer.cs**

```c#
namespace WinForms10
{
    partial class 计算器
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.button12 = new System.Windows.Forms.Button();
            this.button13 = new System.Windows.Forms.Button();
            this.button14 = new System.Windows.Forms.Button();
            this.button15 = new System.Windows.Forms.Button();
            this.button16 = new System.Windows.Forms.Button();
            this.button17 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button1.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button1.Location = new System.Drawing.Point(20, 66);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(68, 52);
            this.button1.TabIndex = 0;
            this.button1.Text = "1";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button2.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button2.Location = new System.Drawing.Point(107, 66);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(68, 52);
            this.button2.TabIndex = 0;
            this.button2.Text = "2";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.button1_Click);
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button3.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button3.Location = new System.Drawing.Point(195, 66);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(68, 52);
            this.button3.TabIndex = 0;
            this.button3.Text = "3";
            this.button3.UseVisualStyleBackColor = false;
            this.button3.Click += new System.EventHandler(this.button1_Click);
            // 
            // button4
            // 
            this.button4.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button4.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button4.Location = new System.Drawing.Point(20, 139);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(68, 52);
            this.button4.TabIndex = 0;
            this.button4.Text = "4";
            this.button4.UseVisualStyleBackColor = false;
            this.button4.Click += new System.EventHandler(this.button1_Click);
            // 
            // button5
            // 
            this.button5.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button5.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button5.Location = new System.Drawing.Point(107, 139);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(68, 52);
            this.button5.TabIndex = 0;
            this.button5.Text = "5";
            this.button5.UseVisualStyleBackColor = false;
            this.button5.Click += new System.EventHandler(this.button1_Click);
            // 
            // button6
            // 
            this.button6.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button6.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button6.Location = new System.Drawing.Point(195, 139);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(68, 52);
            this.button6.TabIndex = 0;
            this.button6.Text = "6";
            this.button6.UseVisualStyleBackColor = false;
            this.button6.Click += new System.EventHandler(this.button1_Click);
            // 
            // button7
            // 
            this.button7.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button7.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button7.Location = new System.Drawing.Point(20, 215);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(68, 52);
            this.button7.TabIndex = 0;
            this.button7.Text = "7";
            this.button7.UseVisualStyleBackColor = false;
            this.button7.Click += new System.EventHandler(this.button1_Click);
            // 
            // button8
            // 
            this.button8.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button8.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button8.Location = new System.Drawing.Point(107, 215);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(68, 52);
            this.button8.TabIndex = 0;
            this.button8.Text = "8";
            this.button8.UseVisualStyleBackColor = false;
            this.button8.Click += new System.EventHandler(this.button1_Click);
            // 
            // button9
            // 
            this.button9.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button9.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button9.Location = new System.Drawing.Point(195, 215);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(68, 52);
            this.button9.TabIndex = 9;
            this.button9.Text = "9";
            this.button9.UseVisualStyleBackColor = false;
            this.button9.Click += new System.EventHandler(this.button1_Click);
            // 
            // button10
            // 
            this.button10.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button10.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button10.Location = new System.Drawing.Point(20, 286);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(68, 52);
            this.button10.TabIndex = 0;
            this.button10.Text = "0";
            this.button10.UseVisualStyleBackColor = false;
            this.button10.Click += new System.EventHandler(this.button1_Click);
            // 
            // button11
            // 
            this.button11.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button11.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button11.Location = new System.Drawing.Point(107, 286);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(68, 52);
            this.button11.TabIndex = 0;
            this.button11.Text = ".";
            this.button11.UseVisualStyleBackColor = false;
            this.button11.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(20, 12);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Horizontal;
            this.textBox1.Size = new System.Drawing.Size(333, 36);
            this.textBox1.TabIndex = 10;
            // 
            // button12
            // 
            this.button12.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button12.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button12.Location = new System.Drawing.Point(285, 66);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(153, 52);
            this.button12.TabIndex = 0;
            this.button12.Text = "C";
            this.button12.UseVisualStyleBackColor = false;
            this.button12.Click += new System.EventHandler(this.button12_Click);
            // 
            // button13
            // 
            this.button13.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button13.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button13.Location = new System.Drawing.Point(282, 139);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(68, 52);
            this.button13.TabIndex = 0;
            this.button13.Text = "+";
            this.button13.UseVisualStyleBackColor = false;
            this.button13.Click += new System.EventHandler(this.button13_Click);
            // 
            // button14
            // 
            this.button14.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button14.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button14.Location = new System.Drawing.Point(282, 215);
            this.button14.Name = "button14";
            this.button14.Size = new System.Drawing.Size(68, 52);
            this.button14.TabIndex = 0;
            this.button14.Text = "-";
            this.button14.UseVisualStyleBackColor = false;
            this.button14.Click += new System.EventHandler(this.button13_Click);
            // 
            // button15
            // 
            this.button15.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button15.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button15.Location = new System.Drawing.Point(370, 139);
            this.button15.Name = "button15";
            this.button15.Size = new System.Drawing.Size(68, 52);
            this.button15.TabIndex = 0;
            this.button15.Text = "*";
            this.button15.UseVisualStyleBackColor = false;
            this.button15.Click += new System.EventHandler(this.button13_Click);
            // 
            // button16
            // 
            this.button16.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button16.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button16.Location = new System.Drawing.Point(370, 215);
            this.button16.Name = "button16";
            this.button16.Size = new System.Drawing.Size(68, 52);
            this.button16.TabIndex = 9;
            this.button16.Text = "/";
            this.button16.UseVisualStyleBackColor = false;
            this.button16.Click += new System.EventHandler(this.button13_Click);
            // 
            // button17
            // 
            this.button17.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button17.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button17.Location = new System.Drawing.Point(195, 286);
            this.button17.Name = "button17";
            this.button17.Size = new System.Drawing.Size(243, 52);
            this.button17.TabIndex = 0;
            this.button17.Text = "=";
            this.button17.UseVisualStyleBackColor = false;
            this.button17.Click += new System.EventHandler(this.button17_Click);
            // 
            // 计算器
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(509, 404);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button16);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.button15);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button12);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button14);
            this.Controls.Add(this.button17);
            this.Controls.Add(this.button11);
            this.Controls.Add(this.button13);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button10);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button1);
            this.Name = "计算器";
            this.Text = "计算器";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Button button1;
        private Button button2;
        private Button button3;
        private Button button4;
        private Button button5;
        private Button button6;
        private Button button7;
        private Button button8;
        private Button button9;
        private Button button10;
        private Button button11;
        private TextBox textBox1;
        private Button button12;
        private Button button13;
        private Button button14;
        private Button button15;
        private Button button16;
        private Button button17;

        private double num = 0;
        private string s = "";
        private string f = "";
    }
}
```

17的Button按钮和一个文本框，以及三个为了计算的成员变量

**Program.cs**

```c#
namespace WinForms10
{
    public partial class 计算器 : Form
    {
        public 计算器()
        {
            InitializeComponent();
        }

        private void button12_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            s = "";
            num = 0;
            f = "";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var t = (Button)sender;
            textBox1.Text += t.Text;
            s += t.Text;
        }

        private void button13_Click(object sender, EventArgs e)
        {
            var t = (Button)sender;
            var t2 = t.Text;

            if (f == t2)
            {
                if (f == "+") num += Convert.ToDouble(s);
                else if (f == "-") num -= Convert.ToDouble(s);
                else if (f == "*") num *= Convert.ToDouble(s);
                else if (f == "/") num /= Convert.ToDouble(s);
            }
            else
            {
                num = Convert.ToDouble(s);
            }
            s = "";
            textBox1.Text += t2;
            f = t2;
        }

        private void button17_Click(object sender, EventArgs e)
        {
            double tmp = Convert.ToDouble(s);
            if (f == "+")
            {
                textBox1.Text = "";
                textBox1.Text +=  (num + tmp);
                num = (num + tmp);
                s = Convert.ToString(num);
            }
            if (f == "-")
            {
                textBox1.Text = "";
                textBox1.Text +=  (num - tmp);
                num = (num + tmp);
                s = Convert.ToString(num);

            }
            if (f == "*")
            {
                textBox1.Text = "";
                textBox1.Text +=  (num * tmp);
                num = (tmp * num);
                s = Convert.ToString(num);

            }
            if (f == "/")
            {
                textBox1.Text =" ";
                textBox1.Text +=  (num / tmp);
                num = (tmp / num);
                s = Convert.ToString(num);

            }
        }
    }
}
```

只有四个部分，

1. 清零
2. 数字输入，0-9和.这些按钮的点击事件都被关联到button1_Click函数
3. 运算符，加减乘除，都使用button13_Click函数
4. =号

计算器支持`5*2*3=` `5-3-1=`，或`5*2*4=-6(这里指5*2*4的结果-6)` 不支持`5*2+3`
