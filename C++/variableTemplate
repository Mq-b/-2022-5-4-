#include<iostream>

template<typename T>
class MyClass {
public:
	static constexpr int max = 1000;
};

template<typename T>
int myMax = MyClass<T>::max;

template<typename T>
T b=100;

int main()
{
    int a=myMax<int>;
    std::cout<<a<<std::endl;
    //而不再需要
    int i=MyClass<int>::max;

    //或者直接创建
    std::cout<<b<int><<std::endl;

    system("pause");
}
//变量模板不是局部变量，是另一种全局变量,main函数内是使用不是实例化也不是创建
