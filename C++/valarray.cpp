#include<valarray>
#include<iostream>
int main() {
    int n=0;
	std::valarray<int>arr{};
	arr.resize(10);

	//1. apply（）：-该函数立即将其参数中给出的操作应用于所有valarray元素，并返回具有操作值的新valarray。
    std::valarray<int>arr2=arr.apply([](int i){return i+5;});
    for(auto i:arr2)
        std::cout<<i<<' ';
    std::cout<<std::endl;

    //2.max(),min()
    std::cout<<arr2.max()<<' '<<arr2.min()<<std::endl;

    //3.std::valarray::cshift 循环移动
    for(int i=0;i<10;i++)
        arr2[i]=i;

    for(auto i:arr2)
        std::cout<<i<<' ';
    std::cout<<std::endl;
    arr2=arr2.cshift(-2);   //正数向左移动，负数向右移动
     for(auto i:arr2)
        std::cout<<i<<' ';

    arr2*=10;
    for(auto i:arr2)
        std::cout<<i<<' ';
    system("pause");
}
//还有swap，迭代器之类的，不过无伤大雅
