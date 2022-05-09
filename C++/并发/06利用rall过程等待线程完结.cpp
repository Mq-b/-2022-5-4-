#include<iostream>
#include<thread>
class thread_guard {
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) :t(t_) {}
	~thread_guard() {
		/* joinabe成员函数的作用在c++官方文档中是返回线程是否是可结合的。. 可结合的意思就是，一个线程是否能够被执行Join或者是detch操作，
		因为相同的线程不能被join两次，也不能join完再进行detach，同理也不可以被detach两次，所以joinable函数就是判断是否能进行可结合。*/
		if (t.joinable()) {
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};
void do_something() {}
struct func {
	int& i;
	func(int& i_) :i(i_) {}
	void operator()() {
		for (unsigned j = 0; j < 1000000; ++j) {
			do_something();
		}
	}
};
void f() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	do_something();
}
int main() {
	f();
}
//20面下半部分到21页