#include<iostream>
#include<thread>
class background_task {
public:
	void operator()()const {}
};

int main() {
	//std::thread my_thread(background_task());//本意是发起新的线程，传递一个匿名函数对象，但是会被解释为函数声明
	
	//解决方式是再加一个小括号，或者使用新语法初始化列表替代小括号的方式,两种选一种就行，推荐使用初始化列表，或者lambda表达式
	
	//std::thread my_thread{ background_task() };
	std::thread my_thread((background_task()));
	my_thread.join();

	//lambda的写法，没啥区别，我们这里直接写空
	std::thread my_thread2([] {});
	my_thread2.join();

}
//在第17面对此有详细的介绍