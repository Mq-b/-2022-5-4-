#include <iostream>                
#include <thread>                
#include <mutex>                
#include <condition_variable>    // std::condition_variable
#include<vector>
std::condition_variable av;
void print(int &i) {
	static std::mutex a;
	std::unique_lock<std::mutex>A(a);
	av.wait(A);						//等待所有线程创建完毕再执行
	std::cout << i++ << std::endl;
}
void go()
{
	av.notify_all();
}
int main() {
	int n = 0;
	std::vector<std::jthread>V;
	for (int i = 0; i < 10; i++)
		V.emplace_back(print,std::ref(n));
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	go();														
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return 0;
}
