# C++在Windows为utf-8环境下无法输入中文问题

原因是:控制台本身是支持的utf-8输入，utf-16输出，但是stdout和stdin不支持
	使用Windows的API可以正常
	std的则不行

可以使用下面两种方式

```c++
#include <fcntl.h>
#include<iostream>
#include <io.h>
#include<filesystem>
int main()
{
	_setmode(_fileno(stdin), _O_U16TEXT);//将标准输入设置为utf-16
	std::wstring s;
	std::wcin >> s;
	std::cout << std::filesystem::path{ s }.string();
}
```

或者直接使用Windows的API
```C++
#include <iostream>
#include<Windows.h>

int main(){
    DWORD dwChars;
    TCHAR buf[64]{};
    ReadConsole(GetStdHandle(STD_INPUT_HANDLE), buf, 99, &dwChars, nullptr);
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, lstrlen(buf), &dwChars, nullptr);
}
```
