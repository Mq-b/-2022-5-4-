#include<thread>
#include<iostream>
#include<vector>
#include<mutex>

std::mutex p;

void do_word(int &id) {
	{
		std::lock_guard<std::mutex>a(p);//上锁
		std::cout << ++id << '\n';
	}
}
void f() {
	int a = 1;
	std::vector<std::thread>threads;
	for (unsigned i = 0; i < 20; ++i) {
		threads.emplace_back(do_word, std::ref(a));//生成主线程，此成员函数在C++14添加
	}
	for (auto& entry : threads)
		entry.join();
}
int main() {
	f();
}
//因为线程之间的运行速度不一样，所以结果一般都不一样,资源争夺，当thread对象创建好的时候子线程开始运行
//4月27我们给这个程序加了一些改进，加入互斥，锁住了，所以线程不再争夺