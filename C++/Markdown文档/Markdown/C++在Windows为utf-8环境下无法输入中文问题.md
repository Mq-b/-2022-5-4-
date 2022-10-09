# C++在Windows为utf-8环境下无法输入中文问题

原因是:stdin 不支持utf8输入 但支持utf16,shell 支持utf8显示 但不支持显示utf16

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

