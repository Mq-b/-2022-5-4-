#include<iostream>
#include<thread>

void do_something(unsigned) {}
struct func {
	int& i;
	func(int& i_) :i(i_) {}
	void operator()() {
		for (unsigned j = 0; j < 1000000; ++j) {
			do_something(i);
		}
	}
};

void oops() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	/*detach()后子线程在后台独立继续运行，主线程无法再取得子线程的控制权，即使主线程结束，子线程未执行也不会结束。当主线程结束时，由运行时库负责清理与子线程相关的资源。*/
	my_thread.detach();
}

int main() {
	oops();
	//新线程可能仍在运行，主线程的函数结束,然后就回收了,所以有可能导致悬空引用
}
//第18面深入理解
//在19面上半部分谈解决方案