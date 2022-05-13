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

   /* int a[2][2]{ {1,2,},{3,4} };
    std::cout << a[0][3] << '\n';*/
    system("pause");
    return 0;
}
