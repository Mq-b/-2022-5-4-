#include<iostream>
#include<thread>
#include<Windows.h>

void do_something(unsigned) { std::cout << 1 << ' '; }
struct func {
	int& i;
	func(int& i_) :i(i_) {}
	void operator()() {
		for (unsigned j = 0; j < 10; ++j) {
			do_something(i);
		}
	}
};
class scoped_thread {
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) :t(std::move(t_)) {
		if (!t.joinable())
			throw std::logic_error("NO thread");//抛异常，当这个线程不能被结合，也就是join或者death的时候就抛出异常
												//使用std::logic_error其实和普通的没啥区别，但是好管理一些，看起来标准
	}
	~scoped_thread() {
		//join 等待线程结束 如果没结束就卡在join里面直到结束,执行太快了，我误以为是要join才会打印，其实不需要，我们加一个Sleep就看出来了
		//子线程是一个循环，我们这个函数太短了，运行完的时候子线程函数还没运行完，就需要在join卡住才能执行完
		Sleep(1000);
		t.join();
	}
	//scoped_thread(std::thread const&) = delete;
	scoped_thread operator=(scoped_thread const&) = delete;
};
void f() {
	int some_local_state = 0;
	scoped_thread t{ std::thread(func(some_local_state)) };
}
int main() {
	f();
}