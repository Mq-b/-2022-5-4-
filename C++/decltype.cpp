#include<iostream>
int main() {
    decltype(5 + 2) a;
    using str = decltype("123");
    std::cout << typeid(a).name() << std::endl;
    std::cout << typeid(str).name() << std::endl;
    //所以说typedef是根据已有的类型进行推导，这些都是可以的
    std::cout << typeid(decltype(a)).name() << std::endl;
    //当然也能用来做转发，也不再赘述了
    system("pause");
}