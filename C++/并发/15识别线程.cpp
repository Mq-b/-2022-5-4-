#include<iostream>
#include<thread>
int main(){
	std::thread a([]() {});
	std::cout << a.get_id() << std::endl;
	a.detach();
	//thread对象必须关联了线程才能获取到id，如果没有，则会返回一个std::thread::id对象，它按照默认构造方式生成，表示“线程不存在”

	//其次当前线程的ID可以通过调用std::this_thread::get_id()获得,如下
	std::cout << std::this_thread::get_id() << std::endl;
	std::thread b([]() {std::cout << std::this_thread::get_id() << std::endl; });
	b.join();
}