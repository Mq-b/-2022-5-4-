#include<iostream>
#include<string>
class Test {
public:
	Test() {
		auto f = [this, m = 0]()mutable{
			int c = 0;
			std::cout << m++ <<' '<<c++ << std::endl;
		};
		f();
		f();
		f();
	}
private:
	int m = 0;
};
int main() {
	int c = 5;
	auto f = [i = 0]()mutable {
		int c = 0; 
		std::cout << i++<<' ' << c++ << std::endl; 
	};
	f();
	f();
	f();

	Test i;
	//在[]内创建的对象，生命周期与lambda一样长
	//差不多是类成员一样，只有lambda销毁才会销毁

	//配合auto一起使用，使用std::string作为成员变量
	auto F = [s = std::string()](auto c)mutable{
		s += c;
		return s;
	};
	F("无聊");
	F("ABCD");
	auto s=F("|||");
	std::cout << s << std::endl;
	//mutabl并非是要改变外部的才加，而是我们需要改变我们自己在[]创建的对象的时候加上它，因为默认是const的
}