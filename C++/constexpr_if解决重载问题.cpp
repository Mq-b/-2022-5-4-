
#include<string>
#include<stdio.h>
#include<type_traits>
#pragma warning(disable:4996)

template<typename T>
::std::string to_string(const T& t)
{
	if constexpr (std::is_integral_v<T>)
	{
		if constexpr (std::is_signed_v<T>)
		{
			char str[64];
			int len = ::sprintf(str, "%lld", t);
			return ::std::string(str, len);
		}
		else
		{
			char str[64];
			int len = ::sprintf(str, "%llu", t);
			return ::std::string(str, len);
		}
	}
	else
	{
		if constexpr (std::is_signed_v<T>)
		{
			char str[64];
			int len = ::sprintf(str, "%Lg", t);
			return std::string(str, len);
		}
		else return "";
	}
}

int main() {
	::std::string str;

	str = to_string(1234);
	::printf("str=%s\n", str.c_str());

	str = to_string(-1234LL);
	::printf("str=%s\n", str.c_str());

	str = to_string(1234u);
	::printf("str=%s\n", str.c_str());

	str = to_string(56.789);
	::printf("str=%s\n", str.c_str());

	return 0;
}
