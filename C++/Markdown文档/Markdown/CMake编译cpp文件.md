我们在Ubuntu22.04环境下测试，要求必须有CMake，Make的环境

假设有一个main.cpp的文件

```c++
#include<iostream>
int main(){
    std::cout<<"6666\n";
}
```

我们写一个CMakeList.txt

```cmake
cmake_minimum_required(VERSION 3.10) 
project(Test) 
add_executable(Test main.cpp) 
```

只需要这些即可，打开终端，输入

```cmake
cmake .
#此时的文件如下,生成了Makefile和CMakeFiles等
CMakeCache.txt  cmake_install.cmake  main.cpp
CMakeFiles      CMakeLists.txt       Makefile
#生成完毕后就可以使用make进行编译了，它将产生可执行文件
make
##将产生一个和项目名一样的可执行文件，我们这里就是Test，然后执行即可
```

