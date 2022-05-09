#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

std::mutex I;

void f(int& i) {
	I.lock();
	std::cout << i++ << std::endl;
	I.unlock();
}
void g(int& i) {
	std::lock_guard<std::mutex>a(I);
	std::cout << i++ << std::endl;
}
int main() {
	int n = 1;
	std::vector<std::jthread>a;
	for (int i = 0; i < 10; i++) {
		//a.emplace_back(f, std::ref(n));		//这是lock版本的
		a.emplace_back(g, std::ref(n));
	}
	/*for (auto& i : a) {				//因为使用了C++20的jthread，所以不需要join了
		i.join();
	}*/
}