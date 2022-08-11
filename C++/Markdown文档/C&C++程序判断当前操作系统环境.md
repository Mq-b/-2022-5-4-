# C/C++程序判断当前操作系统环境



### 参考[链接](https://iq.opengenus.org/detect-operating-system-in-c/)



## gcc下各个平台宏

|                       |                           |                             |
| :-------------------: | :-----------------------: | :-------------------------: |
|       操作系统        |         宏观呈现          |            笔记             |
| Windows 32 位 + 64 位 |         `_WIN32`          | 适用于所有 Windows 操作系统 |
|      视窗 64 位       |         `_WIN64`          |   仅适用于 64 位 Windows    |
|         苹果          |        `__APPLE__`        |  适用于所有 Apple 操作系统  |
|         苹果          |        `__MACH__`         |          替代上述           |
|      iOS 嵌入式       |   `TARGET_OS_EMBEDDED`    |  包括 TargetConditionals.h  |
|      iOS 刺激器       | `TARGET_IPHONE_SIMULATOR` |  包括 TargetConditionals.h  |
|       苹果手机        |    `TARGET_OS_IPHONE`     |  包括 TargetConditionals.h  |
|       苹果系统        |      `TARGET_OS_MAC`      |  包括 TargetConditionals.h  |
|         安卓          |       `__ANDROID__`       |         linux的子集         |
| 基于 Unix 的操作系统  |        `__unix__`         |                             |
|         Linux         |        `__linux__`        |         Unix的子集          |
|      基于 POSIX       |     `_POSIX_VERSION`      |   带有 Cygwin 的 Windows    |
|       索拉里斯        |          `__sun`          |                             |
|     惠普用户体验      |         `__hpux`          |                             |
|          BSD          |           `BSD`           |        所有 BSD 风格        |
|       蜻蜓 BSD        |      `__DragonFly__`      |                             |
|        自由BSD        |       `__FreeBSD__`       |                             |
|        NetBSD         |       `__NetBSD__`        |                             |
|        OpenBSD        |       `__OpenBSD__`       |                             |

请注意，宏对 GNU GCC 和 G++ 有效，并且可能因其他编译器而异。

## 简单的例子

在下面的示例中，我们专注于检测我们正在运行的 Windows 的风格，它可以是 64 位或 32 位。对于 Windows，我们的表格将是：

|            操作系统            | 宏观呈现 |
| :----------------------------: | :------: |
| Windows 操作系统 32 位 + 64 位 | `_WIN32` |
|     Windows 操作系统 64 位     | `_WIN64` |

与`_WIN32`32 位和 64 位 Windows 操作系统中都存在一样，我们需要首先检查是否存在`_WIN32`以确认它是 Windows 操作系统，然后检查是否存在`_WIN64`以确认它是 64 位 Windows 操作系统还是32 位 Windows 操作系统。

以下是检查 Windows 操作系统的代码：

```c
#include <stdio.h>

int main() 
{
	#ifdef _WIN32 // Includes both 32 bit and 64 bit
	    #ifdef _WIN64
	        printf("Windows 64 bit\n");
	    #else 
	        printf("Windows 32 bit\n");
	    #endif
	#else
	    printf("Not a Windows OS\n");
	#endif
	return 0;
}
```

输出：

```
Windows 32 bit
```

## 苹果操作系统示例

在此示例中，我们使用 Apple OS 的宏来检测正在使用的 Apple OS，例如 MacOS 或 iPhone。

```c
#include <stdio.h>

int main() 
{
	#if __APPLE__
        #include "TargetConditionals.h"
        #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
            printf("iPhone stimulator\n");
        #elif TARGET_OS_IPHONE
            printf("iPhone\n");
        #elif TARGET_OS_MAC
            printf("MacOS\n");
        #else
            printf("Other Apple OS\n");
        #endif
	#else
	    printf("Not an Apple OS\n");
	#endif
	return 0;
}
```

输出：

```
MacOS
```

## 一般示例

在此示例中，我们正在检测我们是否具有 Windows 操作系统或基于 Linux 的操作系统。

```c
#include <stdio.h>

int main() {
	#ifdef _WIN32
	    printf("Windows\n");
	#elif __linux__
	    printf("Linux\n");
	#elif __unix__
	    printf("Other unix OS\n");
	#else
	    printf("Unidentified OS\n");
	#endif
	return 0;
}
```

值得注意的是在Linux发行版中，如Ubuntu下对linux和unix的宏都会定义，一般推荐先判断linux

## 用法

凭借检测语言（在我们的案例中为 C 和 C++）中的操作系统的能力，我们可以编写一个跨平台代码，通过分离平台相关代码来在所有平台上运行。

例子：

```c
#include <stdio.h>

int main() 
{
	#if __APPLE__
	    // apple specific code
	#elif _WIN32
	    // windows specific code
	#elif __LINUX__
	    // linux specific code
	#elif BSD
	    // BSD specific code
	#else
	    // general code or warning
	#endif
	// general code
	return 0;
}
```

同时，我们可以编写针对特定平台优化的代码。例如，一个函数调用可能在所有平台上都受支持，但我们可以针对特定平台（例如 Linux）对其进行大幅优化，但这个新代码会在其他平台上引发错误。在这种情况下，我们可以使用宏来检测它是否是 Linux，对于这种情况，我们可以轻松地使用其他替代优化代码。

例子：

```c
#include <stdio.h>

int main() 
{
	#if __linux__
	    // linux optimized code (will fail in other platforms)
	#else
	    // general code for all platforms
	#endif
	// general code
	return 0;
}
```
