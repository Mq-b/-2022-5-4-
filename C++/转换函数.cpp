#include<iostream>
class A {
public:
    A(int n) :m(n) {}

    operator int() {//重载int()
        return m;
    }
private:
    int m;
};

int main() {
    A n(10);

    std::cout <<int(n) << std::endl;//相当于重载了int()运算发，调用方式就是这样直接
}