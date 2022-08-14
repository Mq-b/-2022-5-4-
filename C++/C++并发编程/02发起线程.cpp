#include<iostream>
#include<thread>
void do_some_work(){}
class background_task {
public:
	void operator()()const {
		do_some_work();
	}
};
int main() {
	background_task f;
	std::thread my_thread(f);
	my_thread.join();
}
//函数对象，lambda表达式，函数指针等都可以，这里是使用函数对象