## gcc
1. 编译cpp后缀使用:g++ 文件名 -std=c++版本
比如:`g++ main.cpp -std=c++17`

2. 默认生成的可执行文件名字是:a.out
自行设置:`g++ main.cpp -o main -std=c++17`
注意设置c++标准的std要放到最后面 `-o`空格后面就是要设置生成可执行文件的名字,我们这里设置的是main

3. 设置debug可调式模式的可执行文件`g++ main.cpp -g -o main -std=c++17`
-g表示生成的可执行文件是可调式的 它包含了丰富的调试信息 所以占用的大小明显更大
我们之前没有加-g默认生成的都是release的
可以使用`ls-l`或者`ls-h`进行查看当前目录下文件大小

4. C++程序编译
指定具体的cpp文件 头文件目录要使用`./`跟目录名
`g++ src/insert.cpp src/select.cpp test.cpp -o sort -I ./include`

编译 src 目录下所有的 .cpp 文件 `*`表示所有 `-I`是指定头文件路径
`g++ src/*.cpp test.cpp -o sort -I ./include`

但是这不适合用于管理大型的项目，文件不在一个目录，我们可以使用CMake