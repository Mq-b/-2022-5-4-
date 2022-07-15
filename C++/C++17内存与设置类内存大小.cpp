#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory_resource>
struct alignas(32) MyType32 {

};

auto p = new MyType32;
int main()
{
	// 在栈上分配一些内存：
	std::array<std::byte, 200000> buf;
	std::pmr::monotonic_buffer_resource pool{ buf.data(), buf.size() };
	std::pmr::vector<std::pmr::string> coll{ &pool };
	coll.emplace_back("无趣");
	std::cout << "无趣" << std::endl;

	std::cout << sizeof MyType32;
}