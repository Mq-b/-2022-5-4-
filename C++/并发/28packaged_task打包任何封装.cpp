#include<iostream>
#include<thread>
#include<mutex>
#include<future>
#include<vector>

int mythread(int i) {	//线程入口函数
	std::cout << i << std::endl;
	std::cout << "mythread() start " << "threadid=" << std::this_thread::get_id() << std::endl;//打印新线程id
	std::chrono::milliseconds dura(1000);//延时一秒
	std::this_thread::sleep_for(dura);
	std::cout << "mythread() end " << "threadid=" << std::this_thread::get_id() << std::endl;
	return 5;
}
void test() {		//直接调用,所在的线程和主线程是同一个线程
	std::packaged_task<int(int)>mypt(mythread);
	mypt(100);
	std::future<int>result = mypt.get_future();
	std::cout << result.get() << std::endl;
}
int main() {
/*二、std::pakcaged_task：打包任务，把任务包装起来。
类模板，它的模板参数是各种可调用对象，通过packaged_task把各种可调用对象包装起来，方便将来作为线程入口函数来调用。*/
//packaged_task包装起来的可调用，所以从这个角度来讲，pakcaged_task对象，也是一个可调用对象
	test();
	std::cout << "main " << "threadid =" << std::this_thread::get_id() << std::endl;
	std::packaged_task<int(int)>mypt(mythread);	//我们把函数mythread通过packaged_task包装起来
	std::thread t1(std::ref(mypt), 1);
	t1.join();	//等待线程执行完毕
	std::future<int>result = mypt.get_future();	//std::future对象包含有线程入口函数的返回结果，这里result保存mythread线程的返回值
	std::cout << result.get() << std::endl;
	//使用lambda表达式
	std::packaged_task<int(int)>mypt2([](int i) {
		std::cout << i << std::endl;
		std::cout << "mythread() start " << "threadid=" << std::this_thread::get_id() << std::endl;//打印新线程id
		std::chrono::milliseconds dura(1000);//延时一秒
		std::this_thread::sleep_for(dura);
		std::cout << "mythread() end " << "threadid=" << std::this_thread::get_id() << std::endl;
		return 50;
		});
	std::thread t2(std::ref(mypt2), 1);
	t2.join();	//等待线程执行完毕
	std::future<int>result2 = mypt2.get_future();	
	std::cout << result2.get() << std::endl;

	//放到容器
	std::packaged_task<int(int)>mypt3(mythread);	//我们把函数mythread通过packaged_task包装起来
	std::vector<std::packaged_task<int(int)>>mytasks;
	mytasks.push_back(std::move(mypt3));		//容器	用了移动语义，入进去后mypt就为空

	std::packaged_task<int(int)>mypt_;
	auto iter = mytasks.begin();
	mypt_ = std::move(*iter);	//移动语义
	mytasks.erase(iter);	//删除第一个元素，迭代器已经失效，所以后序代码不能再使用
	mypt_(123);
	std::future<int>result_ = mypt_.get_future();
	std::cout << result_.get() << std::endl;
}