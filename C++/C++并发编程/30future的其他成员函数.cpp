#include<iostream>
#include<thread>
#include<mutex>
#include<future>
int mythread() {	
	std::cout << "mythread() start " << "threadid=" << std::this_thread::get_id() << std::endl;
	std::chrono::milliseconds dura(2000);
	std::this_thread::sleep_for(dura);
	std::cout << "mythread() end " << "threadid=" << std::this_thread::get_id() << std::endl;
	return 5;
}
int main() {
/*一、std::future 的成员函数
1、std::future_status status = result.wait_for(std::chrono::seconds(几秒));
卡住当前流程，等待std::async()的异步任务运行一段时间，然后返回其状态std::future_status。如果std::async()的参数是std::launch::deferred（延迟执行），则不会卡住主流程。
常量 解释 wait_for的返回值
future_status::deferred 共享状态持有的函数正在延迟运行，结果将仅在显式请求时计算
future_status::ready 共享状态就绪
future_status::timeout 共享状态在经过指定的等待时间内仍未就绪
*/
	std::cout << "main " << "threadid=" << std::this_thread::get_id() << std::endl;
	//std::future<int>result = std::async(std::launch::deferred, mythread);
	std::future<int>result = std::async(mythread);
	std::cout << "continue......!" << std::endl;
	//枚举类型
	std::future_status status = result.wait_for(std::chrono::seconds(3));	//等待一秒钟,wait_for成员函数的返回值在上面
	if (status == std::future_status::timeout)//超时：我想等待你一秒钟，希望你返回，你没有返回，那么status==timeout
	{
		//线程还没执行完
		std::cout << "超时，线程还没有执行完毕" << std::endl;
	}
	else if (status == std::future_status::ready)
	{
		//表示线程成功返回
		std::cout << "线程成功执行完毕，返回" << std::endl;
		std::cout << result.get() << std::endl;
	}
	else if (status == std::future_status::deferred)//延迟
	{
		//如果async第一个参数被设置为std::launch::deferred则本条件成立
		std::cout << "线程被延迟执行" << std::endl;
		std::cout << result.get() << std::endl;		
	}

	//get只能调用一次，因为这是一个移动语义,如果再次调用就会引发异常，在我们这里的话必须满足status == std::future_status::ready第一次调用get()，然后重复调用get引发异常
	return 0;
}