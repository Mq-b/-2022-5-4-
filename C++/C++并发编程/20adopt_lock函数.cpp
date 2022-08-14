#include<iostream>
#include<mutex>
#include<thread>

//std::lock_guard的std::adopt_lock参数
//std::adopt_lock是个结构体对象，起一个标记作用：作用就是表示这个互斥量已经lock()，
//不需要再std::lock_guard<std::mutext>构造函数里面对mutex对象再次进行lock()了
//如果已经lock而继续普通std::lock_guard<std::mutext>没有adopt_lock参数就会报错

std::mutex test5_mutex;//测试5的锁
void test5() {
	test5_mutex.lock();		//可以是成员函数的lock，也可以是19的std::lock()
	std::lock_guard<std::mutex> lg(test5_mutex, std::adopt_lock);
	std::cout << "hello test5" <<std:: endl;
}
void test5(int) {//对照
	std::lock_guard<std::mutex>a(test5_mutex);
	std::cout << "hello test5(int)" << std::endl;
}

int main() {
	std::thread t1([] { test5(); });//调用第一个test5函数
	std::thread t2([] { test5(2); });//调用第二个test5函数

	t1.join();
	t2.join();
	return 0;
}