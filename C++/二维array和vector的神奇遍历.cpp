#include<iostream>
#include<vector>
#include<array>

int main()
{
    const int m=10,n=12;
    int y=0;
    std::vector<std::vector<int>>arr(m,std::vector<int>(n,0));//构造初始化
    for(int i=0;i<m;++i)
        for(int j=0;j<n;++j)arr[i][j]=y++;//赋值
    for(int k=0;k<m*n;++k)std::cout<<arr[k/n][k%n]<<' ';//遍历

    std::endl(std::cout);
    //UB遍历array嵌套
    std::array<std::array<int, 10>, 10>A{};
    int* ptr = reinterpret_cast<int*>(&A);//强转
    for (int i = 0; i < 10* 10; ++i) //遍历
        std::cout << ptr[i] << ' '; 

    //对于普通数组，当然可以像下面这样（虽然地址一样，但是安全性暂不清楚）
    int A[4][4]{};
	A[3][3] = 100;
	std::cout << &A[0][1] << std::endl;
	int* ptr = reinterpret_cast<int*>(A);
	for (auto i = 0; i < 16; i++) {
		std::cout << ptr[i] << ' ';
	}
	std::cout << std::endl;
	std::cout << &ptr[1] << std::endl;
    system("pause");
    return 0;
}
